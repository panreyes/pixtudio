// import modules
import "mod_proc"
import "mod_map"
import "mod_key"
import "mod_video"
import "mod_timers"

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

BEGIN
    set_mode(1600, 1200);
    set_fps(60, 0);

    graphid = png_load("image.png");

    pid = collisioner(graphid, 255, 255, 255);
    pid.x = 1600/2;
    pid.y = 1200/2;

    WHILE (NOT key(_esc))
        if(key(_right) && timer[0] > t0+50)
            t0 = timer[0];
            if(pid.modr == 255)
                pid.modr = 0;
            elif(pid.modg == 255)
                pid.modg = 0;
            elif(pid.modb == 255)
                pid.modb = 0;
            else
                pid.modr = 255;
                pid.modg = 255;
                pid.modb = 255;
            end
        end
        FRAME;
    END

    // kill all processes, execpt the "main" process.
    let_me_alone();
END

