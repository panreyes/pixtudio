Definition
----------

**FontID**

A FontID is an identifier associated with a certain
[font](font "wikilink"). It is returned by functions that load fonts,
for example [load\_fnt](load_fnt "wikilink")(). You can use the FontID
in [functions](Function "wikilink") to specify the font used in the
writing of texts like [write](write "wikilink")(),
[write\_int](write_int "wikilink")(),
[write\_float](write_float "wikilink")(),
[write\_string](write_string "wikilink")(),
[write\_var](write_var "wikilink")() and
[write\_in\_map](write_in_map "wikilink")().

Notes
-----

Font "0" is the built-in font, and can be used in functions as well.

Example
-------

    import "mod_text"
    import "mod_key"

    Global
        My_font;
    End

    Process Main()
    Begin

        //Using the built-in font:
        My_font=0;
        Write(My_font,320/2,200/2,4,"Game programming is awesome!");

        Repeat
            frame;
        Until(key(_ESC))
    End

Used in example: [write](write "wikilink")(), [key](key "wikilink")()

This will result in something like:\
![](FontID.png "fig:FontID.png")

<Category:general> <Category:Texts>
