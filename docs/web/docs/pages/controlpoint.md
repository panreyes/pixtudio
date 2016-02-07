Definition
----------

Native bennu map files have a special propetry, wich is an
[Array](Array "wikilink") of controlpoints. A controlpoint has an
[X](X "wikilink") and [Y](Y "wikilink") coordinate, and a number. A map
can have up to 1000 controlpoints, ranging from 0 to 999. Controlpoint 0
is always the center of the bitmap by default, but this can be changed
with the [Center\_set](Center_set "wikilink")() function.

The controlpoints 1-999 are optional and can be created with the
[Point\_set](Point_set "wikilink")() function, and read with the
[Point\_get](Point_get "wikilink")() function. It is also possible to
change the controlpoints of the maps inside and [FPG](FPG "wikilink")
archive. Besides changing the controlpoints in a program, they can also
be edited with fpg editors like [Smart FPG
Editor](http://code.google.com/p/smartfpgeditor/).

See also
--------

-   [MAP Format Specification](MAP_Format_Specification "wikilink")
-   [map\_new](map_new "wikilink")()
-   [map\_load](map_load "wikilink")()
-   [map\_save](map_save "wikilink")()
-   [map\_unload](map_unload "wikilink")()
-   [Center\_set](Center_set "wikilink")()
-   [Point\_set](Point_set "wikilink")()
-   [Point\_get](Point_get "wikilink")()

<Category:controlpoints>
