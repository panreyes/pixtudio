Definition
----------

**STRING** chr ( &lt;**BYTE** ASCIIvalue&gt; )

Returns the character associated with *ASCIIvalue*.

Parameters
----------

  --------------------- -------------------------------------------------------------------------
  **BYTE** ASCIIvalue   - The [ASCII](ascii "wikilink") value of which the character is wanted.
  --------------------- -------------------------------------------------------------------------

Returns
-------

**STRING** : The character associated with *ASCIIvalue*.

Example
-------

    Program chars;
    Begin

        write(0,0, 0,0,chr(65));
        write(0,0,10,0,chr(67));

        Repeat
            frame;
        Until(key(_esc))

    End

Used in example: [write](write "wikilink")(), [key](key "wikilink")()

<Category:functions> <Category:strings> <Category:mod_string>
