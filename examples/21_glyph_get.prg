import "mod_map"
import "mod_video"
import "mod_key"
import "mod_say"

Process main()
Begin
    set_mode(800, 600);
    x = 400;
    y = 300;
    graph = glyph_get(0, 65);   // "A"
    while(!key(_esc))
        FRAME;
    End
End