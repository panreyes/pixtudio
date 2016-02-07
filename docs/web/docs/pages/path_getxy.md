Syntax
------

'''INT ''' path\_getxy ( &lt;**POINTER** x&gt;, &lt;**POINTER** y&gt; )

Description
-----------

This function gets a node and returns a 1 when there's still a point
left, or a 0 when there are no more points. This function requires a two
dimensional [Array](Array "wikilink") to work on. The arguments should
accessed with the [Offset](Offset "wikilink") operator. The function is
typically used inside a loop. The pathfinding in bennu is based on the
A\* algorithm. It uses a logic map with a maze, a start position and an
end position.

Here's the bennu source code:
[mod\_path.c](http://bennugd.svn.sourceforge.net/viewvc/bennugd/modules/mod_path/mod_path.c?revision=277&view=markup),
[wikipedia page about
pathfinding](http://en.wikipedia.org/wiki/Pathfinding).

Parameters
----------

  --------------- ------------------------------------------
  **POINTER** x   - Offset of the array with the x values.
  **POINTER** y   - Offset of the array with the y values.
  --------------- ------------------------------------------

Returns
-------

**INT** : Status.

  --- ------------------------------------------------------------
  0   - There are no more coordinate points (nodes) in the list.
  1   - There are still coordinate points (nodes) in the list.
  --- ------------------------------------------------------------

Example
-------

Look at this tutorial: <Tutorial:Pathfind_demo>.

<Category:functions> <Category:Pathfind> <Category:mod_path>
