<category:variables> <category:predefined> [category:local
variables](category:local_variables "wikilink") <category:librender>

[**Up to Local Variables**](Local_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** size\_y = 100

Size\_y is a predefined [local variable](local_variable "wikilink") that
can be used to stretch or compress a graphic along its vertical axis. It
is defined as a percentage of the original graphic size. The graphics's
center will remain at the drawing coordinates when the graphic is drawn.

When either [size\_x](size_x "wikilink") or [size\_y](size_y "wikilink")
of a [process](process "wikilink") are unequal to \[code\]100\[/code\],
that process' [size](size "wikilink") has no effect.

Example
-------

To make the [graphic](graphic "wikilink") of a
[process](process "wikilink") continually stretch vertically:

    Process Main()
    Begin
        graph = new_map(50,50,8); // Create a new graphic
        x = 100;                  // Position the graphic 100 pixels
        y = 100;                  // from the top and left of the screen
        Loop
            size_y += 1;          // Increase the height of the graphic by 1 pixel each frame.
            frame;
        End
    OnExit
        unload_map(0,graph);
    End

Used in example: [new\_map](new_map "wikilink")(), \[\[x\],
[y](y "wikilink"), [size\_y](size_y "wikilink"),
[unload\_map](unload_map "wikilink")()

See also
--------

-   [size](size "wikilink")
-   [size\_x](size_x "wikilink")

