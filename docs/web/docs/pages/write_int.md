Definition
----------

**INT** write\_int ( &lt;**INT** fontID&gt; , &lt;**INT** x&gt; ,
&lt;**INT** y&gt; , \[&lt;**INT** z&gt;\] , &lt;**INT** alignment&gt; ,
&lt;**INT POINTER** var&gt; )

Writes an [integer](Int "wikilink") to the screen, which will be
automatically updated when the value of the integer changes. The integer
will remain on the screen until deleted with
[delete\_text](delete_text "wikilink")().

Parameters
----------

  --------------------- ------------------------------------------------------------------------
  **INT** fontID        - The [FontID](FontID "wikilink") of the font to be used for the text.
  **INT** x             - The X coordinate of the text.
  **INT** y             - The Y coordinate of the text.
  **INT** z             - The depthplane of the text (optional, introduced in version rc282).
  **INT** alignment     - The type of [alignment](Alignment_modes "wikilink").
  **INT POINTER** var   - A [pointer](pointer "wikilink") to an [integer](Int "wikilink").
  --------------------- ------------------------------------------------------------------------

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

Instead of [write\_int](write_int "wikilink")(),
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
        my_integer=0;
    Begin

        write_int(0,320/2,200/2,4,my_integer);

        Repeat
            my_integer=rand(1,1000);
            frame;
        Until(key(_ESC))

    End

Used in example: [rand](rand "wikilink")(), [key](key "wikilink")()

This will result in something like:\
![](Write_int.png "fig:Write_int.png")

<Category:functions> <Category:texts> <Category:mod_text>
