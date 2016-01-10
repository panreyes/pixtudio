Definition
----------

**INT** draw\_line( &lt;**INT** x0&gt; , &lt;**INT** y0&gt; ,
&lt;**INT** x1&gt; , &lt;**INT** y1&gt; )

Draws a line from point *(x0,y0)* to point *(x1,y1)*.

Parameters
----------

  ------------ ----------------------------------------------------
  **INT** x0   - The x coordinate of one point of the line.
  **INT** y0   - The y coordinate of one point of the line.
  **INT** x1   - The x coordinate of the other point of the line.
  **INT** y1   - The y coordinate of the other point of the line.
  ------------ ----------------------------------------------------

Returns
-------

**INT** : [DrawID](DrawID "wikilink")

  --------- ---------------------------------------------------------------------------------
  -1        - Error.
  1         - If drawn after [drawing\_map](drawing_map "wikilink")().
  !-1&&!1   - The [DrawID](DrawID "wikilink") of the [drawing](drawing "wikilink") created.
  --------- ---------------------------------------------------------------------------------

<Category:functions> <Category:drawing> <Category:mod_draw>
