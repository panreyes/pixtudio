Definition
----------

**INT** write ( &lt;**INT** fontID&gt; , &lt;**INT** x&gt; , &lt;**INT**
y&gt; , \[&lt;**INT** z&gt;\] , &lt;**INT** alignment&gt; ,
&lt;**STRING** text&gt;)

Puts a dynamic text with a certain font on certain coordinates on the
screen with a certain [alignment](Alignment_modes "wikilink").

Parameters
----------

  ------------------- ------------------------------------------------------------------------
  **INT** fontID      - The [FontID](FontID "wikilink") of the font to be used for the text.
  **INT** x           - The X coordinate of the text.
  **INT** y           - The Y coordinate of the text.
  **INT** z           - The depthplane of the text (optional, introduced in version rc282).
  **INT** alignment   - The type of [alignment](Alignment_modes "wikilink").
  **STRING** text     - The text to be used.
  ------------------- ------------------------------------------------------------------------

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

To write variables to the screen, rather use
[write\_int](write_int "wikilink")(),
[write\_string](write_string "wikilink")(),
[write\_float](write_float "wikilink")() or
[write\_var](write_var "wikilink")() than this command.

To write text on a map you can use the command
[write\_in\_map](write_in_map "wikilink")().

If you write texts with a font and you change any symbol of this font
after, all written texts will be updated using the new changed symbols.

Example
-------

    Program texts;
    Const
        maxtexts = 10;
    Private
        int textid[maxtexts-1];
        string str;
        float flt;
    Begin

        // Set FPS
        set_fps(60,0);

        // Write some texts
        textid[0] = write(0,0,0,0,"FPS:");
        textid[1] = write_int(0,30,0,0,&fps);
        textid[2] = write_string(0,160,95,1,&str);
        textid[3] = write_float(0,160,105,0,&flt);

        // Update the texts until ESC is pressed
        Repeat
            // Notice the texts get updated as the values of str and flt changes.
            // The same goes for the value of fps.
            str = "This program is running for " + timer/100 + " seconds.";
            flt = (float)timer/100;
            frame;
        Until(key(_esc));

        // Delete the texts
        for(x=0; x<maxtexts; x++)
            if(textid[x]!=0)
                delete_text(textid[x]);
            end
        end

    End

Used in example: [set\_fps](set_fps "wikilink")(),
[write\_int](write_int "wikilink")(),
[write\_string](write_string "wikilink")(),
[write\_float](write_float "wikilink")(), [key](key "wikilink")(),
[delete\_text](delete_text "wikilink")(), [array](array "wikilink"),
[fps](fps "wikilink"), [TextID](TextID "wikilink")

This will result in something like:\

<Category:functions> <Category:texts> <Category:mod_text>
