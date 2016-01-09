import "mod_say";
import "mod_time";

/* A process we'll just keep killing */
Process dummie()
Private
    int now=0, then=0;
    string formatted="", old="";

Begin
    then = time();
    while(1)
        now = time();
        formatted=ftime("%d-%m-%Y %H:%M:%S", now);
        if(formatted != old)
            old = formatted;
            say(id+": "+formatted);
        end;

        if(now > then+10)
            return;
        end;
        FRAME;
    End;
End;

/* Main process that'll kill dummie as many times as needed */
/* to prove I'm right.                                      */
Process main()
Private
    int procid=0;

Begin
    /* Killing the process by its return code */
    procid = dummie();
End;
