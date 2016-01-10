<category:variables> <category:predefined> [category:global
variables](category:global_variables "wikilink") <category:mod_key>

[**Up to Global Variables**](Global_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** shift\_status

Shift\_status is defined in the module [mod\_key](mod_key "wikilink")
and indicates whether a modifier key is being pressed. If more than a
modifier key is pressed at the same time shift\_status will return the
sum.

List
----

  --------------- -----------
  *Key*           - *Value*
  Right Control   - 20 \*
  Left Control    - 36
  Right Alt       - 72 \*
  Left Alt        - 136
  NUM LOCK        - 256
  CAPS LOCK       - 512
  Right Shift     - 1025
  Left Shift      - 1026
  --------------- -----------

`* At the time of the writing of this article, right alt and right control didn't return anything. It is unknown whether it is a bug or just deprecated.`
