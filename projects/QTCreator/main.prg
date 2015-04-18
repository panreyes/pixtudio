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
//import "mod_theora"
//import "mod_sound"

PROCESS int main();
Private
    int font;
    int time;

BEGIN
    set_mode(800,600,32);
    set_fps(60, 0);

    font = fnt_load("font.fnt");
    graph = png_load("logo.png");
    drawing_map(0, graph);
    drawing_color(rgb(0, 255, 0));
    point_set(0, graph, 0, 50, 50);
    draw_fcircle(50, 50, 10);
    //if((graph = video_play("sintel_trailer.ogv")) == -1)
    //    say("Sorry, I couldn't play your video :(");
    //    exit();
    //end;
    write(font, 0, 0, 0, "No flags");
    x = 400; y = 300;
    time = timer[0];
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
            /*elif(flags == B_HMIRROR)
                flags = B_VMIRROR;
                delete_text(ALL_TEXT);
                write(font, 0, 0, 0, "B_VMIRROR");
            elif(flags == B_VMIRROR)
                flags = B_HMIRROR+B_VMIRROR;
                delete_text(ALL_TEXT);
                write(font, 0, 0, 0, "B_HMIRROR+B_VMIRROR");*/
            else
                flags = 0;
                delete_text(ALL_TEXT);
                write(font, 0, 0, 0, "No flags");
            end
            time = timer[0];
        end
        if(key(_esc))
            break;
        end
        FRAME;
    End

    //video_stop();
    map_unload(0, graph);
    fnt_unload(font);
END

