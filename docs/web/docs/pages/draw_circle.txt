Definition
----------

**INT** draw\_circle ( &lt;**INT** x&gt; , &lt;**INT** y&gt; ,
&lt;**INT** radius&gt; )

Draws a non-filled circle with center *(x0,y0)* and radius *radius*.

Parameters
----------

  ---------------- ------------------------------------------------------------
  **INT** x        - The x coordinate of one center of the non-filled circle.
  **INT** y        - The y coordinate of one center of the non-filled circle.
  **INT** radius   - The radius of the non-filled circle.
  ---------------- ------------------------------------------------------------

Returns
-------

**INT** : [DrawID](DrawID "wikilink")

  --------- ---------------------------------------------------------------------------------
  -1        - Error.
  1         - If drawn after [drawing\_map](drawing_map "wikilink")().
  !-1&&!1   - The [DrawID](DrawID "wikilink") of the [drawing](drawing "wikilink") created.
  --------- ---------------------------------------------------------------------------------

<Category:functions> <Category:drawing> <Category:mod_draw>
