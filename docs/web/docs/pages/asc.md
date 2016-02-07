Definition
----------

**BYTE** asc ( &lt;**STRING** character&gt; )

Returns the [ASCII](ascii "wikilink") value of the first character of
the string *character*.

Parameters
----------

  ---------------------- --------------------------------------------------------------------------------
  **STRING** character   - The string of which the ASCII value of the first character will be returned.
  ---------------------- --------------------------------------------------------------------------------

Returns
-------

**BYTE** : The ASCII value of the first character of the string
*character*.

Example
-------

    Program asciis;
    Begin

        write(0,0, 0,0,asc("A"));
        write(0,0,10,0,asc("CAT"));

        Repeat
            frame;
        Until(key(_esc))

    End

Used in example: [write](write "wikilink")(), [key](key "wikilink")()

<Category:functions> <Category:strings> <Category:mod_string>
