import "mod_grproc"
import "mod_map"
import "mod_video"

GLOBAL
scr_width = 640, scr_height=480;
End;

Process main()
Begin
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(scr_width, scr_height, 16, MODE_WINDOW))
        return -1;
    end;
    set_mode(scr_width, scr_height, 16, MODE_WINDOW);

    // Load the graph and put it in the middle of the screen
    graph = png_load("mouse.png");
    x = scr_width/2; y = scr_height/2;
    while(!mouse.left)
        angle+=2000;
        advance(5);
        
        if(mouse.right) //Restart the cursor position
            x = scr_width/2;
            y = scr_height/2;
        end;
        FRAME;
    end;
End;
