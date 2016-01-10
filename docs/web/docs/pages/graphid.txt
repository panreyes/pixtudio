Definition
----------

**GraphID**

A GraphID is an identifier associated with a certain
[graphic](graphic "wikilink") in the [file](file "wikilink") (FPG)
specified by a [FileID](FileID "wikilink").

GraphID's can be used to point to certain graphics in certain files
(FPGs), for displaying them onscreen, or manipulating them in another
way, like [put](put "wikilink")() or [map\_put](map_put "wikilink")().
They can also be used to specify the graphic of a
[process](process "wikilink") or [function](function "wikilink"), by
assigning the GraphID to the [local variable](local_variable "wikilink")
[graph](graph "wikilink"). This will make the process use the graphic in
the file (FPG), specified by the local variable [file](file "wikilink"),
at the position specified by the local variable graph.

Example
-------

    Program files;
    Global
        int file_id;
    Begin

        // Load FPG
        file_id = load_fpg("example.fpg");

        // Set locals for display of graph
        file = file_id;
        graph = 1;
        x = y = 50;

        Repeat
            frame;
        Until(key(_frame))

    End

Used in example: [load\_fpg](load_fpg "wikilink")(),
[key](key "wikilink")(), [file](file "wikilink"),
[graph](graph "wikilink")

<Category:general>
