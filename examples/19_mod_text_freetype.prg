import "mod_video"
import "mod_text"
import "mod_key"
import "mod_map"
import "mod_say"

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
    ttf = ttf_load("ttf/DejaVuSans.ttf");
    ttf_set_size(ttf, ttf_size);
    say("Font family: " + ttf_get_family(ttf));
    say("Font style: " + ttf_get_style(ttf));

    // Paint the text red
    set_text_color(rgb(255,0,0));

    write(fnt, 512, 300, 4, fnt_rendering);
    write(ttf, 512, 320, 1, ttf_text);
    set_text_color(rgb(255,255,255));
    write(ttf, 512, 360, 1, ttf_text);
    x = 512; y = 380;
    while(!key(_esc))
        FRAME;
    end
    fnt_unload(fnt);
    fnt_unload(ttf);
End
