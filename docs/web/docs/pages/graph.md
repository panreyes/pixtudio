<category:variables> <category:predefined>

[**Up to Local Variables**](Local_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** graph = 0

Graph is a predefined local variable which holds the
[GraphID](GraphID "wikilink") of the process. A
[graphic](graphic "wikilink") can be assigned to the process by
assigning the [GraphID](GraphID "wikilink") of that graphic to graph.
Assign 0 to the local variable graph to have the process display no
graph. Keep in mind that this doesn't free the memory used by the
graphic; to free it, use [unload\_map](unload_map "wikilink")().

Example
-------

    Process cyan_graphic()
    Begin
        graph = new_map(100,100,8);   // create a new 100x100x8 map.
        map_clear(0,graph,rgb(0,255,255));   // clear it cyan-colored
        x = 100;     //Position the graphic 100 pixels
        y = 100;     //from the top and left of the screen
        Repeat
            frame;
        Until(key(_ESC))
    End

Used in example: [new\_map](new_map "wikilink")(),
[map\_clear](map_clear "wikilink")(), [graphic](graphic "wikilink"),
[x](x "wikilink"), [y](y "wikilink")

[Category:local variables](Category:local_variables "wikilink")
