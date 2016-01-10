<category:variables> <category:predefined> [category:global
variables](category:global_variables "wikilink") <category:time>
<category:mod_timers>

[**Up to Global Variables**](Global_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT\[9\]** timer

**Timer** is a [global variable](global_variable "wikilink"), holding
ten integers. Each [frame](frame "wikilink") a certain value is added to
all of them. This value is the difference in time between the start of
the last frame and the current frame, in 1/100 seconds.

So when all the timers are never altered, their values will be 1234 when
the program has been running for about 12.34 seconds.

Examples
--------

### Display how long the program has been running

    import "mod_timers"
    import "mod_key"
    import "mod_text"

    Process Main()
    Begin

        write_int(0,0,100,0,&timer[0]);

        Repeat
            frame;
        Until(key(_ESC))

    End

Used in example: [write\_int](write_int "wikilink")(),
[key](key "wikilink")(), [timer](timer "wikilink")

This can be done more accurately with the use of
[frame\_time](frame_time "wikilink"), which is in milliseconds.

### Let a [process](process "wikilink") wait for a certain time by calling this function

    Function int wait(int t)
    Begin
        t += timer[0];
        While(timer[0]<t) frame; End
        return t-timer[0];
    End

This can be done without a timer too, as is displayed
[here](frame_time#Example "wikilink").
