import "mod_say"
import "mod_video"
import "mod_map"

Process main()
Private
    int ttf;
Begin
    // Load a TTF file and print its family and style names
    ttf = ttf_load("ttf/DejaVuSans.ttf");
    say("System font:        '" + ttf_get_family(0) + "'->'" + ttf_get_style(0) + "'");
    say("ttf/DejaVuSans.ttf: '" + ttf_get_family(ttf) + "'->'" + ttf_get_style(ttf) + "'");
    if(OS_ID == OS_WIN32)
        fnt_unload(ttf);
        ttf = ttf_load("c:/Windows/Fonts/arial.ttf");
        if(ttf > 0)
            say("c:/Windows/Fonts/arial.ttf: '" + ttf_get_family(ttf) + "'->'" + ttf_get_style(ttf) + "'");
        end
        fnt_unload(ttf);
        ttf = ttf_load("c:/Windows/Fonts/arialbd.ttf");
        if(ttf > 0)
            say("c:/Windows/Fonts/arialbd.ttf: '" + ttf_get_family(ttf) + "'->'" + ttf_get_style(ttf) + "'");
        end
        fnt_unload(ttf);
        ttf = ttf_load("c:/Windows/Fonts/arialbi.ttf");
        if(ttf > 0)
            say("c:/Windows/Fonts/arialbi.ttf: '" + ttf_get_family(ttf) + "'->'" + ttf_get_style(ttf) + "'");
        end
        fnt_unload(ttf);
        ttf = ttf_load("c:/Windows/Fonts/ariali.ttf");
        if(ttf > 0)
            say("c:/Windows/Fonts/ariali.ttf: '" + ttf_get_family(ttf) + "'->'" + ttf_get_style(ttf) + "'");
        end
        fnt_unload(ttf);
    end
End
