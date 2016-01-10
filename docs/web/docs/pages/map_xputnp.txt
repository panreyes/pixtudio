Definition
----------

**INT** map\_xputnp ( &lt;**INT** destinationFileID&gt; , &lt;**INT**
destinationGraphID&gt; , &lt;**INT** originFileID&gt; , &lt;**INT**
originGraphID&gt; , &lt;**INT** x&gt; , &lt;**INT** y&gt; , &lt;**INT**
angle&gt; , &lt;**INT** scale\_x&gt; , &lt;**INT** scale\_y&gt; ,
&lt;**INT** blitflags&gt; )

Draws ([blits](blit "wikilink")) a [graphic](graphic "wikilink") onto
another graphic.

If the advanced parameters aren't needed,
[map\_put](map_put "wikilink")() or [map\_xput](map_xput "wikilink")()
can be used.

Parameters
----------

  ---------------------------- ----------------------------------------------------------------------------------------------------------------
  **INT** destinationFileID    - The [fileID](fileID "wikilink") of the [file](file "wikilink") that holds the destination graphic.
  **INT** destinationGraphID   - The [graphID](graphID "wikilink") of the [graphic](graphic "wikilink") to draw on.
  **INT** originFileID         - The [fileID](fileID "wikilink") of the [file](file "wikilink") that holds the origin graphic.
  **INT** originGraphID        - The [graphID](graphID "wikilink") of the [graphic](graphic "wikilink") to draw with.
  **INT** x                    - Where on the destination graph's x-axis to put the graphic.
  **INT** y                    - Where on the destination graph's y-axis to put the graphic.
  **INT** angle                - What [angle](angle "wikilink") to draw the graphic at.
  **INT** scale\_x             - What [size](size "wikilink") to draw the origin graphic's x-axis at (also see [size\_x](size_x "wikilink"))
  **INT** scale\_y             - What [size](size "wikilink") to draw the origin graphic's y-axis at (also see [size\_y](size_y "wikilink")).
  **INT** blitflags            - What [blit flags](blit_flags "wikilink") to draw the graphic with.
  ---------------------------- ----------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Notes
-----

The x and y parameters denote where to draw the graphic, that is, where
the center of the to be drawn [graphic](graphic "wikilink") will be.
[Blit flags](Blit_flags "wikilink") can be used to give the drawing
(blitting) a special effect.

When angle is 0 and size is 100, the speed is greater, because the
graphic doesn't need rotating or scaling.

Errors
------

  ------------------------- -----------------------------------------------------------------------------
  Unsupported color depth   - The origin graphic's color depth is greater than the destination graph's.
  ------------------------- -----------------------------------------------------------------------------

Example
-------

    import "mod_video"
    import "mod_map"
    import "mod_wm"

    Process Main()
    Global
        int destgraph;
        int origgraph;
    Begin

        // Set the mode to 16bit and some resolution
        set_mode(320,200,16);

        // Makes the destination graphic a red square
        destgraph=new_map(100,100,16);
        map_clear(0,destgraph,rgb(255,0,0));

        // Makes the origin graphic a blue square
        origgraph=new_map(100,100,16);
        map_clear(0,origgraph,rgb(0,0,255));

        // Draws the blue square on the center of the red square transparently,
        // at a random angle and a random size
        map_xputnp(0,destgraph,0,origgraph,50,50,rand(-180000,180000),rand(50,150),rand(50,150),4);
        map_xputnp(0,destgraph,0,origgraph,50,50,rand(-180000,180000),rand(50,150),rand(50,150),4);

        // Shows the final graph
        put(0,destgraph,160,100);

        Repeat
             frame;
        Until(exit_status)

    End

Used in example: [set\_mode](set_mode "wikilink")(),
[new\_map](new_map "wikilink")(), [map\_clear](map_clear "wikilink")(),
[map\_xputnp](map_xputnp "wikilink")(), [put](put "wikilink")(),
[exit\_status](exit_status "wikilink"), [blit
flags](blit_flags "wikilink")

This will result in something like:

<Category:functions> <Category:maps> <Category:mod_map>
