<category:variables> <category:predefined> [category:local
variables](category:local_variables "wikilink") <category:librender>

[**Up to Local Variables**](Local_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** size = 100

Size is a predefined [local variable](local_variable "wikilink") that
can be used to stretch or compress a graphic, equally along the
horizontal axis and vertical axis. It is defined as a percentage of the
original graphic size. The graphics's center will remain at the drawing
coordinates when the graphic is drawn.

This variable only has effect for the appearance of a
[process](process "wikilink")' [graphic](graphic "wikilink") when its
local variables [size\_x](size_x "wikilink") and
[size\_y](size_y "wikilink") are both `100`. When either is not equal to
`100`, [size](size "wikilink") doesn't affect the appearance of the
graphic.

Example
-------

To make the [graphic](graphic "wikilink") of a
[process](process "wikilink") continually stretch:

    Process Main()
    Begin
        graph = new_map(50,50,8); // Create a new graphic
        x = 100;                  // Position the graphic 100 pixels
        y = 100;                  // from the top and left of the screen
        Loop
            size += 1;            // Increase the height and width of the graphic by 1 percent each frame.
            frame;
        End
    OnExit
        unload_map(0,graph);
    End

Used in example: [new\_map](new_map "wikilink")(), [x](x "wikilink"),
[y](y "wikilink"), [size](size "wikilink"),
[unload\_map](unload_map "wikilink")()

See also
--------

-   [size\_x](size_x "wikilink")
-   [size\_y](size_y "wikilink")

