Definition
----------

Dump modes are used to define the type of dump, needed to be applied to
the screen, by assigning them to the [global
variable](global_variable "wikilink")
[dump\_type](dump_type "wikilink"). This influences when and if
[graphics](graphic "wikilink") of processes are drawn to the screen.

List
----

  ---------------- ----------- ----------------------------------------------------------------------------------------------------
  *Constant*       - *Value*   - *Description*
  PARTIAL\_DUMP    - 0         - Only graphics of updated (changed) [processes](processes "wikilink") will be drawn (default).
  COMPLETE\_DUMP   - 1         - Graphics of all [processes](processes "wikilink") will be drawn, whether they've changed or not.
  ---------------- ----------- ----------------------------------------------------------------------------------------------------

Notes
-----

It is clear that completely drawing all processes every frame is more
expensive then updating only some of them. This mode can be useful
still, because partially drawing processes can cause probably unwanted
effects in some situations, mostly in combination with a certain
[restore\_modes](restore_modes "wikilink"). However, if you experience
no such thing, you can use the partial drawing.

PARTIAL\_DUMP is useful if there is relatively not much changing to
processes and when there are a lot of processes that don't need
updating. COMPLETE\_DUMP is useful if most processes need updating.

Be certain [restore\_type](restore_type "wikilink") is compatible with
the dump\_type set, because some combinations can cause probably
unwanted effects.

See also
--------

-   [dump\_type](dump_type "wikilink")
-   [restore\_type](restore_type "wikilink")
-   [restore\_modes](restore_modes "wikilink")

<Category:constantcategories>
