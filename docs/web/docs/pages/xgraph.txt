<category:variables> <category:predefined> [category:local
variables](category:local_variables "wikilink") <category:libscroll>
<category:librender>

[**Up to Local Variables**](Local_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

The predefined local variable xgraph is assigned to each process. It is
the so called "extended" graphic, and it allows graphics to be displayed
that are controlled by the nearest process [Angle](Angle "wikilink").
When the xgraph is defined, the normal variable
[Graph](Graph "wikilink") is ignored, and the graphic used for display
is determined by the angle.

So when the angle changes, a different graphic is selected from a table
(defined as an [Array](Array "wikilink")). The standard value of xgraph
is 0, so normally it isn't used unless it is explicitly specified.
Xgraps are usefull in combination with [Mode7](Mode7 "wikilink"), to
create graphics with perspectives. This mechanism is similair to how
[Wolfenstein3D](http://en.wikipedia.org/wiki/Wolfenstein_3D),
[Doom](http://en.wikipedia.org/wiki/Doom_%28video_game%29) and [Duke
Nukem 3D](http://en.wikipedia.org/wiki/Duke_Nukem_3D) render their
sprites. So it's not true 3d, but just a bunch of sprites wich
perspective depends on the viewing angle.

How to use it
-------------

First, you'll have to make sprites for all intended perspective's. To
more angle's you wish, the more perspectives you'll need.

Second, you must place the graphics in order of their angle, in
clockwise fashion.

Third, you'll have to make a table with the graphic codes.

    GLOBAL

    perspective_table[]=4,10,11,12,13; // the length doesn't matter, but the more perspectives you wish, 
                                       // the more graphics you need to have.

Fourth, you'll have to assing the table offset to the xgraph.

    xgraph=&perspective_table; // xgraph get's the offset adress of the array.

The [Offset](Offset "wikilink") operator is get's the adress of the
data, this is related to pointers.

Remarks
-------

When xgraph is defined, it has to be set to 0 in order to deactivate it.

When a graphic code in the table has a negative number, this graphic
will be mirrored horizontally.
