import "mod_video"
import "mod_text"
import "mod_key"
import "mod_map"
import "mod_say"
import "mod_ttf"

Process main()
Private
    int fnt;
    int ttf;
    int graph_ttf;
Begin
    set_mode(800, 600);
    fnt = fnt_load("fnt/font.fnt");
    graph_ttf = modttf_load("/opt/android-sdk/platforms/android-19/data/fonts/Roboto-Regular.ttf",
                            "Hello, FreeType world!", 20);
    png_save(0, graph_ttf, "/home/joseba/tmp/mod_ttf.png");
    // Size should be 199x20
    ttf = ttf_load("/opt/android-sdk/platforms/android-19/data/fonts/Roboto-Regular.ttf");
    say(fnt);
    say(ttf);
    write(fnt, 400, 300, 4, "Hello, world!");
    write(ttf, 400, 320, 4, "Hello, FreeType world!");
    while(!key(_esc))
        FRAME;
    end
    fnt_unload(fnt);
    fnt_unload(ttf);
End
