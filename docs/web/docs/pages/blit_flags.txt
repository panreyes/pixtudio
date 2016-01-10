Definition
----------

Blit flags are [bit flags](bit_flags "wikilink") which can be passed to
some [map functions](:Category:Maps "wikilink"), to specify a certain
effect when [blitting](blit "wikilink") a [graphic](graphic "wikilink").
These functions are:

-   [xput](xput "wikilink")()
-   [map\_xput](map_xput "wikilink")()
-   [map\_xputnp](map_xputnp "wikilink")()

They can also be used to specify a certain effect for the blitting of
the graphic of a [process](process "wikilink"), by assigning blit flags
to its [local variable](local_variable "wikilink")
[flags](flags "wikilink").

List
----

  ---------------- ----------- -------------------------------------------------------------------------
  *Constant*       - *Value*   - *Description*
  B\_HMIRROR       - 1         - Blit the graph horizontally mirrored.
  B\_VMIRROR       - 2         - Blit the graph vertically mirrored.
  B\_TRANSLUCENT   - 4         - Blit the graph with half transparency.
  B\_ALPHA         - 8         - Blit the graph in some way. (*What does this do exactly?*)
  B\_ABLEND        - 16        - Blit the graph using additive blending (nice effect for fire).
  B\_SBLEND        - 32        - Blit the graph using subtractive blending (nice effect for ghosting).
  B\_NOCOLORKEY    - 128       - Blit the transparent parts of the graph as black (color 0).
  ---------------- ----------- -------------------------------------------------------------------------

<Category:constantcategories>
