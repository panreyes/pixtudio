Definition
----------

**INT** point\_set ( &lt;**INT** fileID&gt; , &lt;**INT** graphID&gt; ,
&lt;**INT** controlpointID&gt; , &lt;**INT** x&gt;, &lt;**INT** y&gt;)

Allows you to set a control point of a particular
[graphic](graphic "wikilink").

Any graph can contain up to 1000 control points (from 0 to 999). Control
point 0 is the center of the graphic. This
[function](function "wikilink") allows you to set the location of any
control point belonging to any graph. The coordinates are relative to
the upper left corner of the graphic.

To obtain the coordinates of a control point, use
[point\_get](point_get "wikilink")().

The previous name [set\_point](set_point "wikilink")() is deprecated.

Parameters
----------

  ------------------------ -------------------------------------------------------------------------------------------------------
  **INT** fileID           - [FileID](FileID "wikilink") of the [file](file "wikilink") containing the graphic.
  **INT** graphID          - [GraphID](GraphID "wikilink") of the [graphic](graphic "wikilink") of which to set a control point.
  **INT** controlpointID   - Number of the control point.
  **INT** x                - The new X-coordinate of the control point.
  **INT** y                - The new Y-coordinate of the control point.
  ------------------------ -------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : Successrate

  ---- -----------------------------------------------------------------------------------------
  -1   - One of the following: specified graph is invalid, specified control point is invalid.
  1    - The control point was set successfully.
  ---- -----------------------------------------------------------------------------------------

Example
-------

    import "mod_map"
    import "mod_say"
    import "mod_wm"
    import "mod_key"
    import "mod_grproc"

    Process Main()
    Private
        int map;
        int cx,cy;
    Begin

        // Create a red graph
        map = new_map(100,100,8);
        map_clear(0,map,rgb(255,0,0));

        // Set the center to a random point
        point_set(0,map,0,rand(-10,110),rand(-10,110));

        // Get the center
        point_get(0,map,0,&cx,&cy);

        // Show the center
        say("Center-X: " + cx);
        say("Center-Y: " + cy);

        // Assign the map to the graph variable
        graph = map;

        // Set the location of this process to the center of the screen
        x = 160;
        y = 100;

        Repeat
            frame;
        Until(exit_status||key(_ESC))

    End

Used in example: [new\_map](new_map "wikilink")(),
[map\_clear](map_clear "wikilink")(),
[point\_set](point_set "wikilink")(),
[point\_get](point_get "wikilink")(), [say](say "wikilink")(),
[pointer](pointer "wikilink"), [graph](graph "wikilink")

Notice that setting the center influences the position of the graph:

<Category:functions> <Category:maps> <Category:mod_map>
