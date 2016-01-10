Definition
----------

**INT** get\_glyph ( &lt;**INT** fontID&gt; , &lt;**INT** glyphID&gt; )

Creates a new [graphic](graphic "wikilink") containing the specified
[glyph](glyph "wikilink") of the specified [font](font "wikilink").

The previous name [get\_glyph](get_glyph "wikilink")() is deprecated.

Parameters
----------

  ----------------- -------------------------------------------------------------------------
  **INT** fontID    - The [fontID](fontID "wikilink") of the font the glyph is wanted.
  **INT** glyphID   - The [glyphID](glyphID "wikilink") of the glyph in the specified font.
  ----------------- -------------------------------------------------------------------------

Returns
-------

**INT** : [GraphID](GraphID "wikilink")

  ------- ----------------------------------------------------------
  0       - Invalid font; Invalid glyph; could not create graphic;
  &gt;0   - The graphID of the graphic containing the glyph.
  ------- ----------------------------------------------------------

See also
--------

-   [set\_glyph](set_glyph "wikilink")()

<Category:functions> <Category:fonts> <Category:mod_map>
