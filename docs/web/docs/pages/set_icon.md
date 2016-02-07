Definition
----------

**INT** set\_icon ( &lt;**INT** fileID&gt; , &lt;**INT** graphID&gt; )

Set the window icon to a certain graph.

The icon will only be updated after [set\_mode](set_mode "wikilink")()
is called, so call set\_icon() before set\_mode(). The map used for the
icon must be 32x32 large, but it can have different depths. After
set\_icon() and set\_mode() have been called, the map used for the icon
can be freed from memory using [unload\_map](unload_map "wikilink")().

Parameters
----------

  ----------------- ---------------------------------------------------------------------------------------
  **INT** fileID    - The fileID of the [file](file "wikilink") containing the [graph](graph "wikilink").
  **INT** graphID   - The graphID of the graph to be used as an icon.
  ----------------- ---------------------------------------------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Example
-------

    import "mod_key"
    import "mod_map"
    import "mod_wm"
    import "mod_video"

    Const
        screen_width  = 320;
        screen_height = 200;
        screen_depth  =  16;
    End

    Process Main()
    Private
        int map;
        int iconsize      =  32;
    Begin

        set_mode(screen_width,screen_height,screen_depth);

        map = new_map(iconsize,iconsize,screen_depth);
        map_clear(0,map,rgb(0,255,255));

        set_title("<-- Look at the cyan block!");
        set_icon(0,map);

        unload_map(0,map);

        Repeat
            frame;
        Until(key(_ESC)||exit_status)

    End

Used in example: [set\_mode](set_mode "wikilink")(),
[new\_map](new_map "wikilink")(), [map\_clear](map_clear "wikilink")(),
[rgb](rgb "wikilink")(), [set\_title](set_title "wikilink")(),
[set\_icon](set_icon "wikilink")(),
[unload\_map](unload_map "wikilink")(), [key](key "wikilink")(),
[exit\_status](exit_status "wikilink")

<Category:functions> <Category:programinteraction> <Category:mod_wm>
