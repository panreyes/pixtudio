:   *This is about the [filetype](filetypes "wikilink"). Did you mean
    the local variable [file](Local:file "wikilink") or the function
    [file](Function:file "wikilink")()?*

------------------------------------------------------------------------

[**Up to Filetypes**](Filetypes "wikilink")

------------------------------------------------------------------------

Description
-----------

A file is a container for [graphics](graphic "wikilink"), identified by
a non-negative [integer](int "wikilink") (0 or higher). It holds all
information about the contained graphics ([pixels](pixel "wikilink"),
[width](width "wikilink"), [height](height "wikilink"),
[depth](depth "wikilink"), name, etc). Each of these graphics have a
unique identifier inside the file (positive [int](int "wikilink")).

A file can be created for example by loading an [FPG](FPG "wikilink")
(*Fichero Para Gráficos*, meaning "file for graphics") into it, by using
[fpg\_load](fpg_load "wikilink")(), which creates a new file with the
graphics from the loaded FPG and returns a unique identifier. Another
option is to create a new, empty one by using
[fpg\_new](fpg_new "wikilink")(). Don't let the name *fpg*\_new() fool
you: fpg\_new() has nothing to do with the filetype FPG. This is because
the FPG format is only for files and not for internal use. There are
more ways to load graphics into a file.

A file can be used by using the [local
variable](local_variable "wikilink") [file](Local:File "wikilink") or by
using the identifier in the various [functions](functions "wikilink")
with a file parameter.

Don't forget to unload it with [fpg\_unload](fpg_unload "wikilink")()
after use.

Example
-------

    import "mod_map"
    import "mod_grproc"
    import "mod_key"
    import "mod_wm"

    Global
        int file_id;
        int file_id2;
    End

    Process Main()
    Begin

        // Load FPG
        file_id = load_fpg("example.fpg");
        file_id2 = load_fpg("example2.fpg");

        // Set locals for display of graph
        file = file_id;
        graph = 1;
        x = y = 50;
        
        // assign Ship to use example2.fpg
        Ship(300,100,5,file_id2,1); // undefined in this sample
        
        Repeat
            frame;
        Until(key(_ESC)||exit_status)

    End

Used in example: [load\_fpg](load_fpg "wikilink")(),
[key](key "wikilink")(), [x](x "wikilink"), [y](y "wikilink"),
[file](file "wikilink"), [graph](graph "wikilink").
[process](process "wikilink")

Media in example: [example.fpg](Media:example.fpg "wikilink")

Note: nothing will be seen unless you have an [FPG](FPG "wikilink")
"example.fpg" with a [graphic](graphic "wikilink") with ID 1.

<Category:general>
