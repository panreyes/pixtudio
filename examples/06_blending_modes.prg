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
import "mod_sound"
import "mod_math"
import "mod_debug"
import "mod_say"

Process bigbox()
Begin
    graph = map_new(640, 480, 32);
    drawing_map(0, graph);
    drawing_color(rgb(20, 20, 20));
    draw_box(0, 0, 320, 240);
    drawing_color(rgb(100, 125, 140));
    draw_box(320, 0, 640, 240);
    drawing_color(rgb(50, 200, 120));
    draw_box(0, 240, 320, 480);
    drawing_color(rgb(150, 40, 90));
    draw_box(320, 240, 640, 480);
    center_set(0, graph, 320, 240);
    x = 320; y = 240;
    LOOP
        FRAME;
    End
End

Process smallbox()
Begin
    graph = map_new(200, 150, 32);
    drawing_map(0, graph);
    drawing_color(rgb(255, 255, 255));
    draw_box(0, 0, 100, 75);
    drawing_color(rgb(255, 0, 0));
    draw_box(100, 0, 200, 150);
    drawing_color(rgb(0, 255, 0));
    draw_box(0, 75, 100, 150);
    drawing_color(rgb(0, 0, 255));
    draw_box(100, 75, 200, 150);
    center_set(0, graph, 100, 75);
    angle = 180000;
    x = 320; y = 240;
    z = -10;
    alpha = 200;
    LOOP
        angle -= 200;
        FRAME;
    End
End

PROCESS int main();
Private
    int time;
    int pid;

BEGIN
    set_mode(640, 480);
    set_fps(60, 0);

    time = timer[0];
    bigbox();
    pid = smallbox();
    pid.flags = B_ALPHA;
    write(0, 0, 0, 0, "Alpha blending (B_ALPHA)");
    LOOP
        if(key(_f) && timer[0] > time+50 )
            if(pid.flags == B_ALPHA)
                pid.flags = B_ABLEND;
                delete_text(ALL_TEXT);
                write(0, 0, 0, 0, "Additive blending (B_ABLEND)");
            elif(pid.flags == B_ABLEND)
                pid.flags = B_MBLEND;
                delete_text(ALL_TEXT);
                write(0, 0, 0, 0, "Module blending (B_MBLEND)");
            elif(pid.flags == B_MBLEND)
                pid.flags = B_NOCOLORKEY;
                delete_text(ALL_TEXT);
                write(0, 0, 0, 0, "No colorkey (B_NOCOLORKEY)");
            else
                pid.flags = B_ALPHA;
                delete_text(ALL_TEXT);
                write(0, 0, 0, 0, "Alpha blending (B_ALPHA)");
            end
            time = timer[0];
        end

        if(key(_esc))
            let_me_alone();
            break;
        end
        FRAME;
    End
END

