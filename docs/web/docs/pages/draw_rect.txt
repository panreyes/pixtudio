Definition
----------

**INT** draw\_rect ( &lt;**INT** x0&gt; , &lt;**INT** y0&gt; ,
&lt;**INT** x1&gt; , &lt;**INT** y1&gt; )

Draws a non-filled rectangle with corners *(x0,y0)*, *(x0,y1)*,
*(x1,y0)* and *(x1,y1)*.

Parameters
----------

  ------------ -----------------------------------------------------------------------------------
  **INT** x0   - The x coordinate of one corner of the non-filled rectangle.
  **INT** y0   - The y coordinate of one corner of the non-filled rectangle.
  **INT** x1   - The x coordinate of the diagonally opposite corner of the non-filled rectangle.
  **INT** y1   - The y coordinate of the diagonally opposite corner of the non-filled rectangle.
  ------------ -----------------------------------------------------------------------------------

Returns
-------

**INT** : [DrawID](DrawID "wikilink")

  --------- ---------------------------------------------------------------------------------
  -1        - Error.
  1         - If drawn after [drawing\_map](drawing_map "wikilink")().
  !-1&&!1   - The [DrawID](DrawID "wikilink") of the [drawing](drawing "wikilink") created.
  --------- ---------------------------------------------------------------------------------

<Category:functions> <Category:drawing> <Category:mod_draw>
