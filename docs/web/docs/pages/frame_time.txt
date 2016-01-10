<category:variables> <category:predefined> [category:global
variables](category:global_variables "wikilink") <category:librender>

[**Up to Global Variables**](Global_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**FLOAT** frame\_time

**Frame\_time** is a [global variable](global_variable "wikilink"),
holding the time passed the last frame. In other words: the difference
in time between the start of the last frame and the current frame.

Doing a bit of physics, we see that:

:   FPS = 1 / frame\_time

Be advised that frame\_time is in milliseconds accurate, so it can be 0
at times, so one might prevent such a case from happening:

:   FPS = 1 / ( frame\_time + (frame\_time==0)\*0.0001 );

This gives a sort of FPS which is accurate every frame.

Example
-------

Display how long the program has been running, by use of frame\_time:

    Program timers;
    Private
        int ft; // Help variable
        int i;  // how long the program has been running in 1/100s
        float f; // how long the program has been running in 1/100s
    Begin

        set_mode(320,400,8);
        write_int   (0,0,300,0,&timer);
        write_int   (0,0,310,0,&i);
        write_float (0,0,320,0,&f);

        Repeat

            // Calculate how long the program has been running in 1/100s without a float
            ft %= 10; // keep the milliseconds from last time
            ft += frame_time*1000; // add the last passed time to it in milliseconds
            i += ft/10; // add it to the integer without the milliseconds

            // Calculate how long the program has been running in 1/100s with a float
            f+=frame_time*100;

            frame;
        Until(key(_ESC))

    End

Used in example: [set\_mode](set_mode "wikilink")(),
[write\_int](write_int "wikilink")(),
[write\_float](write_float "wikilink")(), [key](key "wikilink")(),
[timer](timer "wikilink")

Let a [process](process "wikilink") wait for a certain time by calling
this function:

    Function int wait(float seconds)
    Begin
        While( (seconds-=frame_time) > 0 ) frame; End
        return -seconds;
    End

This can be done with a timer too, as is displayed
[here](timer#Example "wikilink").
