Definition
----------

Render flags are [bit flags](bit_flags "wikilink") used to specify the
mode of rendering, by passing them to the function
[set\_mode](set_mode "wikilink")() as the flags parameter. Multiple
render flags can be specified using "|" (pipe character) for separation.

See also [graph\_modes](graph_modes "wikilink").

List
----

  -------------------- ----------- ---------------------------------------------------------------------------------------
  *Constant*           - *Value*   - *Description*
  MODE\_WINDOW         - 0         - Enables window view.
  MODE\_2XSCALE        - 256       - Doubles the resolution. Edges get smoothed using the scale2x algorithm.
  MODE\_FULLSCREEN     - 512       - Enables fullscreen view.
  MODE\_DOUBLEBUFFER   - 1024      - Enables using a double buffer for display. Also called DOUBLE\_BUFFER.
  MODE\_HARDWARE       - 2048      - Enables writing directly to Video RAM instead of main RAM. Also called HW\_SURFACE.
  MODE\_MODAL          - 4096      - Makes the main window a Modal window.
  MODE\_FRAMELESS      - 8192      - Makes the main window borderless.
  MODE\_WAITVSYNC      - 16384     - Synchronize with vertical retrace. Also called WAITVSYNC.
  -------------------- ----------- ---------------------------------------------------------------------------------------

More info
---------

-   MODE\_HARDWARE can cause some operations to speed up and some to
    slow down.

<!-- -->

-   MODE\_DOUBLEBUFFER can cause frame transitions to be smoother.
    However, compatibility with [restore\_type =
    partial\_restore](restore_modes "wikilink") is lost!

<!-- -->

-   MODE\_MODAL causes the main window to stay focused and hold
    the mouse.

<Category:constantcategories>
