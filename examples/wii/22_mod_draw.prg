import "mod_draw"
import "mod_video"
import "mod_mouse"
import "mod_map"

GLOBAL
scr_width = 640, scr_height=480;
End;

Process main()
Begin
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(scr_width, scr_height, 8, MODE_WINDOW))
        return -1;
    end;
    set_mode(scr_width, scr_height, 8, MODE_WINDOW);

    /* Draw a big red circle in the middle of the screen */
    drawing_map(0, 0);
    drawing_color(rgb(255, 0, 0));
    draw_fcircle(scr_width/2, scr_height/2, scr_height/3);
    /* Now, draw a smaller green box */
    drawing_color(rgb(0, 255, 0));
    draw_box(scr_width/4, scr_height/4, 3*scr_width/4, 3*scr_height/4);

    while(! mouse.left)
        FRAME;
    end;

    // Delete all the drawings
    delete_draw(0);
End;
