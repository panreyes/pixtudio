Definition
----------

**INT** center\_set ( &lt;**INT** FileID&gt; , &lt;**INT** GraphID&gt; ,
&lt;**INT** x&gt; , &lt;**INT** y&gt;)

Allows you to change the center of a [graphic](graphic "wikilink").

This function changes a graphic's center pixel, which is the pixel that
is located on screen at the [graph](graph "wikilink")'s x and y
coordinates. So changing this will influence the position on the screen.

The previous name [set\_center](set_center "wikilink")() is deprecated.

Parameters
----------

  ----------------- ---------------------------------------------------------------------------------------------------
  **INT** FileID    - The [FileID](FileID "wikilink") of the [file](file "wikilink") containing the graphic
  **INT** GraphID   - The [GraphID](GraphID "wikilink") of the [graphic](graphic "wikilink") to change the center of.
  **INT** x         - The new horizontal center [coordinate](coordinate "wikilink") of the graphic.
  **INT** y         - The new vertical center [coordinate](coordinate "wikilink") of the graphic.
  ----------------- ---------------------------------------------------------------------------------------------------

Returns
-------

**INT** : Successrate

  ---- ------------------------------------
  -1   - Specified graphic is invalid.
  1    - The center was set successfully.
  ---- ------------------------------------

Notes
-----

You set the position of [control point](control_point "wikilink") 0 in
the graphic. This control point acts as the graphic's
[coordinate](coordinate "wikilink") on screen. For example, if a
graphic's center is set to 0,0 , then the upper left pixel of the
graphic will be placed on screen at the graphic's coordinates. If no
center is set, by default control point 0 is set to the graphics true
geometric center.

Another key feature is that the graphic will rotate around its center,
as set by this function, and any horizontal or vertical mirrors (set
with [flags](flags "wikilink")) will flip at this point.

When a graphic is used as a [mouse](mouse "wikilink") pointer, its
center point is used for the mouse tip. Most mouse cursors in [Operating
Systems](Operating_System "wikilink") have a mouse with the tip in the
upper left of the image. Therefore, for a standard mouse pointer in
Bennu, you will have to set the center at 0,0 to enable mouse accuracy.

Example
-------

    import "mod_map"
    import "mod_text"
    import "mod_key"

    Process Main()
    Begin
        graph=png_load("set_center.png");    //Loads a 128x128 image as the graphic
        x=160;
        y=100;                               //Places the graphic in the centre of the screen
        write(0,0,0,0,"Press [1] to set center to 0,0");
        write(0,0,0,10,"Press [2] to set center to 64,64");
        Loop
            if(key(_1))   
                center_set(0,graph,0,0);
            end
            if(key(_2))
                center_set(0,graph,64,64);
            end
            angle+=100;                      //Rotates the graphic constantly
            frame;
        End
    End

Used in example: [graph](graph "wikilink"),
[png\_load](png_load "wikilink")(), [key](key "wikilink")(),
[write](write "wikilink")(), [center\_set](center_set "wikilink")()

File(s) used in example:
[set\_center.png](Media:set_center.png "wikilink")

<Category:functions> <Category:mod_map>
