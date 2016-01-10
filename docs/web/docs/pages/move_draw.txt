Definition
----------

**INT** move\_draw ( &lt;**INT** DrawID&gt; , &lt;**INT** x&gt; ,
&lt;**INT** y&gt; )

Moves a certain [drawing](drawing "wikilink") on the screen. Only
drawings drawn with a certain z value can be moved like this, as other
ones are drawn on a [graphic](graphic "wikilink") and thus cannot be
moved.

Parameters
----------

  ---------------- ---------------------------------------------------------------------------------
  **INT** DrawID   - [DrawID](DrawID "wikilink") of the [drawing](drawing "wikilink") to be moved.
  **INT** x        - The new x coordinate of the drawing.
  **INT** y        - The new y coordinate of the drawing.
  ---------------- ---------------------------------------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

<Category:functions> <Category:drawing> <Category:mod_draw>
