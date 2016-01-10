Definition
----------

**INT** xput ( &lt;**INT** fileID&gt; , &lt;**INT** GraphID&gt; ,
&lt;**INT** x&gt; , &lt;**INT** y&gt; , &lt;**INT** angle&gt; ,
&lt;**INT** size&gt; , &lt;**INT** blitflags&gt; , &lt;**INT**
region&gt; )

Draws ([blits](blit "wikilink")) a [graphic](graphic "wikilink") onto
the [background](background "wikilink").

If the advanced parameters aren't needed, [put](put "wikilink")() can be
used.

Parameters
----------

  ------------------- ----------------------------------------------------------------------------------------------------------------------------
  **INT** fileID      - The [fileID](fileID "wikilink") of the [file](file "wikilink") that holds the graphics.
  **INT** graphID     - The [graphID](graphID "wikilink") of the [graphic](graphic "wikilink") to draw with.
  **INT** x           - Where on the background graphic's x-axis to put the graphic.
  **INT** y           - Where on the background graphic's y-axis to put the graphic.
  **INT** angle       - What [angle](angle "wikilink") to draw the graphic at.
  **INT** size        - What [size](size "wikilink") to draw the graphic at.
  **INT** blitflags   - What [blit flags](blit_flags "wikilink") to draw the graphic with.
  **INT** regionID    - The [regionID](regionID "wikilink") of the [region](region "wikilink") in which the graphic is only allowed to be drawn.
  ------------------- ----------------------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Notes
-----

The x and y parameters denote where to draw the graphic, that is, where
the center of the to be drawn graphic will be. Blit flags can be used to
give the drawing (blitting) a special effect.

When angle is 0 and size is 100, the speed is greater, because the graph
doesn't need rotating or scaling.

Errors
------

  ------------------------- -----------------------------------------------------------------------
  Unsupported color depth   - The graphic's color depth is greater than the background graphic's.
  ------------------------- -----------------------------------------------------------------------

<Category:functions> <Category:screen> <Category:mod_screen>
