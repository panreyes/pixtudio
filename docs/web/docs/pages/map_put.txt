Syntax
------

**INT** map\_put ( &lt;**INT** fileID&gt; , &lt;**INT**
destinationGraphID&gt; , &lt;**INT** originGraphID&gt; , &lt;**INT**
x&gt; , &lt;**INT** y&gt; )

Description
-----------

Draws ([blits](blit "wikilink")) a [graph](graph "wikilink") onto
another graph.

If more advanced parameters are needed,
[map\_xput](map_xput "wikilink")() can be used. If a graph from one
[file](file "wikilink") needs to be drawn onto another graph in a
different file, or a separate width and height scaling is needed,
[map\_xputnp](map_xputnp "wikilink")() can be used.

Parameters
----------

  ---------------------------- -------------------------------------------------------------------------------------------
  **INT** fileID               - The [fileID](fileID "wikilink") of the [file](file "wikilink") that holds the graphics.
  **INT** destinationGraphID   - The [graphID](graphID "wikilink") of the [graphic](graphic "wikilink") to draw on.
  **INT** originGraphID        - The [graphID](graphID "wikilink") of the [graphic](graphic "wikilink") to draw with.
  **INT** x                    - Where on the destination graphic's x-axis to put the graph.
  **INT** y                    - Where on the destination graphic's y-axis to put the graph.
  ---------------------------- -------------------------------------------------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Notes
-----

The x and y parameters denote where to draw the graph, that is, where
the center of the to be drawn graph will be.

Errors
------

  --------------------------- ---------------------------------------------------------------------------
  Invalid origin graph        - The origin graph is invalid.
  Invalid destination graph   - The destination graph is invalid.
  Unsupported color depth     - The origin graph's color depth is greater than the destination graph's.
  --------------------------- ---------------------------------------------------------------------------

Example
-------

    import "mod_video"
    import "mod_map"
    import "mod_wm"

    Process Main()
    Private
        int destgraph;
        int origgraph1;
        int origgraph2;
    Begin

        // Set the mode to 16bit and some resolution
        set_mode(320,200,16);

        // Makes the destination graphic a red square
        destgraph=new_map(100,100,16);
        map_clear(0,destgraph,rgb(255,0,0));

        // Makes the first origin graphic a green square
        origgraph1=new_map(100,100,16);
        map_clear(0,origgraph1,rgb(0,255,0));

        // Makes the second origin graphic a blue square
        origgraph2=new_map(100,100,16);
        map_clear(0,origgraph2,rgb(0,0,255));

        // Draws the blue and green squares at a random position on the red square
        map_put(0,destgraph,origgraph1,rand(0,100),rand(0,100));
        map_put(0,destgraph,origgraph2,rand(0,100),rand(0,100));

        // Shows the final graph
        put(0,destgraph,160,100);
        
        Repeat
            frame;
        Until(exit_status)

    End

Used in example: [set\_mode](set_mode "wikilink")(),
[new\_map](new_map "wikilink")(), [map\_clear](map_clear "wikilink")(),
[map\_put](map_put "wikilink")(), [put](put "wikilink")(),
[key](key "wikilink")(), [exit\_status](exit_status "wikilink")

This will result in something like:\

<Category:functions> <Category:maps> <Category:mod_map>
