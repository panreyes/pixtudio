Definition
----------

A drawing is something drawn on the screen using [draw\_xxx()
functions](Functioncategory:drawing "wikilink"). This can be a circle,
square, line or whatever they can draw. A drawing is associated with a
certain [DrawID](DrawID "wikilink"), returned by the function which drew
the drawing.

A drawing also has a certain z value, initialized when drawn and at that
point equal to the value set using [drawing\_z](drawing_z "wikilink")().
The drawing will behave like a [process](process "wikilink") with the
same [z](z "wikilink"). When [drawing\_map](drawing_map "wikilink")() is
used, that z value is ignored and the drawing is just drawn on the
specified [graphic](graphic "wikilink").
