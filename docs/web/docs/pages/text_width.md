Definition
----------

**INT** text\_width ( &lt;**INT** fontID&gt; , &lt;**STRING** text&gt; )

Calculates the width in pixels of the specified text in the specified
[font](font "wikilink").

Parameters
----------

  ----------------- ---------------------------------------------------------------------------------------------------
  **INT** FontID    - [FontID](FontID "wikilink") of the font for which the width of the text will be the calculated.
  **STRING** text   - The text of which the width will be calculated.
  ----------------- ---------------------------------------------------------------------------------------------------

Returns
-------

**INT** : The width in pixels of the text in the font.

  ------- ------------------------------------------------
  0       - Invalid or no text; invalid font.
  &gt;0   - The width in pixels of the text in the font.
  ------- ------------------------------------------------

See also
--------

-   [text\_height](text_height "wikilink")()

<Category:functions> <Category:texts> <Category:mod_text>
