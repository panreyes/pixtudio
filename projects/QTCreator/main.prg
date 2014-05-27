import "mod_video"
import "mod_key"
import "mod_map"
import "mod_draw"
import "mod_say"
import "mod_screen"
import "mod_text"
import "mod_proc"
import "mod_file"

GLOBAL
int width = 1024;
int height = 768;
End;

Process bouncer(graph, x, y, vx, vy)
Begin
    region = 1;
    loop
        if(x + graphic_info(0, graph, G_WIDTH)/2 > width || x - graphic_info(0, graph, G_WIDTH)/2 < 0)
            vx = -vx;
        end
        if(y + graphic_info(0, graph, G_HEIGHT)/2 > width || y - graphic_info(0, graph, G_HEIGHT)/2 < 0)
            vy = -vy;
        end
        x += vx;
        y += vy;
        FRAME;
    End
End

Process main()
Private
int vx = 2;
int vy = 2;
int img = 0;
int font = 0;
int fd = 0;

Begin
    set_mode(width, height, 32);
    fd = fopen("main.prg", O_READ);
    //while(!feof(fd))
        //say(fgets(fd));
    //end
    //say("EOF");
    fclose(fd);
    graph = load_png("bigimage.png");
    bouncer(graph, width/2, height/2, -3*vx, -3*vy);
    img = load_png("image.png");
    put(0, img, width/2, height/2);
    font = load_fnt("font.fnt");
    write(font, width/2, height/2, 4, "OLA, KE ASE?");
    x = width/2; y = width/2;
    define_region(1, 0, 0, width/2, height/2);
    while(! key(_esc))
        /*if(x+10 > width || x-10 < 0)
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

        if(key(_x))
            size_x += 5;
        end

        if(key(_y))
            size_y += 5;
        end

        if(key(_a))
            alpha += 1;
        end

        if(key(_z))
            alpha -= 1;
        end*/

        if(key(_left))
            x -= 100;
        end
        if(key(_right))
            x += 100;
        end
        if(key(_up))
            y -= 100;
        end
        if(key(_down))
            y += 100;
        end

        if(key(_space))
            save_png(0, get_screen(), "shot.png");
            say("Saved as shot.png");
        end

        /*x += vx;
        y += vy;*/

        FRAME;
    end
    let_me_alone();
    unload_map(0, graph);
    unload_map(0, img);
    unload_fnt(font);
End
