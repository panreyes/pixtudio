Definition
----------

**INT** draw\_curve ( &lt;**INT** x0&gt; , &lt;**INT** y0&gt; ,
&lt;**INT** x1&gt; , &lt;**INT** y1&gt; , &lt;**INT** x2&gt; ,
&lt;**INT** y2&gt; , &lt;**INT** x3&gt; , &lt;**INT** y3&gt; ,
&lt;**INT** smoothness&gt; )

Draws a curve starting at the point *(x0,y0)*, ending at the point
*(x3,y3)* and influenced by the points *(x1,y1)* and *(x2,y2)* with a
certain level of smoothness.

Parameters
----------

  -------------------- ------------------------------------------------------------------------------------------
  **INT** x0           - The x coordinate of the starting point of the curve.
  **INT** y0           - The y coordinate of the starting point of the curve.
  **INT** x1           - The x coordinate of the first influence point of the curve.
  **INT** y1           - The x coordinate of the first influence point of the curve.
  **INT** x2           - The x coordinate of the second influence point of the curve.
  **INT** y2           - The x coordinate of the second influence point of the curve.
  **INT** x3           - The x coordinate of the end point of the curve.
  **INT** y3           - The y coordinate of the end point of the curve.
  **INT** smoothness   - The smoothness with which the line will be drawn from 1 to 15, 15 being the smoothest.
  -------------------- ------------------------------------------------------------------------------------------

Returns
-------

**INT** : [DrawID](DrawID "wikilink")

  --------- ---------------------------------------------------------------------------------
  -1        - Error.
  1         - If drawn after [drawing\_map](drawing_map "wikilink")().
  !-1&&!1   - The [DrawID](DrawID "wikilink") of the [drawing](drawing "wikilink") created.
  --------- ---------------------------------------------------------------------------------

Example
-------

    import "mod_draw"
    import "mod_video"
    import "mod_mouse"
    import "mod_map"

    GLOBAL
    scr_width = 640, scr_height=480;
    End;

    Process main()
    Begin
        /* Check that we can set the video mode before actually setting it */
        if(!mode_is_ok(scr_width, scr_height, 16, MODE_WINDOW))
            return -1;
        end;
        set_mode(scr_width, scr_height, 16, MODE_WINDOW);

        /* Draw three long bezier lines with different colors and smoothnesses */
        drawing_map(0, 0);
        drawing_color(rgb(255, 0, 0));
        draw_curve(0, scr_height/4, scr_width/4, 0, 3*scr_width/4, 2*scr_height/4,
                   scr_width, scr_height/4, 1);
        drawing_color(rgb(0, 255, 0));
        draw_curve(0, 2*scr_height/4, scr_width/4, scr_height/4, 3*scr_width/4,
                   3*scr_height/4, scr_width, 2*scr_height/4, 3);
        drawing_color(rgb(0, 0, 255));
        draw_curve(0, 3*scr_height/4, scr_width/4, 2*scr_height/4, 3*scr_width/4,
                   4*scr_height/4, scr_width, 3*scr_height/4, 15);

        while(! mouse.left)
            FRAME;
        end;

        // Delete all the lines
        delete_draw(0);
    End;

Used in example: [mode\_is\_ok](mode_is_ok "wikilink")(),
[set\_mode](set_mode "wikilink")(),
[drawing\_map](drawing_map "wikilink")()
[drawing\_color](drawing_color "wikilink")(), [rgb](rgb "wikilink")(),
[draw\_curve](draw_curve "wikilink")(),
[delete\_draw](delete_draw "wikilink")()

<Category:functions> <Category:drawing> <Category:mod_draw>
