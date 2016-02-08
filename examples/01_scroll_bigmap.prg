// import modules
import "mod_say"
import "mod_proc"
import "mod_grproc"
import "mod_map"
import "mod_text"
import "mod_key"
import "mod_video"
import "mod_screen"
import "mod_draw"
import "mod_scroll"
import "mod_sound"

GLOBAL
   int graphic;
   int scroll_window;
   int scroll_window2;

Process collisioner()
Private
    int v = 2;
    string collided;
BEGIN
    graph = png_load("png/logo.png");
    //collision_graph = mouse.graph;
    x = 400; y = 300;
    write_var(0, 800, 0, 2, collided);
    LOOP
        collided = "Collision: " + collision(TYPE mouse);
        FRAME;
    END
END


PROCESS int main();
BEGIN
    set_mode(800, 600);
    set_fps(60, 0);

    flags=B_HMIRROR;

    // load the PNG file with the graphics
    mouse.graph = png_load("png/ball_opaque.png");
    graphic = png_load("png/longbg_x.png");
    say("Scroll image: "+graphic);

    // (standard version)
    // int scroll_start (int scrollnumber,
    //                   int file,
    //                   int graph,
    //                   int backgroundgraph,
    //                   int regionnumber,
    //                   int lockindicator);

    // create an extended scroll, drawn on the "scroll_blit_graph".
    scroll_window=scroll_start(0,0,graphic,0,0,3);
    scroll_window2=scroll_start(1,0,graphic,0,0,3);

    scroll[0].modr1 = 0;
    scroll[1].modg1 = 0;

    write_var(0, 10, 10, 0, fps);

    collisioner();

    WHILE (NOT key(_esc))
        if(! key(_down))
            if(key(_right) || mouse.left)
                scroll[0].x0 += 30;
            elseif(key(_left))
                scroll[0].x0 -= 30;
            else
                scroll[0].x0 += 30;
            end
        end
        scroll[1].x0 -= 15;
        FRAME;
    END

    // stop scroll window.
    scroll_stop(0);

    // kill all processes, execpt the "main" process.
    let_me_alone();
END


