Definition
----------

Graph modes are used to specify the color depth of the screen and the
mode of rendering, by assigning them to the [global
variable](global_variable "wikilink")
[graph\_mode](graph_mode "wikilink"). This is also achieved by passing
them to the [parameters](parameter "wikilink") depth and flags in the
function [set\_mode](set_mode "wikilink")(), which is a pretty tidy
solution.

List
----

[Color depths constants](Color_depths "wikilink"):

  -------------- ----------- --------------------------------------------------------
  *Constant*     - *Value*   - *Description*
  MODE\_8BITS    - 8         - Use a color depth of 8bit. Also called MODE\_8BPP.
  MODE\_16BITS   - 16        - Use a color depth of 16bit. Also called MODE\_16BPP.
  -------------- ----------- --------------------------------------------------------

[Render flags constants](Render_flags "wikilink"):

  -------------------- ----------- ---------------------------------------------------------------------------------------
  *Constant*           - *Value*   - *Description*
  MODE\_WINDOW         - 0         - Enables window view.
  MODE\_2XSCALE        - 256       - Doubles the resolution. Edges get smoothed.
  MODE\_FULLSCREEN     - 512       - Enables fullscreen view.
  MODE\_DOUBLEBUFFER   - 1024      - Enables using a double buffer for display. Also called DOUBLE\_BUFFER.
  MODE\_HARDWARE       - 2048      - Enables writing directly to Video RAM instead of main RAM. Also called HW\_SURFACE.
  MODE\_MODAL          - 4096      - Makes the main window a Modal window.
  MODE\_FRAMELESS      - 8192      - Makes the main window borderless.
  -------------------- ----------- ---------------------------------------------------------------------------------------

<Category:constantcategories>
