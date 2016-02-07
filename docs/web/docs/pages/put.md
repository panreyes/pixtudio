Definition
----------

**INT** put ( &lt;**INT** fileID&gt; , &lt;**INT** graphID&gt; ,
&lt;**INT** x&gt; , &lt;**INT** y&gt; )

Draws ([blits](blit "wikilink")) a [graph](graph "wikilink") onto the
[background](background "wikilink").

For more advanced blitting, see:

-   [xput](xput "wikilink")()
-   [map\_put](map_put "wikilink")()
-   [map\_xput](map_xput "wikilink")()
-   [map\_xputnp](map_xputnp "wikilink")()

Parameters
----------

  ----------------- ------------------------------------------------------
  **INT** fileID    - The [file](file "wikilink") that holds the graph.
  **INT** graphID   - The [graph](graph "wikilink") to draw with.
  **INT** x         - Where on the background's x-axis to put the graph.
  **INT** y         - Where on the background's y-axis to put the graph.
  ----------------- ------------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Notes
-----

The x and y parameters denote where to draw the graph, that is, where
the center of the to be drawn graph will be.

Errors
------

  ------------------------- ---------------------------------------------------------------------------
  Unsupported color depth   - The origin graph's color depth is greater than the destination graph's.
  ------------------------- ---------------------------------------------------------------------------

Example
-------

    import "mod_map"
    import "mod_screen"
    import "mod_key"

    Process Main()
    Private
        int map;
    Begin

        // Create a new graph of size 100x100 and color depth of 8bit
        map = map_new(100,100,8);
        
        // Clear the map red
        map_clear(0,map,rgb(255,0,0));

        // Put it in the center of the screen
        put(0,map,160,100);

        Repeat
            frame;
        Until(key(_ESC))

    End

Used in example: [map\_new](map_new "wikilink")(),
[map\_clear](map_clear "wikilink")(), [put](put "wikilink")(),
[key](key "wikilink")()

This will result in something like:\

<Category:functions> <Category:screen> <Category:mod_screen>
