Syntax
------

**INT** write\_string ( &lt;**INT** fontID&gt; , &lt;**INT** x&gt; ,
&lt;**INT** y&gt; , &lt;**INT** alignment&gt; , &lt;**STRING POINTER**
var&gt; )

Description
-----------

Writes a [string](string "wikilink") to the screen, which will be
automatically updated when the value of the string changes. The string
will remain on the screen until deleted with
[delete\_text](delete_text "wikilink")().

Parameters
----------

  ------------------------ ------------------------------------------------------------------------
  **INT** fontID           - The [FontID](FontID "wikilink") of the font to be used for the text.
  **INT** x                - The X coordinate of the text.
  **INT** y                - The Y coordinate of the text.
  **INT** alignment        - The type of [alignment](Alignment_modes "wikilink").
  **STRING POINTER** var   - A [pointer](pointer "wikilink") to a [string](string "wikilink").
  ------------------------ ------------------------------------------------------------------------

Returns
-------

**INT** : [TextID](TextID "wikilink")

  -------- -------------------------------------------------------
  -1       - Error. The text could not be obtained or was empty.
  &gt;=0   - The [TextID](TextID "wikilink") of the text.
  -------- -------------------------------------------------------

Notes
-----

There is a limit of 511 texts to simultaneously exist on the screen. The
program will crash with an error when this number is reached.

The text depth can be changed by adjusting the global variable
[text\_z](text_z "wikilink").

Instead of [write\_string](write_string "wikilink")(),
[write\_var](write_var "wikilink")() can be used for the same purpose,
which is a more general function that allows you to write variables of
any type to the screen.

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
        string my_string="Bennu Game Development";
    End
    Process Main()
    Begin

        write_string(0,320/2,200/2,4,&my_string);

        Repeat
            frame;
        Until(key(_ESC))

    End

Used in example: [write\_string](write_string "wikilink")(),
[key](key "wikilink")()

This will result in something like:\
![](Write_string.png "fig:Write_string.png")

<Category:functions> <Category:texts> <Category:mod_text>
