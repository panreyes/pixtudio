import "mod_video"
import "mod_wm"
import "mod_key"
import "mod_text"

Process main()
Begin
    set_mode(640, 480, MODE_WINDOW);
    write(0, 320, 240, 4, "Press enter");
    while(! key(_enter))
        FRAME;
    end

    delete_text(ALL_TEXT);
    write(0, 320, 240, 4, "Press space after closing the dialog box");
    FRAME;

    messagebox(MESSAGEBOX_WARNING, "Message title", "message text");

    while(! key(_space))
        FRAME;
    end
End
