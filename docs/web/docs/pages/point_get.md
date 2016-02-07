Definition
----------

**INT** get\_point ( &lt;**INT** fileID&gt; , &lt;**INT** graphID&gt; ,
&lt;**INT** controlpointID&gt; , &lt;**INT POINTER** x&gt;, &lt;**INT
POINTER** y&gt;)

Allows you to obtain a control point of a particular
[graph](graph "wikilink").

Any graph can contain up to 1000 control points (from 0 to 999). Control
point 0 is the center of the graphic. This
[function](function "wikilink") allows you to know the location of any
control point belonging to any graph.

To set a control point, use [set\_point](set_point "wikilink")() or, for
only the center of a graph, [set\_center](set_center "wikilink")().

The previous name [get\_point](get_point "wikilink")() is deprecated.

Parameters
----------

  ------------------------ ---------------------------------------------------------------------------
  **INT** fileID           - Number of the FPG library.
  **INT** graphID          - Number of the graph inside the library which you want to use.
  **INT** controlpointID   - Number of the control point.
  **INT POINTER** x        - Pointer to where the X-coordinate of the control point will be written.
  **INT POINTER** y        - Pointer to where the Y-coordinate of the control point will be written.
  ------------------------ ---------------------------------------------------------------------------

Returns
-------

**INT** : Successrate

  --------------------------- -------------------------------------------------------------------------------------------------------------------------------
  [false](false "wikilink")   - One of the following: specified graph is invalid, specified control point is invalid, specified control point is undefined.
  [true](true "wikilink")     - The control point was defined or the center was used.
  --------------------------- -------------------------------------------------------------------------------------------------------------------------------

Example
-------

    Program cpoint;
    Private
        int map;
        int cx,cy;
    Begin

        // Create a red graph
        map = new_map(100,100,8);
        map_clear(0,map,rgb(255,0,0));

        // Set the center to a random point
        set_center(0,map,rand(-10,110),rand(-10,110));

        // Get the center
        get_point(0,map,0,&cx,&cy);

        // Show the center
        say("Center-X: " + cx);
        say("Center-Y: " + cy);

        // Assign the map to the graph variable
        graph = map;

        // Set the location of this process to the center of the screen
        x = 160;
        y = 100;

        Loop
            frame;
        End

    End

Used in example: [new\_map](new_map "wikilink")(),
[map\_clear](map_clear "wikilink")(),
[set\_center](set_center "wikilink")(), [say](say "wikilink")(),
[pointer](pointer "wikilink"), [graph](graph "wikilink")

Notice that setting the center influences the position of the graph:

<Category:functions> <Category:maps> <Category:mod_map>
