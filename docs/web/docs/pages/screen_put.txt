Definition
----------

**INT** screen\_put ( &lt;**INT** fileID&gt; , &lt;**INT** graphID&gt; )

Clears and draws ([blits](blit "wikilink")) a [graph](graph "wikilink")
onto the [background](background "wikilink") in the center.

For more advanced blitting, see:

-   [put](put "wikilink")()
-   [xput](xput "wikilink")()

Also called [put\_screen](put_screen "wikilink")().

Parameters
----------

  ----------------- -----------------------------------------------------
  **INT** fileID    - The [file](file "wikilink") that holds the graph.
  **INT** graphID   - The [graph](graph "wikilink") to draw with.
  ----------------- -----------------------------------------------------

Returns
-------

**INT**

  --- ----------------
  0   - Invalid map.
  1   - Success.
  --- ----------------

Notes
-----

The center of the specified graph influences its placement.

The following codes are equivalent:

    screen_put(f,g);

    screen_clear();
    put(f,g,graphic_info(0,BACKGROUND,G_WIDTH)/2,graphic_info(0,BACKGROUND,G_HEIGHT)/2);

See [screen\_clear](screen_clear "wikilink")(), [put](put "wikilink")()
and [map\_info](map_info "wikilink")().

Errors
------

  ------------------------- ---------------------------------------------------------------------------
  Invalid map               - The specified map is invalid.
  Unsupported color depth   - The origin graph's color depth is greater than the destination graph's.
  ------------------------- ---------------------------------------------------------------------------

<Category:functions> <Category:screen> <Category:mod_screen>
