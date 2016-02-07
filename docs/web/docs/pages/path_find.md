Syntax
------

'''INT ''' path\_find ( &lt;**INT** fileID&gt; , &lt;**INT** graphID&gt;
, &lt;**INT** start\_x&gt; , &lt;**INT** start\_y&gt; , &lt;**INT**
dest\_x&gt; , &lt;**INT** dest\_y&gt; , &lt;**INT** options&gt;)

Description
-----------

The pathfinding function is based on the A\* algorithm with a heuristic
value. It uses a logic map with a maze, a start position and an end
position. The logic map is an 8 bit image (with palette), preferably
with only 2 colors, black and white, wich indicates the walls and the
paths.

Here's the bennu source code:
[mod\_path.c](http://bennugd.svn.sourceforge.net/viewvc/bennugd/modules/mod_path/mod_path.c?revision=277&view=markup),
[wikipedia page about
pathfinding](http://en.wikipedia.org/wiki/Pathfinding).

Parameters
----------

  ------------------ ------------------------------------------------------------------------------------------------------------------------------------------
  **INT** fileID     - The fpg archive wich contains the map, may be 0 when the systemfile is used.
  **INT** graphID    - The bitmap (either mapcode from fpg or loaded with [Map\_load](Map_load "wikilink")() into the systemfile) with the maze, see notes\*.
  **INT** start\_x   - The x coordniate of the start position.
  **INT** start\_y   - The y coordniate of the start position.
  **INT** dest\_x    - The x coordinate of the destination position.
  **INT** dest\_y    - The y coordinate of the destination position.
  **INT** options    - The kind of pathfinding, [PF\_NODIAG](PF_NODIAG "wikilink"), [PF\_REVERSE](PF_REVERSE "wikilink")
  ------------------ ------------------------------------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : Status.

  --- ------------------------------------
  0   - The path has not been found yet.
  1   - The path has been found.
  --- ------------------------------------

Example
-------

Look at this tutorial: <Tutorial:Pathfind_demo>.

Notes
-----

-   This function requires the use of 8 bit indexed (256 color) bitmaps
    for the path map, because of the logic behind it's design. The
    philosophy behind this is similair to a hardness (logic) map. It is
    perfectly possible to combine 8 bit images in 16 or 32 bit
    colormodes, provided that all 8 bit maps share the
    same colorpalette.

<Category:functions> <Category:Pathfind> <Category:mod_path>
