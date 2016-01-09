import "mod_key"
import "mod_video"
import "mod_text"
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

    while(! key(_esc))
        FRAME;
    End;
End
