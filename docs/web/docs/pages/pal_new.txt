Syntax
------

**INT** pal\_new ()

Description
-----------

This function creates a new palette in memory and returns the handle,
for later use by other [palette](palette "wikilink") functions such as
[Pal\_save](Pal_save "wikilink")(), [Pal\_get](Pal_get "wikilink")(),
[Pal\_set](Pal_set "wikilink"), etc. When you're done, you can free the
memory with [Pal\_unload](Pal_unload "wikilink")().

The previous name [new\_pal()](new_pal() "wikilink") is deprecated.

Returns
-------

**INT** : Status.

  ---- -----------------------------------------------------------------------------
  id   - The identification code of the memory area for the newly created palette.
  ---- -----------------------------------------------------------------------------

<Category:functions> <Category:palettes> <Category:mod_map>
