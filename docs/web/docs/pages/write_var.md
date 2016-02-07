Syntax
------

**INT** write\_var ( &lt;**INT** fontID&gt; , &lt;**INT** x&gt; ,
&lt;**INT** y&gt; , \[&lt;**INT** z&gt;\] , &lt;**INT** alignment&gt; ,
&lt;**VARSPACE** var&gt; )

Description
-----------

Writes a variable of any kind to the screen, which will be automatically
updated when the value of the variable changes. The variable will remain
on the screen until deleted with
[delete\_text](delete_text "wikilink")().

Parameters
----------

  ------------------- ------------------------------------------------------------------------
  **INT** fontID      - The [FontID](FontID "wikilink") of the font to be used for the text.
  **INT** x           - The X coordinate of the text.
  **INT** y           - The Y coordinate of the text.
  **INT** z           - The depthplane of the text (optional, introduced in version rc282).
  **INT** alignment   - The type of [alignment](Alignment_modes "wikilink").
  **VARSPACE** var    - The name of [any variable](Varspace "wikilink").
  ------------------- ------------------------------------------------------------------------

Returns
-------

**INT** : [TextID](TextID "wikilink")

  -------- ------------------------------------------------
  -1       - Error.
  &gt;=0   - The [TextID](TextID "wikilink") of the text.
  -------- ------------------------------------------------

Notes
-----

Please note that for the [varspace](Varspace "wikilink") **var**
parameter *no* pointer should be filled out, while
[write\_int](write_int "wikilink")()/[write\_string](write_string "wikilink")()/[write\_float](write_float "wikilink")()
*do* require a pointer.

There is a limit of 511 texts to simultaneously exist on the screen. The
program will crash with an error when this number is reached.

The text depth can be changed by adjusting the global variable
[text\_z](text_z "wikilink").

Instead of [write\_var](write_var "wikilink")(),
[write\_int](write_int "wikilink")() could be used to write an
[int](int "wikilink") to the screen,
[write\_string](write_string "wikilink")() for a
[string](string "wikilink"), [write\_float](write_float "wikilink")()
for a [float](float "wikilink").

Errors
------

  ------------------------- -------------------------------------------
  Too many texts onscreen   - There are too many texts on the screen.
  ------------------------- -------------------------------------------

Example
-------

    import "mod_text"
    import "mod_key"

    Global
        my_integer=0;
        string my_string="Bennu Game Development";
    End

    Process Main()
    Begin

        write_var(0,0,0,0,my_string);
        write_var(0,320/2,200/2,4,my_integer);

        Repeat
            my_integer=rand(1,1000);
            frame;
        Until(key(_ESC))

    End

Used in example: [write\_var](write_var "wikilink")(),
[rand](rand "wikilink")(), [key](key "wikilink")()

This will result in something like:\
![](Write_var.png "fig:Write_var.png")

<Category:functions> <Category:texts> <Category:mod_text>
