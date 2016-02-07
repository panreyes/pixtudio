Definition
----------

**INT** get\_pixel ( &lt;**INT** x&gt; , &lt;**INT** y&gt; )

Returns the [color](color "wikilink") of the specified
[pixel](pixel "wikilink") on the [background](background "wikilink"). Is
equivalent to [map\_get\_pixel](map_get_pixel "wikilink")( 0, 0, x, y ).

Parameters
----------

  ----------- --------------------------------------------------------------------------
  **INT** x   - The X-coordinate of the [pixel](pixel "wikilink") the color is wanted.
  **INT** y   - The Y-coordinate of the [pixel](pixel "wikilink") the color is wanted.
  ----------- --------------------------------------------------------------------------

Returns
-------

**INT** : The color

Example
-------

    import "mod_video"
    import "mod_wm"
    import "mod_draw"
    import "mod_map";
    import "mod_screen";
    import "mod_mouse";

    Process Main()

    Begin

        set_mode(640,480,16); 

        // Creates a white box as mouse's cursor
        mouse.graph = new_map(20,20,16);
        map_clear(0,mouse.graph,rgb(255,255,255));

        // This area will show the pixel's color behind the cursor
        graph=new_map(100,50,16);
        x=50;
        y=25; 

        //Puts the background
        put_screen(0,load_png("image.png"));  

        Repeat
            map_clear(0,graph,get_pixel(mouse.x,mouse.y));
            frame;
        Until(exit_status)

    End

Used in example: [set\_mode](set_mode "wikilink")(),
[new\_map](new_map "wikilink")(), [map\_clear](map_clear "wikilink")(),
[put\_screen](put_screen "wikilink")(),
[get\_pixel](get_pixel "wikilink")()

<Category:functions> <Category:maps> <Category:mod_draw>
<Category:mod_map>
