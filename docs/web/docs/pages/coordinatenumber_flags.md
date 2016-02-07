Definition
----------

Coordinatenumber flags are used to set which [scroll](scroll "wikilink")
or [mode\_7](mode_7 "wikilink") coordinate system should display a
[process](process "wikilink"), by assigning them to the [local
variable](local_variable "wikilink") [cnumber](cnumber "wikilink") of
that process. This only has influence on scrolls or mode\_7 coordinate
systems, not on the screen's coordinate system.

How to change the used coordinate system, see [ctype](ctype "wikilink")
and [its constants](Coordinatetype_modes "wikilink").

List
----

  ------------ ----------- -------------------------------------------------------------
  *Constant*   - *Value*   - *Description*
               - 0         - Display the process in all scroll/mode\_7-views (default)
  C\_0         - 1         - Display the process in the scroll/mode\_7-view with ID 0
  C\_1         - 2         - Display the process in the scroll/mode\_7-view with ID 1
  C\_2         - 4         - Display the process in the scroll/mode\_7-view with ID 2
  C\_3         - 8         - Display the process in the scroll/mode\_7-view with ID 3
  C\_4         - 16        - Display the process in the scroll/mode\_7-view with ID 4
  C\_5         - 32        - Display the process in the scroll/mode\_7-view with ID 5
  C\_6         - 64        - Display the process in the scroll/mode\_7-view with ID 6
  C\_7         - 128       - Display the process in the scroll/mode\_7-view with ID 7
  C\_8         - 256       - Display the process in the scroll/mode\_7-view with ID 8
  C\_9         - 512       - Display the process in the scroll/mode\_7-view with ID 9
  ------------ ----------- -------------------------------------------------------------

<Category:constantcategories>
