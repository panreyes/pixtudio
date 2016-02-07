Definition
----------

**INT** map\_block\_copy ( &lt;**INT** fileID&gt; , &lt;**INT**
destinationGraphID&gt; , &lt;**INT** destinationX&gt; , &lt;**INT**
destinationY&gt; , &lt;**INT** originGraphID&gt; , &lt;**INT** x&gt; ,
&lt;**INT** y&gt; , &lt;**INT** width&gt; , &lt;**INT** height&gt;,
&lt;**INT** blitflags&gt; )

Draws ([blits](blit "wikilink")) a rectangular block from one
[graphic](graphic "wikilink") onto another graphic.

If the entire graphic is to be blitted, [map\_put](map_put "wikilink")()
or [map\_xput](map_xput "wikilink")() can be used.

Parameters
----------

  ---------------------------- ------------------------------------------------------------------------------------------------------------------
  **INT** fileID               - The [fileID](fileID "wikilink") of the [file](file "wikilink") that holds the destination and origin graphics.
  **INT** destinationGraphID   - The [graphID](graphID "wikilink") of the [graphic](graphic "wikilink") to draw on.
  **INT** destinationX         - Where on the destination graph's x-axis to put the block.
  **INT** destinationY         - Where on the destination graph's y-axis to put the block.
  **INT** originGraphID        - The [graphID](graphID "wikilink") of the [graphic](graphic "wikilink") to draw with.
  **INT** x                    - The x-coordinate of the upperleft corner of the origin block.
  **INT** y                    - The y-coordinate of the upperleft corner of the origin block.
  **INT** width                - The width of the block in pixels.
  **INT** height               - The height of the block in pixels.
  **INT** blitflags            - What [blit flags](blit_flags "wikilink") to draw the graphic with.
  ---------------------------- ------------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Notes
-----

[Blit flags](Blit_flags "wikilink") can be used to give the drawing
(blitting) a special effect.

Errors
------

  --------------------------- -----------------------------------------------------------------------------
  Invalid origin graph        - The origin graph is invalid.
  Invalid destination graph   - The destination graph is invalid.
  Unsupported color depth     - The origin graphic's color depth is greater than the destination graph's.
  --------------------------- -----------------------------------------------------------------------------

<Category:functions> <Category:maps> <Category:mod_map>
