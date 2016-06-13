Definition
----------

&lt;datatype&gt; &lt;array name&gt;**\[**&lt;upperlimit&gt;**\]** \[= &lt;values&gt;\]

**Array**s are [datatypes](#datatypes), consisting of a
*range* of variables of the *same type*. The range is `0..upperlimit`,
meaning there are `upperlimit+1` elements in the array.

The initializing values start at the first (*0th*) element and go up
from there.

Example
-------

### Mutliple ints

    int lottery[9]; // an array of 10 ints

Use them like:

    lottery[0] = 1;
    lottery[5] = 35;
    lottery[1] = lottery[5];

### Multiple types

Consider, using [Type](#Type):

    Type _point;
        float x;
        float y;
    End

    _point point[2] = 1,2,// an array of 3 points at positions (1,2), (3,4) and (5,6)
                      3,4,
                      5,6;

Use them like:

    point[0].x = 0;
    point[1].y = 54.2;
    point[2].x = point[0].x;
    point[1].x = point[2].y = 23.2;

### Multiple structs

See [Struct](#Struct).
