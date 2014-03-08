// import modules
IMPORT "mod_say";
IMPORT "mod_proc";
IMPORT "mod_grproc";
IMPORT "mod_map";
IMPORT "mod_text";
IMPORT "mod_key";
IMPORT "mod_video";
IMPORT "mod_screen";
IMPORT "mod_draw";
IMPORT "mod_scroll";
import "mod_mouse";



GLOBAL

   int graphics_lib;

   int object1_id;

   int scroll_window;
   int scroll_blit_graph;
   int font;


PROCESS int main();

PRIVATE

BEGIN

    set_mode(640,480,32);
    set_fps(0,0);

    // load the fpg file with the graphics
    graphics_lib=load_fpg("graf2.fpg");
    font = load_fnt("font.fnt");

    // create an extended scroll, drawn on the "scroll_blit_graph".
    scroll_window=start_scroll(0,graphics_lib,1,0,0,3);

    // create the two objct processes.
    object1_id=object1(graphics_lib);

    // write instructions
    write(font ,20,30,ALIGN_CENTER_LEFT,"Scroll extended test demo");
    write(font ,20,40,ALIGN_CENTER_LEFT,"F3 and F4: decrease/increase size of destination map");
    write(font ,20,50,ALIGN_CENTER_LEFT,"F5 and F6: decrease/increase angle of destination map");
    write(font ,20,60,ALIGN_CENTER_LEFT,"F7 and F8: decrease/increase x of destination map");
    write(font ,20,70,ALIGN_CENTER_LEFT,"F9 and F10: decrease/increase y of destination map");
    write_int(font , 640, 480, 8, &fps);


    WHILE (NOT key(_esc))
        FRAME;
    END

    // stop scroll window.
    stop_scroll(0);


    // kill all processes, execpt the "main" process.
    let_me_alone();
END



PROCESS int object1 (int file);

PRIVATE

BEGIN

    graph=3;

    ctype=c_scroll;
    cnumber=c_0; // make this process visible in window 0

    scroll[0].camera=id;

    x=100;
    y=100;

    LOOP

        // move main object
        IF (key(_up) AND y >0)
           y-=5;
        END
        IF (key(_down) AND y <800)
           y+=5;
        END
        IF (key(_left) AND x >0)
           x-=5;
        END
        IF (key(_right) || mouse.left AND x <2000)
           x+=5;
        END

        FRAME;
    END
END
