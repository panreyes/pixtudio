Syntax
------

**INT** set\_mode ( &lt;**INT** width&gt; , &lt;**INT** height&gt; ,
\[&lt;**INT** depth&gt;\] , \[&lt;**INT** flags&gt;\] )

Description
-----------

Sets the screen resolution of your program, and optionally the
colordepth of the screen and any [render flags](render_flags "wikilink")
for extra options. If this command is not used, the default settings
will take effect (320x240 at 32 bpp).

Some much used resolutions are: 320x240, 640x480, 800x600, 1024x768 and
1280x1024.

Parameters
----------

  ------------------- ------------------------------------------------------------------------------------------------------
  **INT** width       - Width of the screen in [pixels](pixel "wikilink").
  **INT** height      - Height of the screen in [pixels](pixel "wikilink").
  **INT** \[depth\]   - [Color depth](Color_depth "wikilink") of the screen. See [color\_depths](color_depths "wikilink").
  **INT** \[flags\]   - Mode of rendering. See [render flags](render_flags "wikilink").
  ------------------- ------------------------------------------------------------------------------------------------------

Returns
-------

  --------------------------------------------------
  **INT** : -1: error, setting the mode has failed
  **INT** : 0: sucess
  --------------------------------------------------

**INT** : [true](true "wikilink") (in versions prior rc282)

Notes
-----

Any fpg files you load must have the same or a lower colordepth as you
set for the screen.

Uncommon resolutions can also be used, for example 399x10, which will be
the actual size of the window if you run in windowed mode. At full
screen black edges might appear.

There is another method of calling set\_mode(): with one parameter. In
this parameter you must use the 4 right digits for the height and the
rest fot the width. For example to set a 320x200 mode you can use
set\_mode(3200200). The maximum height that allow this method is 9999
pixels. This method is **deprecated** and its use is disadvised.

Example
-------

    import "mod_video"
    import "mod_key"
    import "mod_wm"

    Process Main()
    Begin
        set_mode(640,480,16);
        Repeat
            frame;
        Until(key(_ESC)||exit_status)

    End

Used in example: [set\_mode](set_mode "wikilink")(),
[key](key "wikilink")(), [exit\_status](exit_status "wikilink")

<Category:functions> <Category:programinteraction> <Category:mod_video>
