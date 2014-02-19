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
	    LOOP
        	write(0, scr_width/2, 80, 4, "There are "+n+" joysticks available");
	        write(0, scr_width/2, 90, 4, "Joystick names and available buttons:");
            write(0, scr_width/2, 100, 4, "=====================================");
            for(i=0; i<n; i++)
                write(0, scr_width/2, 110+10*i, 4, "Joy["+i+"]: Button 0: "+joy_getbutton(i, 0));
            end;
            write(0, scr_width/2, 300, 4, "Press (A) in Wiimote 0 to quit");
            if(joy_getbutton(0, 6))
                break;
            end;
            FRAME;
            delete_text(ALL_TEXT);
        end;
    else
        write(0, scr_width/2, scr_height/2, 4, "Please, plug in a joystick to be able to use this code");
    end;
End;
