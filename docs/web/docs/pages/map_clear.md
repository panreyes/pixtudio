Definition
----------

**INT** map\_clear ( &lt;**INT** fileID&gt; , &lt;**INT** graphID&gt; ,
&lt;**WORD** color&gt; )

Clears a certain graph to a certain color.

Parameters
----------

  ----------------- -------------------------------------------------------
  **INT** fileID    - The [file](file "wikilink") that holds the graphic.
  **INT** graphID   - The [graphic](graphic "wikilink") to clear.
  **WORD** color    - The [color](color "wikilink") used to clear.
  ----------------- -------------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Notes
-----

Instead of using **map\_clear**() to clear the screen
[background](background "wikilink"),
[clear\_screen](clear_screen "wikilink")() is recommended as it is a
little bit faster.

Errors
------

  ------------------------- --------------------------------------------------------
  Unsupported color depth   - The specified graph has a not supported color depth.
  ------------------------- --------------------------------------------------------

Example
-------

    Program a_map_is_born;
    Private
        int map;
    Begin

        // Create a new graph of size 100x100 and color depth of 8bit
        map = new_map(100,100,8);
        
        // Clear the map red
        map_clear(0,map,rgb(255,0,0));

        // Put it in the center of the screen
        put(0,map,160,100);

        Loop
            frame;
        End

    End

Used in example: [new\_map](new_map "wikilink")(),
[put](put "wikilink")()

This will result in something like:\
<http://wwwhome.cs.utwente.nl/~bergfi/fenix/wiki/new_map.PNG>

<Category:functions> <Category:maps> <Category:mod_map>
