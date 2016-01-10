Definition
----------

**INT** map\_put\_pixel ( &lt;**INT** fileID&gt; , &lt;**INT**
graphID&gt; , &lt;**INT** x&gt; , &lt;**INT** y&gt; , &lt;**INT**
color&gt; )

Draws a single colored [pixel](pixel "wikilink") on a
[graph](graph "wikilink").

Parameters
----------

  ----------------- -----------------------------------------------------
  **INT** fileID    - The [file](file "wikilink") that holds the graph.
  **INT** graphID   - The [graph](graph "wikilink") to draw on.
  **INT** x         - Where on the graph's x-axis to put the pixel.
  **INT** y         - Where on the graph's y-axis to put the pixel.
  **INT** color     - What [color](color "wikilink") to draw.
  ----------------- -----------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Errors
------

  ------------------------- ------------------------------------------------------
  Invalid map               - Map doesn't exist.
  Unsupported color depth   - Destination graph is of an unsupported colordepth.
  ------------------------- ------------------------------------------------------

Example
-------

    import "mod_video"
    import "mod_map"
    import "mod_screen"
    import "mod_wm"
    import "mod_draw"

    Process Main()
    Private
        int map;
        int i;
    Begin

        // Set the mode to 16bit and some res
        set_mode(320,200,16);

        // Create a blue-ish square map
        map = new_map(100,100,16);
        map_clear(0,map,rgb(50,100,150));

        // Puts 100 yellow-ish pixels in random places in the graphic
        for(i=0; i<100; i++)
            map_put_pixel(0,map,rand(0,100),rand(0,100),rgb(255,255,55));
        end

        // Puts the map in the center of the screen
        put(0,map,160,100);

        Repeat
            frame;
        Until(exit_status)

    End

Used in example: [set\_mode](set_mode "wikilink")(),
[new\_map](new_map "wikilink")(), [map\_clear](map_clear "wikilink")(),
[map\_put\_pixel](map_put_pixel "wikilink")(),
[rand](rand "wikilink")(), [put](put "wikilink")()

<Category:functions> <Category:maps> <Category:mod_draw>
<Category:mod_map>
