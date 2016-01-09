import "mod_joy"
import "mod_wpad"
import "mod_video"
import "mod_text"
import "mod_mouse"
import "mod_map"

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

    graph = png_load("logo.png");

    x=scr_width/2; y=scr_height/2;

    while(! mouse.left)
        x = mouse.x; y=mouse.y;
        angle = wpad_info(0, WPAD_ANGLE);
        write(0, scr_width/2, scr_height/2, 4, "ANGLE: "+wpad_info(0, WPAD_ANGLE));
        write(0, scr_width/2, scr_height/2+10, 4, "ACCELX: "+wpad_info(0, WPAD_ACCELX));
        write(0, scr_width/2, scr_height/2+20, 4, "ACCELY: "+wpad_info(0, WPAD_ACCELY));
        write(0, scr_width/2, scr_height/2+30, 4, "ACCELZ: "+wpad_info(0, WPAD_ACCELZ));
        write(0, scr_width/2, scr_height/2+40, 4, "GX: "+wpad_info(0, WPAD_GX));
        write(0, scr_width/2, scr_height/2+50, 4, "GY: "+wpad_info(0, WPAD_GY));
        write(0, scr_width/2, scr_height/2+60, 4, "GZ: "+wpad_info(0, WPAD_GZ));
        if(wpad_info(0, WPAD_HAS_NUNCHUK))
            write(0, scr_width/2, scr_height/2+70, 4, "NUNCHUK ACCELX: "+wpad_info_nunchuk(0, WPAD_ACCELX));
            write(0, scr_width/2, scr_height/2+80, 4, "NUNCHUK ACCELY: "+wpad_info_nunchuk(0, WPAD_ACCELY));
            write(0, scr_width/2, scr_height/2+90, 4, "NUNCHUK ACCELZ: "+wpad_info_nunchuk(0, WPAD_ACCELZ));
            write(0, scr_width/2, scr_height/2+100, 4, "NUNCHUK GX: "+wpad_info_nunchuk(0, WPAD_GX));
            write(0, scr_width/2, scr_height/2+110, 4, "NUNCHUK GY: "+wpad_info_nunchuk(0, WPAD_GY));
            write(0, scr_width/2, scr_height/2+120, 4, "NUNCHUK GZ: "+wpad_info_nunchuk(0, WPAD_GZ));
        end;
        FRAME;
        delete_text(ALL_TEXT);
    End;
    
    map_unload(0, graph);
End;
