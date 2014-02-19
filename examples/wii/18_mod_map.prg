import "mod_map"
import "mod_math"
import "mod_mouse"
import "mod_video"
import "mod_proc"
import "mod_say"

Global
    scr_width=640, scr_height=480;
End;

Process ball(int x, int y, int graph)
Private
    int vx=5, vy=5;
    int myw=0, myh=0;
Begin
    myw=graphic_info(0, graph, G_WIDTH)/2;
    myh=graphic_info(0, graph, G_HEIGHT)/2;
    LOOP
        if(x > scr_width-(myw+abs(vx)) || x < (myw+abs(vx)))
            vx = -vx;
        end;
        if(y > scr_height-(myh+abs(vy)) || y < (myh+abs(vy)))
            vy = -vy;
        end;
        x+=vx;
        y+=vy;
        FRAME;
    End;
End;

Process main()
Private
    int pid1=0;
    int map=0;
Begin
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(scr_width, scr_height, 16, MODE_WINDOW))
        return -1;
    end;
    set_mode(scr_width, scr_height, 16, MODE_WINDOW);
    map=png_load("logo.png");
    pid1=ball(scr_width/2, scr_height/2, map);
    while(!mouse.left)
        FRAME;
    End;
    signal(son, S_KILL);
    map_unload(0, map);
End;
