import "mod_map"
import "mod_text"
import "mod_key"
import "mod_video"
import "mod_gamecontroller"

PROCESS int main();
Private
    int font;
    int n, i;
    int oldn;
    int controllerid;
    string controllername;

BEGIN
    set_mode(800, 600);
    set_fps(60, 0);

    font = fnt_load("font.fnt");
    n = controller_num();
    controllername = "";
    if(n > 0)
        for(i=0; i < n; i++)
            controllerid = controller_open(i);
            if(controllerid != CONTROLLER_INVALID)
                controllername += " " + controller_getname(controllerid);
                controller_close(controllerid);
            end
        end
    end
    write_var(font, 0, 0, 0, fps);
    write_var(font, 800, 0, 2, n);
    write_var(font, 0, 600, 6, controllername);

    WHILE (NOT key(_esc))
        oldn = n;
        n = controller_num();
        if(n != oldn)
            controllername = "";
            for(i=0; i < n; i++)
                controllerid = controller_open(i);
                if(controllerid != CONTROLLER_INVALID)
                    controllername += " " + controller_getname(controllerid);
                    controller_close(controllerid);
                end
            end
        end
        FRAME;
    END

    fnt_unload(font);
END

