<category:variables> <category:predefined> [category:local
variables](category:local_variables "wikilink") <category:internal>

[**Up to Local Variables**](Local_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**Struct** Reserved

Reserved is a [local variable](local "wikilink")
[struct](struct "wikilink"), containing information that is reserved for
[Bennu](Bennu "wikilink")'s internals. However, sometimes you may wish
to use certain members of it. Using in the sense of reading only, **do
not under any circumstances alter their values, unless you know what you
are doing**.

If it's not documented what these members do, their use is reasonably
limited. If you want to know what these members do, your programming
goals are of a level, where you can also look in the
[sourcecode](Latest_Bennu_version "wikilink"). This is because most of
these members would require a lengthy explanation about what they do and
why.

Members
-------

  ------------------------ ------------------------------------------------------------------------------------------------------------------------------------------
  *Member name*            - *Description*
  **INT** ID\_scan         - Internal use only (formerly [got](get_id "wikilink") [processID](processID "wikilink") from within the [process](process "wikilink")).
  **INT** process\_type    - The [ProcessTypeID](ProcessTypeID "wikilink") of the process.
  **INT** type\_scan       - Internal use only (formerly [got](get_id "wikilink") [processTypeID](processTypeID "wikilink") from within the process).
  **INT** status           - The status of the process, containing a [status code](Process_statuscodes "wikilink").
  **INT** changed          - Internal use only.
  **INT** xgraph\_flags    - Internal use only ([blit flags](blit_flags "wikilink") for [xgraph](xgraph "wikilink")).
  **INT** saved\_status    - Internal use only (for [signals](signals "wikilink")).
  **INT** prev\_z          - Previous [z](z "wikilink") value.
  **INT** distance1        - Not used.
  **INT** distance2        - Not used.
  **INT** frame\_percent   - Internal use only.
  **INT** box\_x0          - The x-coordinate of the topleft corner of the process' [graphic](graphic "wikilink") (process.x-graphic.width/2).
  **INT** box\_y0          - The y-coordinate of the topleft corner of the process' graphic (process.y-graphic.height/2).
  **INT** box\_x1          - The x-coordinate of the bottomright corner of the process' graphic (process.x+graphic.width/2).
  **INT** box\_y1          - The y-coordinate of the bottomright corner of the process' graphic (process.y+graphic.height/2).
  ------------------------ ------------------------------------------------------------------------------------------------------------------------------------------


