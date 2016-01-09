import "mod_say";
import "mod_proc";
import "mod_time";
import "mod_joy";

/* Not really a zombie, but it'll refuse to die */
Process zombie()
Private
    int now=0;
    string formatted="", old="";

Begin
    /* Flag this process as unkillable, by normal means */
    signal_action(id, S_KILL, S_IGN);
    LOOP
        now = time();
        formatted=ftime("%d-%m-%Y %H:%M:%S, std zombie time", now);
        if(formatted != old)
            old = formatted;
            say(id+": "+formatted);
        end;
        FRAME;
    End;
End;

/* A process we'll just keep killing */
Process dummie()
Private
    int now=0;
    string formatted="", old="";

Begin
    say("My father is "+father);
    LOOP
        now = time();
        formatted=ftime("%d-%m-%Y %H:%M:%S", now);
        if(formatted != old)
            old = formatted;
            say(id+": "+formatted);
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
    say(id+": Test 1, press (A) in your Wiimote to continue");
    while(!joy_getbutton(0, 0))
        FRAME;
    End;
    procid = dummie();
    say("Press (B) in your Wiimote to kill the process");
    while(!joy_getbutton(0, 1))
        FRAME;
    End;
    signal(procid, S_KILL);
    if(exists(procid))  // Shouldn't happen
        say("Process NOT killed, this is bad");
    else
        say("Process killed, continuing happily");
    end;
    procid=0;

    // Killing a process by let_me_alone 
    say("Test 2, press (A) in your Wiimote to continue");
    while(!joy_getbutton(0, 0))
        FRAME;
    End;
    procid=dummie();   // Call the process
    say("Press (B) in your Wiimote to kill the process");
    while(!joy_getbutton(0, 1))
        FRAME;
    End;
    let_me_alone(); // Kill it
    if(exists(TYPE dummie))  // Shouldn't happen
        say("Process NOT killed, this is bad");
    else
        say("Process killed, continuing happily");
    end;

/*
    say("Test finished, press (B) in yoour wiimote to continue");
    while(!joy_getbutton(0, 1))
        FRAME;
    End;

    // Killing that same process by guessing its id
    say("Test 3, press (A) in your Wiimote to continue");
    dummie();
    procid = get_id(TYPE dummie);
    if(procid > 0)  // This should be true
        signal(procid, S_KILL);
        if(exists(procid))  // Shouldn't happen
            say("Process NOT killed, this is bad");
        else
            say("Process killed, continuing happily");
        end;
        procid = 0;
    end;
    
    say("Test finished, press (B) in yoour wiimote to continue");
    while(!joy_getbutton(0, 1))
        FRAME;
    End;
    
    // Killing a process that's marked itself to not receive normal 
    // S_KILL signals
    say("Test 4, press (A) in your Wiimote to continue");
    while(!joy_getbutton(0, 0))
        FRAME;
    End;
    procid = zombie();
    signal(procid, S_KILL);
    if(exists(procid))
        say("Process NOT killed, this is bad... will have to use force");
        signal(procid, S_KILL_FORCE);
        if(!exists(procid))
            say("Process killed, continuing happily");
        else
            say("Something went wrong :(");
        end;
    else    // Shouldn't happen
        say("Process killed, continuing happily");
    end;

    // Done
    */
    say("Bye!");
    
    while(!joy_getbutton(0, 0))
        FRAME;
    End;
    
    exit();
End;
