<category:general> <category:texts>

Definition
----------

**TextID**

TextID is an identifier associated with a certain
[text](text "wikilink"). It is returned by various [text
functions](Functioncategory:Texts "wikilink"), like
[write](write "wikilink")(), [write\_int](write_int "wikilink")(),
[write\_string](write_string "wikilink")(),
[write\_float](write_float "wikilink")() and
[move\_text](move_text "wikilink")().

When a dynamic text is created, it has the color last set by
[set\_text\_color](set_text_color "wikilink")(). By default this is
white ([rgb](rgb "wikilink")(255,255,255)). Its Z value is equal to
[text\_z](text_z "wikilink") at the moment of creation, which is -256 by
default.

To move the dynamic text associated with a TextID, use
[move\_text](move_text "wikilink")(). To delete the text, use
[delete\_text](delete_text "wikilink")(). There can be a total of 512
dynamic texts on screen simultaneously.

See also
--------

-   [Text](Text "wikilink")
-   [Text functions](Functioncategory:Texts "wikilink")

