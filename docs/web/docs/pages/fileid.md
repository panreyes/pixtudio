Definition
----------

**FileID**

A FileID is an identifier associated with a certain
[file](file "wikilink") (FPG). It is returned by
[load\_fpg](load_fpg "wikilink")(), when a file is loaded to memory and
can be used in many [functions](function "wikilink"), wanting a FileID,
for example [map\_put](map_put "wikilink")() or
[start\_scroll](start_scroll "wikilink")(). A FileID can also be
assigned to the [local variable](local_variable "wikilink")
[file](file "wikilink") of a [process](process "wikilink") or function,
which will make the process in question look in that file (FPG) for the
[graphic](graphic "wikilink"), associated with the
[GraphID](GraphID "wikilink") specified by the process'
[graph](graph "wikilink") local variable.

Notes
-----

You can fill out 0 for the [FileID](FileID "wikilink") to target the
[system file](system_file "wikilink"), for
[graphics](graphic "wikilink") with an ID of *1000* or higher, which are
graphics created on the fly.

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
