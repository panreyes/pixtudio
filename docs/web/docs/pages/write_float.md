Definition
----------

**INT** write\_float ( &lt;**INT** fontID&gt; , &lt;**INT** x&gt; ,
&lt;**INT** y&gt; , \[&lt;**INT** z&gt;\] , &lt;**INT** alignment&gt; ,
&lt;**FLOAT POINTER** var&gt; )

Writes a [floating point variable](float "wikilink") to the screen,
which will be automatically updated when the value of the variable
changes. The floating point variable will remain on the screen until
deleted with [delete\_text](delete_text "wikilink")().

Parameters
----------

  ----------------------- -------------------------------------------------------------------------------------
  **INT** fontID          - The [FontID](FontID "wikilink") of the font to be used for the text.
  **INT** x               - The X coordinate of the text.
  **INT** y               - The Y coordinate of the text.
  **INT** z               - The depthplane of the text (optional, introduced in version rc282).
  **INT** alignment       - The type of [alignment](Alignment_modes "wikilink").
  **FLOAT POINTER** var   - A [pointer](pointer "wikilink") to a [floating point variable](float "wikilink").
  ----------------------- -------------------------------------------------------------------------------------

Returns
-------

**INT** : [TextID](TextID "wikilink")

  -------- ------------------------------------------------
  -1       - Error.
  &gt;=0   - The [TextID](TextID "wikilink") of the text.
  -------- ------------------------------------------------

Notes
-----

There is a limit of 511 texts to simultaneously exist on the screen. The
program will crash with an error when this number is reached.

The text depth can be changed by adjusting the global variable
[text\_z](text_z "wikilink").

Instead of [write\_float](write_float "wikilink")(),
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

    Program test;
    Private
        float my_float=3.14159265;
    Begin

        write_float(0,320/2,200/2,4,&my_float);

        Repeat
            Frame;
        Until(key(_ESC))

    End

This will result in something like:\
![](Write_float.png "fig:Write_float.png")

<Category:functions> <Category:texts> <Category:mod_text>
