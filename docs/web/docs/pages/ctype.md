<category:variables> <category:predefined> [category:local
variables](category:local_variables "wikilink") <category:libscroll>
<category:librender>

[**Up to Local Variables**](Local_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

Coordinatetype modes are used to set the type of coordinatesytem to be
used, by assigning them to the [local
variable](local_variable "wikilink") [ctype](ctype "wikilink").
Different coordinatesystems have different ways of interpreting the
coordinates of a process. There's another local variable which
influences the interpretation of a process' coordinate, which is
[Resolution](Resolution "wikilink").

How to change in which individual [scroll](scroll "wikilink") or
[Mode7](Mode7 "wikilink")-view the process is visible, see
[C\_number](C_number "wikilink") and [its
constants](Coordinatenumber_flags "wikilink").

List
----

  ------------ ----------- --------------------------------------------------------------------------------------------
  *Constant*   - *Value*   - *Relative to*
  C\_SCREEN    - 0         - The [ screen](SCREEN "wikilink")'s top left corner, coordinate (0,0).
  C\_SCROLL    - 1         - The foreground graphic of the [scroll](scroll "wikilink") in which the process is shown.
  C\_M7        - 2         - The main graphic of the [Mode7](Mode7 "wikilink")-view.
  ------------ ----------- --------------------------------------------------------------------------------------------


