// import modules
import "mod_proc"
import "mod_map"
import "mod_key"
import "mod_video"
import "mod_timers"
import "mod_mouse"

Process collisioner(graph, modr, modg, modb)
BEGIN
    LOOP
        FRAME;
    END
END


PROCESS int main();
Private
    int graphid;
    int pid=0;
    int t0=0;
    int state=0;

BEGIN
    set_mode(800, 600);
    set_fps(60, 0);

    mouse.graph = png_load("png/ball_opaque.png");

    graphid = png_load("png/logo.png");

    pid = collisioner(graphid, 255, 255, 255);
    pid.x = 800/2;
    pid.y = 600/2;

    WHILE (NOT key(_esc))
        if(key(_right) && timer[0] > t0+50)
            t0 = timer[0];
            if(state == 0)
                pid.modr = 0;
                pid.modg = 255;
                pid.modb = 255;
                mouse.modr = 0;
                mouse.modg = 255;
                mouse.modb = 255;
                state++;
            elif(state == 1)
                pid.modr = 255;
                pid.modg = 0;
                pid.modb = 255;
                mouse.modr = 255;
                mouse.modg = 0;
                mouse.modb = 255;
                state++;
            elif(state == 2)
                pid.modr = 255;
                pid.modg = 255;
                pid.modb = 0;
                mouse.modr = 255;
                mouse.modg = 255;
                mouse.modb = 0;
                state++;
            else
                pid.modr = 255;
                pid.modg = 255;
                pid.modb = 255;
                mouse.modr = 255;
                mouse.modg = 255;
                mouse.modb = 255;
                state=0;
            end
        end
        FRAME;
    END

    // kill all processes, execpt the "main" process.
    let_me_alone();
END

