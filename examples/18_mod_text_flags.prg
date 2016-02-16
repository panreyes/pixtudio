import "mod_map"
import "mod_key"
import "mod_video"
import "mod_text"

PROCESS int main();
Private
    int font;

BEGIN
    set_mode(800, 600);
    set_fps(60, 0);

    font = fnt_load("fnt/font.fnt");
    write(font, 400, 300, 7, "No flags");
    text_flags = B_HMIRROR;
    write(font, 400, 300, 1, "B_HMIRROR");
    LOOP
        if(key(_esc))
            break;
        end
        FRAME;
    End

    fnt_unload(font);
END

