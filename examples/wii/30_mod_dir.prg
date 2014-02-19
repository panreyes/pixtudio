import "mod_dir"
import "mod_video"
import "mod_mouse"
import "mod_text"

GLOBAL
scr_width = 640, scr_height=480;
End;

Process main()
Private
	int i=0, dh=0;

Begin
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(scr_width, scr_height, 16, MODE_WINDOW))
        return -1;
    end;
    set_mode(scr_width, scr_height, 16, MODE_WINDOW);

    /* Display the first 5 files in the current rdirectory */
	write(0, scr_width/2, scr_height/4, 4, "First 5 files found by GLOB()");
	for(i=0; i<=4; i++)
		write(0, scr_width/2, scr_height/4 + 10*( i+1 ), 4, glob("*"));
	end;
	
	/* Display the first five files as read by the newer DIROPEN */
	write(0, scr_width/2, scr_height/4 + 10*( 7 ), 4, "First 5 files found by DIROPEN()");
	dh = diropen("*");
	for(i=0; i<=4; i++)
		write(0, scr_width/2, scr_height/4+10*( i+8 ), 4, dirread(dh));
	end;
	dirclose(dh);
	

    while(! mouse.left)
        FRAME;
    end;

	/* Delete all the text before quitting */
	delete_text(ALL_TEXT);
End;