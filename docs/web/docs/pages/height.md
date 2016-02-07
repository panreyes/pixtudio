<category:variables> <category:predefined> [category:local
variables](category:local_variables "wikilink") <category:libscroll>
<category:librender>

[**Up to Local Variables**](Local_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

The predefined local variable height is used in
[Mode7](Mode7 "wikilink") windows, and it is assigned to each process.
It is therefore only relevant in the coordinate system of mode7
([Ctype](Ctype "wikilink")=[C\_M7](C_M7 "wikilink")). It is used to
define the height of the process graphics in relation to the semi-3d
field. This is not to be confused with the local variable
[Z](Z "wikilink"), as that is used to control the depth of the graphical
layers.

The height is normally a positive number, because the height of the
bottom is 0, and all the processes are placed above it. When the height
variable is not defined, it is 0 by default. The graphic base is placed
at the indicated height, with the exception when
[controlpoint](controlpoint "wikilink") number 0 is changed (the default
is overruled by the [Center\_set](Center_set "wikilink")() function). In
that case, the controlpoint will be placed at that height.
