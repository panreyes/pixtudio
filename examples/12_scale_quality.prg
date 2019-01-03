import "mod_key"
import "mod_video"
import "mod_map"
import "mod_draw"
import "mod_proc"
import "mod_math"
import "mod_say"
import "mod_sys"
import "mod_wm"

Process main()
private
    string title = "";
begin
    if(argc == 2)
        if(argv[1] == '--nearest')
            title = "Nearest neighbour scaling";
            scale_quality = SCALE_NEAREST;
        elif(argv[1] == '--anisotropic')
            title = "Anisotropic scaling";
            scale_quality = SCALE_ANISOTROPIC;
        end
    else
        title = "Linear scaling";
        scale_quality = SCALE_LINEAR;
    end

    set_mode(640, 480, MODE_FULLSCREEN);
    set_title(title);
    set_fps(60,0);

    x=400;
    y=240;

    drawing_map(0,0);
    drawing_color(rgb(255, 255, 255));
    draw_box(0, 0, 640, 480);

    graph = png_load("png/inventoman.png");

    escalado();

    repeat
        angle-= 1000;
        frame;
    until(key(_esc))

    exit();
end

process escalado()
private float i, e;

begin
    graph = father.graph;
    x = 180;
    y = 240;

    loop
        size= 100 + e*20;
        e = sin(i*2000);
        i+= 1;
        frame;
    end
end
