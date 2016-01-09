import "mod_timers";
import "mod_say";

/* Will wait for 5 seconds before displaying a "Hello, World!" */
Function main()
Private
    int time=0;
    int delay=500;
Begin
    time = timer[9];
    say("Time's now: "+time);
    while(timer[9] < time+delay)
        FRAME;
    end;
    say("Hello, World!");
End;
