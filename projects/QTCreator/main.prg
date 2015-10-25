import "mod_map"
import "mod_text"
import "mod_key"
import "mod_video"
import "mod_timers"
import "mod_text"
import "mod_say"
import "mod_proc"
import "mod_mouse"
import "mod_draw"
import "mod_theora"
import "mod_sound"
import "mod_math"

PROCESS int main();
Private
    int font;
    int time;
    int vol=255;

BEGIN
    set_mode(1024, 768, 16);
    set_fps(60, 0);

    font = fnt_load("font.fnt");
    if((graph = video_play("sintel_trailer-1080p.ogv")) == -1)
        say("Sorry, I couldn't play your video :(");
        exit();
    end;
    write(font, 0, 0, 0, "No flags");
    x = 1024/2; y = 768/2;
    time = timer[0];
    vol = 255;
    LOOP
        if(key(_right))
            angle -= 500;
        end
        if(key(_left))
            angle += 500;
        end
        if(key(_f) && timer[0] > time+50 )
            if(flags == 0)
                flags = B_HMIRROR;
                delete_text(ALL_TEXT);
                write(font, 0, 0, 0, "B_HMIRROR");
            elif(flags == B_HMIRROR)
                flags = B_VMIRROR;
                delete_text(ALL_TEXT);
                write(font, 0, 0, 0, "B_VMIRROR");
            elif(flags == B_VMIRROR)
                flags = B_HMIRROR+B_VMIRROR;
                delete_text(ALL_TEXT);
                write(font, 0, 0, 0, "B_HMIRROR+B_VMIRROR");
            else
                flags = 0;
                delete_text(ALL_TEXT);
                write(font, 0, 0, 0, "No flags");
            end
            time = timer[0];
        end

        // Volume setting
        if(key(_p))
            vol += 2;
            if(vol > 255)
                vol = 255;
            end
            video_set_volume(vol);
        end
        if(key(_m))
            vol -= 2;
            if(vol < 0)
                vol = 0;
            end
            video_set_volume(vol);
        end
        if(key(_esc))
            break;
        end
        FRAME;
    End

    video_stop();
    fnt_unload(font);
END

