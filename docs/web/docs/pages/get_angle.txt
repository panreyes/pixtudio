Definition
----------

**INT** get\_angle ( &lt;**INT** processID&gt; )

Returns the [angle](angle "wikilink") between the coordinates of a
certain [process](process "wikilink") and the process calling
[get\_angle](get_angle "wikilink")().

Parameters
----------

  ------------------- --------------------------------------------
  **INT** processID   - The other [process](process "wikilink").
  ------------------- --------------------------------------------

Returns
-------

**INT** : The wanted [angle](angle "wikilink").

  ----- ------------------------------------------------------------------------
  -1    - An error *may* have occurred: invalid [process](process "wikilink").
  !-1   - The wanted [angle](angle "wikilink").
  ----- ------------------------------------------------------------------------

Example
-------

    Program angling;
    import "mod_grproc"//modules
    import "mod_proc"
    import "mod_wm"
    import "mod_key"
    import "mod_video"
    import "mod_map"
    import "mod_draw"
    import "mod_text"
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

        // Create mouse graph and start mousepointer
        x = new_map(20,20,screen_depth);
        map_clear(0,x,rgb(255,0,0));
        mousepointer(0,x);

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
            // Get the angle and distance between this process' coordinates and those of mousegraph.
            // We can use TYPE and get_id() here, because usually there would only be one
            // mousepointer and one always.
            tempID = get_id(type mousepointer);
            angle = get_angle(tempID);
            distance = get_dist(tempID);
            frame;
        Until(key(_esc))

    End

    /**
     * Follows the mouse coordinates. x is always mouse.x and y is always mouse.y
     * for processes with priority <1. The graphic of this process will be a certain graphic.
     * int file     - The fileID of the file where the graphic is located
     * int graph    - The graphID of the graphic to be used for this process
     */
    Process mousepointer(int file,int graph)
    Begin
        // Set the priority to 1, because we first want to have the correct coordinates of
        // the mouse set in this process. Then after that other process can use those coordinates.
        priority = 1;
        // Obtain father's resolution
        resolution = father.resolution;
        // Loop
        Loop
            // Obtain X and Y coordinates of the mouse and adjust for resolution
            // (mouse.y and mouse.y have an unchangeable resolution of 1)
            x = mouse.x * resolution;
            y = mouse.y * resolution;
            frame;
        End
    End

Used in example: [set\_mode](set_mode "wikilink")(),
[new\_map](new_map "wikilink")(), [map\_clear](map_clear "wikilink")(),
[drawing\_map](drawing_map "wikilink")(),
[drawing\_color](drawing_color "wikilink")(),
[draw\_line](draw_line "wikilink")(), [write](write "wikilink")(),
[write\_int](write_int "wikilink")(), [get\_id](get_id "wikilink")(),
[get\_angle](get_angle "wikilink")(),
[get\_dist](get_dist "wikilink")(), [resolution](resolution "wikilink"),
[mouse](mouse "wikilink"), [graph](graph "wikilink"), [x](x "wikilink"),
[y](y "wikilink"), [angle](angle "wikilink"),
[priority](priority "wikilink")

This example could also be done with
[fget\_angle](fget_angle "wikilink")(), which is easier and doesn't
require an extra [process](process "wikilink").

It could look something like:\
<http://wwwhome.cs.utwente.nl/~bergfi/fenix/wiki/get_angle.PNG>

<Category:functions> <Category:processinteraction> <Category:mod_grproc>
