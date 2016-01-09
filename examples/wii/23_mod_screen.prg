import "mod_video"
import "mod_screen"
import "mod_map"
import "mod_mouse"


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

    screen_put(0, png_load("logo.png"));
    while(! mouse.left)
        FRAME;
    End;
    screen_clear();
End;
