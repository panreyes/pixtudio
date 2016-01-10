Syntax
------

**INT** get\_window\_pos ( &lt;**INT POINTER** x&gt;, &lt;**INT
POINTER** y&gt;)

Description
-----------

Get the X and Y position of the window.

Parameters
----------

  ------------------- --------------------------------------------------------------------
  **INT POINTER** x   - Pointer to where the X-coordinate of the window will be written.
  **INT POINTER** y   - Pointer to where the Y-coordinate of the window will be written.
  ------------------- --------------------------------------------------------------------

Returns
-------

**INT** : Successrate

  --------------------------- --------------------------------
  [false](false "wikilink")   - The system is in fullscreen.
  [true](true "wikilink")     - Success ok.
  --------------------------- --------------------------------

<Category:functions> <Category:programinteraction> <Category:mod_wm>
