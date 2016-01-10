Definition
----------

**INT** rgbscale ( &lt;**INT** fileID&gt; , &lt;**INT** graphID&gt; ,
&lt;**FLOAT** r&gt; , &lt;**FLOAT** g&gt; , &lt;**FLOAT** b&gt; )

This will convert the specified [graphic](graphic "wikilink") by using
the specified color as a reference. The converted graphic will have only
the specified color and lighter/darker colors; see
[notes](#Notes "wikilink") for the details.

Parameters
----------

  ----------------- -------------------------------------------------------------------------------------------
  **INT** fileID    - The [fileID](fileID "wikilink") of the [file](file "wikilink") that holds the graphics.
  **INT** graphID   - The [graphID](graphID "wikilink") of the [graphic](graphic "wikilink") to convert.
  **FLOAT** r       - The red component of the color to be used for reference.
  **FLOAT** g       - The green component of the color to be used for reference.
  **FLOAT** b       - The blue component of the color to be used for reference.
  ----------------- -------------------------------------------------------------------------------------------

Returns
-------

**INT**

  ---- --------------------
  -1   - Invalid graphic.
  1    - Success.
  ---- --------------------

Notes
-----

The exact formula is:

    for every pixel:
        c = 0.3 * oldpixel_r + 0.59 * oldpixel_g + 0.11 * oldpixel_b
        newpixel_r = r * c;
        newpixel_g = g * c;
        newpixel_b = b * c;

where r,g,b are the specified r,g,b.

Note that `[[rgbscale]](0,map,1,1,1) = [[grayscale]](0,map,0)`, for a
valid graphic (0,map).

<Category:functions> [Category:graphical
effects](Category:graphical_effects "wikilink") <Category:mod_effects>
