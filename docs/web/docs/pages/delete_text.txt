Definition
----------

**INT** delete\_text ( &lt;**INT** TextID&gt; )

Deletes a certain [text](text "wikilink") from the screen.

Parameters
----------

  ---------------- -----------------------------------------------------------------------------
  **INT** TextID   - [TextID](TextID "wikilink") of the [text](text "wikilink") to be deleted.
  ---------------- -----------------------------------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Notes
-----

[Delete\_text](Delete_text "wikilink")([ALL\_TEXT](ALL_TEXT "wikilink"))
deletes all text from the screen.

Example
-------

    Program test;
    Global
        my_text;
    Begin
        my_text = write(0,320/2,200/2,4,"Press space to delete this.");
        Repeat
            if (key(_space))
                if(my_text>0)
                    delete_text(my_text);
                    my_text = 0;
                end
            end
            Frame;
        Until(key(_esc))
    End

Used in example: [write](write "wikilink")(), [key](key "wikilink")(),
[textID](textID "wikilink")

This will result in something like:\
![](delete_text.jpg "fig:delete_text.jpg")

<Category:functions> <Category:texts> <Category:mod_text>
