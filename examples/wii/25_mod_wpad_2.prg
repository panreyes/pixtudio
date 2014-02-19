import "mod_video"
import "mod_text"
import "mod_mouse"
import "mod_wpad"
import "mod_map"
import "mod_math"
import "mod_grproc"

GLOBAL
scr_width = 640, scr_height=480;
End;

Process rumble_a_bit(int which)
Begin
    wpad_rumble(which, 1);  // Start rumbling
    FRAME(200);
    wpad_rumble(which, 0);
End;

Process main()
Private
    int myw=0, myh=0, vx=5, vy=5, was_colliding=0;

Begin
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(scr_width, scr_height, 16, MODE_WINDOW))
        return -1;
    end;
    set_mode(scr_width, scr_height, 16, MODE_WINDOW);

    mouse.graph = png_load("mouse.png");
    graph        = png_load("logo.png");
    myw=graphic_info(0, graph, G_WIDTH)/2;
    myh=graphic_info(0, graph, G_HEIGHT)/2;

    x=scr_width/2; y=scr_height/2;

    while(! mouse.left)
        if(x > scr_width-(myw+abs(vx)) || x < (myw+abs(vx)))
            vx = -vx;
        end;
        if(y > scr_height-(myh+abs(vy)) || y < (myh+abs(vy)))
            vy = -vy;
        end;
        x+=vx; y+=vy;
        if(collision(TYPE mouse))
            if(! was_colliding)
                rumble_a_bit(0);
            end;
            was_colliding = 1;
        else
            if(was_colliding)
                rumble_a_bit(0);
            end;
            was_colliding = 0;
        end;
        FRAME;
    End;
    
    map_unload(0, mouse.graph);
    map_unload(0, graph);
End;
