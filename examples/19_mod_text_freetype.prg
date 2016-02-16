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
    int ttf_size = 30;
    string fnt_rendering = "Text rendering with a bitmap font";
    string ttf_text = "Text rendering with Freetype";
Begin
    set_mode(1024, 600);
    fnt = fnt_load("fnt/font.fnt");
    graph = modttf_load("/usr/share/fonts/dejavu/DejaVuSans.ttf",
                        ttf_text, ttf_size);
    png_save(0, graph, "/home/joseba/tmp/mod_ttf.png");
    ttf = ttf_load("/usr/share/fonts/dejavu/DejaVuSans.ttf");
    ttf_set_size(ttf, ttf_size);
    write(fnt, 512, 300, 4, fnt_rendering);
    // Size should be 295x29
    write(ttf, 512, 320, 1, ttf_text);
    x = 512; y = 380;
    while(!key(_esc))
        FRAME;
    end
    fnt_unload(fnt);
    fnt_unload(ttf);
End
