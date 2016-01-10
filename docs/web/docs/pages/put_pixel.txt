Definition
----------

**INT** put\_pixel ( &lt;**INT** x&gt; , &lt;**INT** y&gt; , &lt;**INT**
color&gt; )

Draws a single colored [pixel](pixel "wikilink") on the
[background](background "wikilink"). Is equivalent to
[map\_put\_pixel](map_put_pixel "wikilink") ( 0, 0, x, y, color ).

Parameters
----------

  --------------- ------------------------------------------------------
  **INT** x       - Where on the background's x-axis to put the pixel.
  **INT** y       - Where on the background's y-axis to put the pixel.
  **INT** color   - What [color](color "wikilink") to draw.
  --------------- ------------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Example
-------

    import "mod_video"
    import "mod_map"
    import "mod_wm"
    import "mod_draw"
    import "mod_rand";

    Process Main()
    Private
        int i;
        int direction;
    end
    Begin

        // Set the mode to 16bit and some res
        set_mode(320,200,16);

        // Create a blue-ish square map
        graph = new_map(20,20,16);
        map_clear(0,graph,rgb(50,100,150));
        y=100;
        x=10;

        // Puts 100 yellow-ish pixels in random places in the background
        for(i=0; i<100; i++)
            put_pixel(rand(0,320),rand(0,200),rgb(255,255,55));
        end

        Repeat
            x=x+direction; 
            if (x>=310) direction=-3; end 
            if (x<=10) direction=3; end
            frame;
        Until(exit_status)

    End

Used in example: [set\_mode](set_mode "wikilink")(),
[new\_map](new_map "wikilink")(), [map\_clear](map_clear "wikilink")(),
[rand](rand "wikilink")(), [put\_pixel](put_pixel "wikilink")()

<Category:functions> <Category:maps> <Category:mod_draw>
<Category:mod_map>
