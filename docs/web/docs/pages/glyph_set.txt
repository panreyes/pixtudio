Definition
----------

**INT** glyph\_set ( &lt;**INT** fontID&gt; , &lt;**INT** glyphID&gt; ,
&lt;**INT** fileID&gt; , &lt;**INT** graphID&gt; )

Sets the specified [glyph](glyph "wikilink") of the specified
[font](font "wikilink"). The new glyph will be a copy of the specified
[graphic](graphic "wikilink") and thus it may be freed after the call.

The previous name [set\_glyph](set_glyph "wikilink")() is deprecated.

Parameters
----------

  ----------------- ------------------------------------------------------------------------------------------
  **INT** fontID    - The [fontID](fontID "wikilink") of the font the glyph is to be set.
  **INT** glyphID   - The [glyphID](glyphID "wikilink") of the glyph in the specified font.
  **INT** fileID    - The [fileID](fileID "wikilink") of the [file](file "wikilink") that holds the graphic.
  **INT** graphID   - The [graphID](graphID "wikilink") of the [graphic](graphic "wikilink") to be copied.
  ----------------- ------------------------------------------------------------------------------------------

Returns
-------

**INT** : [false](false "wikilink")

See also
--------

-   [glyph\_get](glyph_get "wikilink")()

<Category:functions> <Category:fonts> <Category:mod_map>
