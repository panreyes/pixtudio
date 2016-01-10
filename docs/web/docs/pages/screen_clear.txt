Definition
----------

**INT** screen\_clear ( )

Clears the [background](background "wikilink") of the screen, making it
completely black.

Also called [clear\_screen](clear_screen "wikilink")().

Returns
-------

**INT** : [true](true "wikilink")

Notes
-----

This is the same as `'''[[map_clear]]'''(0,[[BACKGROUND]])`. When the
background is cleared in either way, [Bennu](Bennu "wikilink") knows the
background is empty and will take advantage of this knowledge.

Errors
------

  ------------------------- --------------------------------------------------------
  Unsupported color depth   - The specified graph has a not supported color depth.
  ------------------------- --------------------------------------------------------

<Category:functions> <Category:screen> <Category:mod_screen>
