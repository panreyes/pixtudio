Definition
----------

**INT** text\_height ( &lt;**INT** fontID&gt; , &lt;**STRING** text&gt;
)

Calculates the height in pixels of the specified text in the specified
[font](font "wikilink").

Parameters
----------

  ----------------- ----------------------------------------------------------------------------------------------------
  **INT** FontID    - [FontID](FontID "wikilink") of the font for which the height of the text will be the calculated.
  **STRING** text   - The text of which the height will be calculated.
  ----------------- ----------------------------------------------------------------------------------------------------

Returns
-------

**INT** : The height in pixels of the text in the font.

  ------- -------------------------------------------------
  0       - Invalid or no text; invalid font.
  &gt;0   - The height in pixels of the text in the font.
  ------- -------------------------------------------------

See also
--------

-   [text\_width](text_width "wikilink")()

<Category:functions> <Category:texts> <Category:mod_text>
