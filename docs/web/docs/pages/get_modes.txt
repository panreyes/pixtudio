Syntax
------

**POINTER** get\_modes ( &lt;**INT** depth&gt;, &lt;**INT** flags&gt; )

Description
-----------

Returns a pointer to an array of available screen dimensions for the
given [depth](depth "wikilink") and [render
flags](render_flags "wikilink"), sorted largest to smallest.

Returns NULL if there are no dimensions available for a particular
format, or -1 if any dimension is okay for the given format.

Parameters
----------

  --------------- ------------------------------------------------------------------------------------------------------
  **INT** depth   - [Color depth](Color_depth "wikilink") of the screen. See [color\_depths](color_depths "wikilink").
  **INT** flags   - Mode of rendering. See [render flags](render_flags "wikilink").
  --------------- ------------------------------------------------------------------------------------------------------

Returns
-------

**POINTER** : A pointer to an array of available screen dimensions

Example
-------

    import "mod_say";
    import "mod_video";

    Process Main()
    Private
        int * modes;
    Begin
        // Modes will point to an array whose values are acceptable values for resolution

        // Get 8bpp acceptable modes when in fullscreen
        modes = get_modes(8, MODE_FULLSCREEN);
        say ("8bit modes");
        say ("----------");
        if (!modes)
            say ("no video modes available!");
        elsif (modes == -1 )
            say ("any video mode available!");
        else
            while (*modes)
                say ("> " + *modes++ + " x " + *modes++ );
            end
        end
        say ("");

        // Get 16bpp acceptable modes when in fullscreen
        modes = get_modes(16, MODE_FULLSCREEN);
        say ("16bit modes");
        say ("-----------");
        if (!modes)
            say ("no video modes available!");
        elsif (modes == -1 )
            say ("any video mode available!");
        else
            while (*modes)
                say ("> " + *modes++ + " x " + *modes++ );
            end
        end
        say ("");

        // Get 24bpp acceptable modes when in fullscreen
        modes = get_modes(24, MODE_FULLSCREEN);
        say ("24bit modes");
        say ("-----------");
        if (!modes)
            say ("no video modes available!");
        elsif (modes == -1 )
            say ("any video mode available!");
        else
            while (*modes)
                say ("> " + *modes++ + " x " + *modes++ );
            end
        end
        say ("");

        // Get 32bpp acceptable modes when in fullscreen
        modes = get_modes(32, MODE_FULLSCREEN);
        say ("32bit modes");
        say ("-----------");
        if (!modes)
            say ("no video modes available!");
        elsif (modes == -1 )
            say ("any video mode available!");
        else
            while (*modes)
                say ("> " + *modes++ + " x " + *modes++ );
            end
        end
        say ("");

    End

Used in example: [say](say "wikilink")(),
[MODE\_FULLSCREEN](Render_flags "wikilink")

<Category:functions> <Category:programinteraction> <Category:mod_video>
