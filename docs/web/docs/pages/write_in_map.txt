Definition
----------

**INT** write\_in\_map ( &lt;**INT** fontID&gt; , &lt;**STRING**
text&gt; , &lt;**INT** alignment&gt; )

Creates a new [graphic](graphic "wikilink") in memory with the given
text on it (without borders around the text) and puts it in the [system
file](system_file "wikilink").

Parameters
----------

  ------------------- ------------------------------------------------------------------------
  **INT** fontID      - The [FontID](FontID "wikilink") of the font to be used for the text.
  **STRING** text     - The text to be used.
  **INT** alignment   - The type of [alignment](Alignment_modes "wikilink").
  ------------------- ------------------------------------------------------------------------

Returns
-------

**INT** : [GraphID](GraphID "wikilink")

  ---- -----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  0    - Error. The text could not be obtained or was empty.
  !0   - The [GraphID](GraphID "wikilink") of the [graphic](graphic "wikilink") of the generated [graphic](graphic "wikilink") in the [system file](system_file "wikilink").
  ---- -----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Notes
-----

This function creates a [graphic](graphic "wikilink") containing the
specified [font](font "wikilink"), with a [width](width "wikilink") and
[height](height "wikilink") determined by the physical size of the text;
the graphic's size will fit the text exactly to the pixel. The graphic
will be stored in memory with [FileID](FileID "wikilink") 0 (using the
[system file](system_file "wikilink")), and can be obtained at any time
by calling its [GraphID](GraphID "wikilink"). The graphic can also be
unloaded from memory by using [unload\_map](unload_map "wikilink")().

The centre of the graph ([control point](control_point "wikilink") 0) is
given according to the given [alignment](alignment "wikilink"). This
gives added functionality of being able to place the graph like texts,
yet also using [flags](flags "wikilink"), [alpha](alpha "wikilink"),
rotation, [collision](collision "wikilink")(), etc.

Processes can adopt the graphic containing the text, or it can be
displayed with some [maps functions](Functioncategory:Maps "wikilink"),
creating a very handy function.

Errors
------

  -------------- ----------------------------------------------------
  Invalid font   - The specified font does not exist or is invalid.
  -------------- ----------------------------------------------------

Example
-------

    Program example;
    Begin
        Set_text_color(rgb(222,195,140));
        graph=write_in_map(0,"Game programming is awesome!",4);
        repeat
            x=mouse.x;
            y=mouse.y;
        frame;
        until(key(_esc))
    End

Used in example: [set\_text\_color](set_text_color "wikilink")(),
[rgb](rgb "wikilink")(), [key](key "wikilink")(), [x](x "wikilink"),
[y](y "wikilink"), [mouse](mouse "wikilink")

This will result in something like:\
![](Write_in_map.png "fig:Write_in_map.png")

<Category:functions> <Category:texts> <Category:mod_text>
