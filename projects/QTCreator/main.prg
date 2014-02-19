import "mod_video"
import "mod_key"
import "mod_map"
import "mod_draw"
import "mod_say"
import "mod_screen"

Process main()
Private
int width = 640;
int height = 480;
int vx = 5;
int vy = 5;
int img = 0;

Begin
    set_mode(width, height, 32);
    FRAME;
    /*graph = new_map(20, 20, 16);
    drawing_map(0, graph);
    drawing_color(rgb(255, 0, 0));
    draw_box(0, 0, 20, 20);*/
    graph = load_png("ball.png");
    img = load_png("image.png");
    put(0, img, width/2, height/2);
    x = width/2; y = width/2;
    while(! key(_esc))
        if(x+10 > width || x-10 < 0)
            vx = -vx;
        end
        if(y+10 > height || y-10 < 0)
            vy = -vy;
        end

        if(key(_right))
            angle -= 5000;
        end

        if(key(_left))
            angle += 5000;
        end

        if(key(_up))
            graph++;
            say(graph);
        end

        if(key(_down))
            graph--;
            say(graph);
        end

        if(key(_x))
            size_x += 5;
        end

        if(key(_y))
            size_y += 5;
        end

        x += vx;
        y += vy;

        FRAME;
    end
    unload_map(0, graph);
    unload_map(0, img);
End
