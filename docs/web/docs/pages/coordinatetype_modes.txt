Definition
----------

Coordinatetype modes are used to set the type of coordinatesytem to be
used, by assigning them to the [local
variable](local_variable "wikilink") [ctype](ctype "wikilink").
Different coordinatesystems have different ways of interpreting the
coordinates of a process. There's another local variable which
influences the interpretation of a process' coordinate, which is
[resolution](resolution_(local) "wikilink").

How to change in which individual [scroll](scroll "wikilink") or
[Mode7](Mode7 "wikilink")-view the process is visible, see
[cnumber](cnumber "wikilink") and [its
constants](Coordinatenumber_flags "wikilink").

List
----

  ------------ ----------- --------------------------------------------------------------------------------------------
  *Constant*   - *Value*   - *Relative to*
  C\_SCREEN    - 0         - The [screen](screen "wikilink")'s top left corner, coordinate (0,0).
  C\_SCROLL    - 1         - The foreground graphic of the [scroll](scroll "wikilink") in which the process is shown.
  C\_M7        - 2         - The main graphic of the [Mode7](Mode7 "wikilink")-view.
  ------------ ----------- --------------------------------------------------------------------------------------------

<Category:constantcategories>
