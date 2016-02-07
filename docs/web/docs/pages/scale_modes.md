Definition
----------

Scale modes are used to set the mode of scaling, by assigning one of
them to the [global variable](global_variable "wikilink")
[scale\_mode](scale_mode "wikilink").

List
----

  ------------------- ----------- ------------------------------------------------------------------
  *Constant*          - *Value*   - *Description*
  SCALE\_NONE         - 0         - No scale.
  SCALE\_SCALE2X      - 1         - Scale two times; use some filter. Looks like MODE\_2XSCALE.
  SCALE\_HQ2X         - 2         - Scale two times; use HQ filter. Looks nice, runs slower.
  SCALE\_SCANLINE2X   - 3         - Scale two times; use scanline filter.
  SCALE\_NORMAL2X     - 4         - Scale two times; no extra filter. Also called SCALE\_NOFILTER.
  ------------------- ----------- ------------------------------------------------------------------

<Category:constantcategories>
