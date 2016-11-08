Syntax
------

**Frame** \[ **(** &lt;percentage&gt; **)** \] **;**

Description
-----------

The **frame;** command tells the interpreter when a
[process](#process) is done for one game cycle. When the
**frame;** is reached, the screen is updated. If there are several
[processes](#process) running, the screen is updated once
every [process](#process) has reached its **frame;**
statement.

It is commonly used in [loops](#loop) of
[processes](#process) that should do something like moving
around by a certain amount of pixels per game cycle (or per frame).

A possibility is to adjust the amount of cycles to wait. **frame(100);**
would wait one cycle (100%), same as **frame;**. However **frame(200);**
will wait two cycles (200% means the frame statement provides for 200%
frame). So **frame(50);** will wait a half cycle or otherwise said, it
will make a loop run twice per frame.

Example
-------

    Process Main()
    Begin

        square();

        Repeat
            frame;
        Until(key(_ESC))

        exit();

    End

    Process square()
    Begin

        graph = new_map(5,5,16);
        map_clear(0,graph,rgb(255,255,255));

        Loop
            x += 2 * (key(_right)-key(_left));
            frame; //<-vital part
        End

    End

This example [process](#process) would give you a square you
can move around the screen by 2 pixel before it gets showed again,
before the game cycle is over, before the **frame;** happens. If there
would be no **frame;** in the [loop](#loop), it would just run
forever and the interpreter would wait forever for the **frame;**, which
would result in freezing.
