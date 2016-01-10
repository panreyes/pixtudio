Definition
----------

**INT** map\_get\_pixel ( &lt;**INT** fileID&gt; , &lt;**INT**
graphID&gt; , &lt;**INT** x&gt; , &lt;**INT** y&gt; )

Returns the [color](color "wikilink") on the specified
[graphic](graphic "wikilink") of the specified
[pixel](pixel "wikilink").

Parameters
----------

  ----------------- -------------------------------------------------------------------------------------------------
  **INT** fileID    - The [fileID](fileID "wikilink") of the [file](file "wikilink") that holds the graphic.
  **INT** graphID   - The [graphID](graphID "wikilink") of the [graphic](graphic "wikilink") to get the pixel from.
  **INT** x         - The X-coordinate of the [pixel](pixel "wikilink") the color is wanted.
  **INT** y         - The Y-coordinate of the [pixel](pixel "wikilink") the color is wanted.
  ----------------- -------------------------------------------------------------------------------------------------

Returns
-------

**INT** : The color

  ----- --------------------------------------------------------------------------------------------------------------------------
  -1    - Error: invalid map; invalid; invalid pixel; invalid color depth of map. Note: in 32bit graphs this can be a color too.
  !-1   - The color.
  ----- --------------------------------------------------------------------------------------------------------------------------

<Category:functions> <Category:maps> <Category:mod_draw>
<Category:mod_map>
