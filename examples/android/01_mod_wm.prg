/**
 * Android test
 * Joseba García Etxebarria - (C) 2012
 * Use as you wish
 */

import "mod_video"
import "mod_sound"
import "mod_map"
import "mod_draw"
import "mod_say"
import "mod_file"
import "mod_text"
import "mod_wm"
import "mod_multi"

GLOBAL
// Set to your liking
width  = 320;
height = 240;
sound  = 1;
quit   = 0;

Process bouncer()
Private
    int vx=3, vy=3;
    int w=0, h=0;

Begin
    if(file_exists("Icon.png"))
        graph = load_png("Icon.png");
    else
        return 1;
    end
    // Position the graphic onscreen
    w = graphic_info(0, graph, G_WIDTH);
    h = graphic_info(0, graph, G_HEIGHT);
    x = width/2;
    y = height/2;
    while(quit == 0)
        if(x + vx + w/2 >= width || x + vx - w/2 < 0)
            vx = -vx;
        end
        if(y + vy + h/2 >= height || y + vy - h/2 < 0)
            vy = -vy;
        end
        x += vx; y += vy;
        FRAME;
    End;
End;

Process Main()
Private
int song=0, num_fingers=0, i=0;

Begin
    // Uncomment this to set a fixed resolution instead of using your device's
    // default one.
    // Your screen will hold a smaller rectangle with the resolution you set here
    //set_mode(width, height, 32, MODE_FULLSCREEN|MODE_FRAMELESS);
    // Get the real screen resolution we're running at
    width = graphic_info(0, 0, G_WIDTH);
    height = graphic_info(0, 0, G_HEIGHT);
    
    write(0, 0, 0, 0, "Width: "+width+" Height:"+height);
    write(0, width, height, 8, "'0 A.D. Main Theme' CC-BY-SA Wildfire games");
    
    graph = map_new(width, height, 32);
    x = width/2; y = height/2;

    bouncer();

    if(sound == 1)
        song = load_song("1.ogg");
        play_song(song, 0);
    end;
    write_var(0, 0, height, 6, num_fingers);
    drawing_map(0, graph);
    drawing_color(rgb(0, 255, 255));

    /* Some touchscreens cannot detect all 5 fingers at once */
    while(num_fingers < 4 && focus_status == 1)
        // Store the total amount of fingers touching the screen
        num_fingers = multi_numpointers();
        
        for(i=0; i<10; i++)
            if(multi_info(i, "ACTIVE") > 0)
                draw_fcircle(multi_info(i, "X"),
                             multi_info(i, "Y"), 5);
                say_fast("Drawing fcircle for pointer "+i+" @ "+
                             multi_info(i, "Y")+
                         "x"+multi_info(i, "X")+
                         " active:"+multi_info(i, "ACTIVE"));
            end;
        end;

        frame;
    End;

    unload_map(0, graph);
    if(sound == 1)
        unload_song(song);
    end

    quit = 1;
    say("Quitting");
End;
