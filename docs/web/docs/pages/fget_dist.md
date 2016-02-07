Definition
----------

**INT** fget\_dist ( &lt;**INT** pointA-X&gt; , &lt;**INT** pointA-Y&gt;
, &lt;**INT** pointB-X&gt; , &lt;**INT** pointB-Y&gt; )

Returns the distance between two certain points.

Parameters
----------

  ------------------ --------------------------------
  **INT** pointA-X   - The X-coordinate of point A.
  **INT** pointA-Y   - The Y-coordinate of point A.
  **INT** pointB-X   - The X-coordinate of point B.
  **INT** pointB-Y   - The Y-coordinate of point B.
  ------------------ --------------------------------

Returns
-------

**INT** : The distance between point A and point B.

Example
-------

    Program angling;
    Const
        screen_width     = 320;
        screen_height    = 200;
        screen_depth     = 8;
        screen_fps       = 60;
        screen_frameskip = 0;
    Global
        int distance;
        int tempID;
    Begin

        // Set the screen mode
        set_mode(screen_width,screen_height,screen_depth);
        set_fps(screen_fps,screen_frameskip);

        // Change this to see what happens
        resolution = 100;

        // Create mouse graph, assign to mouse.graph
        mouse.graph = new_map(20,20,screen_depth);
        map_clear(0,mouse.graph,rgb(255,0,0));

        // Create arrow, assign to graph
        graph = new_map(30,30,screen_depth);
        drawing_map(0,graph);
        drawing_color(rgb(0,255,0));
        draw_line( 0,29,29,30/2);
        draw_line( 0, 0,30,30/2);

        // Set position
        x = screen_width /2 * resolution;
        y = screen_height/2 * resolution;

        // Display distance
        write(0,0,0,0,"Distance:");
        write_int(0,60,0,0,&distance);

        // Always point to the mouse
        Repeat
            // Get the angle and distance between this process' coordinates and those of the mouse.
            angle    = fget_angle(x,y,mouse.x*resolution,mouse.y*resolution);
            distance = fget_dist (x,y,mouse.x*resolution,mouse.y*resolution);
            frame;
        Until(key(_esc))

    End

Used in example: [set\_mode](set_mode "wikilink")(),
[new\_map](new_map "wikilink")(), [map\_clear](map_clear "wikilink")(),
[drawing\_map](drawing_map "wikilink")(),
[drawing\_color](drawing_color "wikilink")(),
[draw\_line](draw_line "wikilink")(), [write](write "wikilink")(),
[write\_int](write_int "wikilink")(),
[fget\_angle](fget_angle "wikilink")(),
[fget\_dist](fget_dist "wikilink")(),
[resolution](resolution "wikilink"), [mouse](mouse "wikilink"),
[graph](graph "wikilink"), [x](x "wikilink"), [y](y "wikilink"),
[angle](angle "wikilink")

This example could also be done with [get\_dist](get_dist "wikilink")(),
but that would be more work. It also gives a much less accurate distance
when the [resolution](resolution "wikilink") is &gt;1.

Resolution is 100:

  --------- ------------------------ ------------------------------------------------------------------------------------------ ------ --------- ------------------------- ----------------------------------------------------------------------------------------------
  {{Image   image = get\_angle.png   caption = [get\_angle](get_angle "wikilink")() and [get\_dist](get_dist "wikilink")() }}   | VS   {{Image   image = fget\_angle.png   caption = [fget\_angle](fget_angle "wikilink")() and [fget\_dist](fget_dist "wikilink")() }}
  --------- ------------------------ ------------------------------------------------------------------------------------------ ------ --------- ------------------------- ----------------------------------------------------------------------------------------------

<Category:functions> <Category:math> <Category:mod_math>
