Syntax
------

**INT** pal\_save ( &lt;**STRING** filename&gt;, \[&lt;**INT**
paletteID&gt;\] )

Description
-----------

This function saves a [palette](palette "wikilink") to a file on disk in
the [PAL](PAL "wikilink") format. When the second parameter is omitted,
the system palette is saved, otherwise the palette data indicate with
the paletteID. Concluding from this, is that it's possible to load
multiple palettes in bennu and assign an unique identifier to them and
save them to a file later.

The previous name [save\_pal](save_pal "wikilink")() is deprecated.

Parameters
----------

  --------------------- ----------------------------------------------------------------------------------------------------------------------------------------
  **STRING** filename   - The filename of the new palette file.
  **INT** paletteID     - The handle of the [palette](palette "wikilink") that was loaded with [Load\_pal](Load_pal "wikilink")(). This parameter is optional.
  --------------------- ----------------------------------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : Status.

  ---- --------------------
  id   - The file handle.
  ---- --------------------

<Category:functions> <Category:palettes> <Category:mod_map>
