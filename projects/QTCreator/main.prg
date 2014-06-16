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



GLOBAL

   int graphic;
   int font;
   int scroll_window;
   int scroll_window2;


PROCESS int main();
BEGIN

    set_mode(800,600,32);
    set_fps(30, 0);

    // load the PNG file with the graphics
    graphic = load_png("longbg_x.png");
    font = load_fnt("font.fnt");

    // (standard version)
    // int start_scroll (int scrollnumber,
    //                   int file,
    //                   int graph,
    //                   int backgroundgraph,
    //                   int regionnumber,
    //                   int lockindicator);

    // create an extended scroll, drawn on the "scroll_blit_graph".
    scroll_window=start_scroll(0,0,graphic,0,0,3);
    scroll_window2=start_scroll(1,0,graphic,0,0,3);
    write_var(font, 10, 10, 0, fps);

    WHILE (NOT key(_esc))
        if(key(_right) || mouse.left)
            scroll[0].x0 += 30;
        end
        if(key(_left))
            scroll[0].x0 -= 30;
        end
        scroll[0].x0 += 30;
        scroll[1].x0 -= 15;
        FRAME;
    END

    // stop scroll window.
    stop_scroll(0);


    // kill all processes, execpt the "main" process.
    let_me_alone();
END

