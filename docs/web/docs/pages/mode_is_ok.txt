Definition
----------

**INT** mode\_is\_ok ( &lt;**INT** width&gt; , &lt;**INT** height&gt; ,
&lt;**INT** depth&gt;, &lt;**INT** flags&gt; )

Returns 0 if the requested mode is not supported under any bit depth,or
returns the bits-per-pixel of the closest available mode with the given
width, height and requested flags.

Parameters
----------

  ---------------- ------------------------------------------------------------------------------------------------------
  **INT** width    - Width of the screen in [pixels](pixel "wikilink").
  **INT** height   - Height of the screen in [pixels](pixel "wikilink").
  **INT** depth    - [Color depth](Color_depth "wikilink") of the screen. See [color\_depths](color_depths "wikilink").
  **INT** flags    - Mode of rendering. See [render flags](render_flags "wikilink").
  ---------------- ------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : Whether the specified mode can be used.

  ------- -------------------------------------------------------------------------------------------
  0       - The specified mode cannot be used.
  &gt;0   - The bits-per-pixel of the closest available mode for the given width, height and flags.
  ------- -------------------------------------------------------------------------------------------

Example
-------

    import "mod_video"
    import "mod_key"
    import "mod_wm"

    Process Main()
    Begin
        if (is_mode_ok(640,400,16,0))
         set_mode(640,400,16);
        else
         set_mode(640,480,16);
        end
        Repeat
            frame;
        Until(key(_ESC)||exit_status)
    End

Used in example:
[is\_mode\_ok](is_mode_ok "wikilink")(),[set\_mode](set_mode "wikilink")(),
[key](key "wikilink")(), [exit\_status](exit_status "wikilink")

<Category:functions> <Category:programinteraction> <Category:mod_video>
