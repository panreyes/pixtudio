Syntax
------

**INT** pal\_unload ( &lt;**INT** paletteID&gt; )

Description
-----------

This function unloads the palette, thus freeing the memory it ouccupies.

Also called [pal\_del](pal_del "wikilink")(). The previous name
[unload\_pal](unload_pal "wikilink")() is deprecated.

Parameters
----------

  ------------------- ------------------------------------------------------------------------------------------------------------
  **INT** paletteID   - The handle of the [palette](palette "wikilink") that was loaded with [Load\_pal](Load_pal "wikilink")().
  ------------------- ------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : Status.

  --- ------------------------
  1   - Operation completed.
  --- ------------------------

<Category:functions> <Category:palettes> <Category:mod_map>
