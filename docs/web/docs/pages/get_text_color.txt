Definition
----------

**INT** get\_text\_color( \[&lt;**INT** textID&gt;\] )

Gets the current text [color](color "wikilink") (the
[color](color "wikilink") where texts will be written in).

Parameters
----------

**INT** textID: The identification code of the text (optional parameter,
introduced in version rc282).

Returns
-------

**INT**: [color](color "wikilink") the text will be written in, or 0
when there is a problem.

Notes
-----

None.

Errors
------

*<If someone knows, please edit!>*

Example
-------

    Program test;
    Global
        my_text;
        text_color;
    Begin

        set_text_color( rgb(192,112,0) );
        text_color = get_text_color();

        write    (0,320/2    ,200/2,4,"The color of this text is:");
        write_int(0,320/2+100,200/2,4,&text_color);

        Repeat
            frame;
        Until(key(_ESC))

    End

Used in example: [set\_text\_color](set_text_color "wikilink")(),
[write](write "wikilink")(), [write\_int](write_int "wikilink")(),
[key](key "wikilink")()

This will result in something like:\
![](get_text_color.png "fig:get_text_color.png")

<Category:functions> <Category:texts> <Category:mod_text>
