import "mod_say"
import "mod_joy"
import "mod_video"
import "mod_text"

GLOBAL
scr_width = 640, scr_height=480;
End;

// Wiimote example code
// To get the Wiimote (also, nunchuck and gamecube controller) button codes,
// go to:
// http://wiibrew.org/wiki/SDL_Wii
Process main()
Private
	int n=0, i=0, die=0, joy=0;
Begin
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(scr_width, scr_height, 16, MODE_WINDOW))
        return -1;
    end;

    set_mode(scr_width, scr_height, 16, MODE_WINDOW);
    FRAME(5000);
	n = joy_number();	// Get the number of available joysticks
	if(n > 0)
    	write(0, scr_width/2, 80, 4, "There are "+n+" joysticks available");
	    write(0, scr_width/2, 90, 4, "Joystick names and available buttons:");
        write(0, scr_width/2, 100, 4, "=====================================");
        for(i=0; i<n; i++)
            write(0, scr_width/2, 110+10*i, 4, "Joy["+i+"]: "+joy_name(i)+" has "+joy_numbuttons(i)+" buttons");
        end;
        write(0, scr_width/2, 300, 4, "Press (A) in your Wiimote to continue");
        while(die == 0)
            for(i=0; i<n; i++)
                if(joy_getbutton(i, 0))
                    joy = i;
                    write(0, scr_width/2, 310, 4, "You pressed (A) in Wiimote "+joy);
                    die = 1;
                end;
            end;
            FRAME;
        end;
        write(0, scr_width/2, 320, 4, "Great, now press the (HOME) button on that Wiimote to quit");
        die=0;
        while(die == 0)
            if(joy_getbutton(joy, 6))
                write(0, scr_width/2, 330, 4, "Great, bye!");
                die = 1;
            end;
            FRAME;
        end;
    else
        write(0, scr_width/2, scr_height/2, 4, "Please, plug in a joystick to be able to use this code");
    end;
End;
