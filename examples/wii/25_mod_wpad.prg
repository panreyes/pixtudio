import "mod_wpad"
import "mod_video"
import "mod_text"
import "mod_mouse"

GLOBAL
scr_width = 640, scr_height=480;
End;

Process main()
Private
    int i=0, bb=-1, weight=0;

Begin
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(scr_width, scr_height, 16, MODE_WINDOW))
        return -1;
    end;
    set_mode(scr_width, scr_height, 16, MODE_WINDOW);

    while(! mouse.left)
        for(i=0; i<=7; i++)
            if(wpad_is_ready(i) > 0)
                write(0, scr_width/2, 50+10*i, 4, "Joy "+i+" is ready (Battery: "+
                      wpad_info(i, WPAD_BATT)+
                      ")");
            end;
            if(wpad_info(i, WPAD_IS_BB) > 0)
                write(0, scr_width/2, scr_height/2+10*i, 4, "Using "+i+" as a Balance Board");
                bb = i;
            end;
        end;
        if(bb >= 0)
            // Get your weight (in kg) from the Wii Balance Board
            weight  = wpad_info_bb(bb, WPAD_WTL);
            weight += wpad_info_bb(bb, WPAD_WTR);
            weight += wpad_info_bb(bb, WPAD_WBL);
            weight += wpad_info_bb(bb, WPAD_WBR);
            write(0, scr_width/2, 3*scr_height/4, 4, "Meassured weight: "+
                weight );
            // Get the position of your center of gravity
            write(0, scr_width/2, 3*scr_height/4+10, 4, "X:"+
                wpad_info_bb(bb, WPAD_X) + " Y: "+
                wpad_info_bb(bb, WPAD_Y) );
        end;
        FRAME;
        delete_text(ALL_TEXT);
        bb = -1;
    End;
End;
