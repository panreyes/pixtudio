<category:variables> <category:predefined> [category:local
variables](category:local_variables "wikilink") <category:librender>

[**Up to Local Variables**](Local_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** angle = 0

**Angle** is a predefined [local variable](local_variable "wikilink")
which holds the angle (measured in 1/1000 of a degree) at which the
[graphic](graphic "wikilink") of that [process](process "wikilink")
(assigned by the local variable [graph](graph "wikilink")) will be
drawn. It also influences the result of the
[function](function "wikilink") [advance](advance "wikilink")().

An angle of 0 means to the right, 90000 means up, 180000 means left and
270000 and -90000 mean down.

Example
-------

To make the graphic of a process spin:

    import "mod_grproc"
    import "mod_map"
    import "mod_wm" // for exit_status
    import "mod_key" // for key()

    Process Main()
    Begin
        graph = map_new(100,100,8);  //Create a cyan square and assign it to 'graph'
        map_clear(0,graph,rgb(0,255,255));
        x = 160;     //Position the graphic's center
        y = 100;     //in the center of the screen
        Repeat
            angle += 1000;    //increase the angle of graphic by 1000 each frame. 1000 = 1 degree.
            frame;
        Until(key(_ESC) || exit_status)
    OnExit
        map_unload(0,graph);
    End

Used in example: [map\_new](map_new "wikilink")(),
[map\_clear](map_clear "wikilink")(), [rgb](rgb "wikilink")(),
[map\_unload](map_unload "wikilink")(), [key](key "wikilink")(),
[exit\_status](exit_status "wikilink"), [graph](graph "wikilink"),
[x](x "wikilink"), [y](y "wikilink"), [angle](angle "wikilink")

This process will spin the cyan square by 1 degree each frame.
