Definition
----------

**INT** map\_new ( &lt;**INT** width&gt; , &lt;**INT** height&gt; ,
&lt;**INT** depth&gt;, \[ &lt;**INT** flags&gt; \] )

Creates a new [graphic](graphic "wikilink"), sets the color of all
pixels to 0 (transparent) and puts it in the [system
file](system_file "wikilink").

The previous name [new\_map](new_map "wikilink")() is deprecated.

Parameters
----------

  ------------------- --------------------------------------------------------------------------------------------------
  **INT** width       - The width of the to be created graph in [pixels](pixel "wikilink").
  **INT** height      - The height of the to be created graph in pixels.
  **INT** depth       - The [color depth](color_depth "wikilink") of the to be created graph in [bits](bit "wikilink")
  \[**INT** flags\]   - can be: [B\_CLEAR](B_CLEAR "wikilink") (bitmap clear) or 0 (no clear new bitmap)
  ------------------- --------------------------------------------------------------------------------------------------

Returns
-------

**INT** : [GraphID](GraphID "wikilink")

  ------- ---------------------------------------------
  0       - There was an error.
  &gt;0   - The graphID of the newly created graphic.
  ------- ---------------------------------------------

Errors
------

  ------------------------- ---------------------------------------------------------------------------------------
  Unsupported color depth   - The specified color depth is not supported. *(Console)*
  Insufficient memory       - There is insufficient memory available. This error doesn't occur often. *(Console)*
  ------------------------- ---------------------------------------------------------------------------------------

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

<Category:functions> <Category:maps> <Category:mod_map>
