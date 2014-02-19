import "mod_map"
import "mod_math"
import "mod_mouse"
import "mod_video"
import "mod_rand"
import "mod_text"
import "mod_sound"
import "mod_file"

Global
    scr_width=640, scr_height=480;
End;

Process main()
Private
    int textid=0, song=0;
    int font=0, fd=0;

Begin
    // Check that we can set the video mode before actually setting it
    if(!mode_is_ok(scr_width, scr_height, 16, MODE_WINDOW))
        return -1;
    end;
    set_mode(scr_width, scr_height, 16, MODE_WINDOW);
    
    // Load the example font
    font = load_fnt("font.fnt");
    if(font <= 0)
        write(0, scr_width, scr_height, 8, "Font load error: "+font);
    else
        write(font, scr_width/2, scr_height/2+10, 1, "Sample text");
    end;
    
    // Load the song and play it
    song = load_song("game.s3m");
    play_song(song, 0);

    // Set the text color and write a "Hello, World!" message
    // Should appear in red colour
    set_text_color(rgb(255, 0, 0));
    textid = write(0, scr_width/2, scr_height/2, ALIGN_CENTER, "Hello, world!");
    while(! mouse.left)
        // When pressing the right button in the mouse, move the text down
        if(mouse.right)
            move_text(textid, rand(0, scr_width), rand(0, scr_height));
        end;
        FRAME;
    end;
    
    // Delete the text
    delete_text(ALL_TEXT);

    // Unload stuff
    stop_song();
    unload_song(song);
    unload_fnt(font);
End;
