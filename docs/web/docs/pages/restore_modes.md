Definition
----------

Restore modes are used to define the type of restoration, needed to be
applied to the screen background, by assigning them to the [global
variable](global_variable "wikilink")
[restore\_type](restore_type "wikilink"). This influences if and how the
background is restored after each frame.

List
----

  ------------------- ----------- --------------------------------------------------------------------------------------------------------
  *Constant*          - *Value*   - *Description*
  NO\_RESTORE         - -1        - The background won't be restored (i.e. redrawn).
  PARTIAL\_RESTORE    - 0         - The background will be restored in areas where graphics have been painted or text written (default).
  COMPLETE\_RESTORE   - 1         - The background will be completely restored.
  ------------------- ----------- --------------------------------------------------------------------------------------------------------

Notes
-----

It is clear that completely restoring the background every frame is more
expensive than updating only parts of it. However, detecting what parts
need updating is no small thing either. So cost-wise both have their
situations in which they are good.

PARTIAL\_RESTORE is useful if there is relatively not much changing to
the background. COMPLETE\_RESTORE is useful if many parts of the
background need restoration, like in the case of screen-wide partially
transparent scrolls.

Be certain [dump\_type](dump_type "wikilink") is compatible with the
restore\_type set, because some combinations can cause probably unwanted
effects.

See also
--------

-   [restore\_type](restore_type "wikilink")
-   [dump\_type](dump_type "wikilink")
-   [dump\_modes](dump_modes "wikilink")

<Category:constantcategories>
