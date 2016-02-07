Definition
----------

**INT** set\_title ( &lt;**STRING** title&gt; )

Sets the title of the program's window.

The title will only be updated after [set\_mode](set_mode "wikilink")()
is called, so call set\_title() before set\_mode().

Parameters
----------

  ------------------ -------------------------------------------
  **STRING** title   - The new title for the program's window.
  ------------------ -------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Example
-------

    Program icon;
    Private
        int map;
        int screen_width  = 320;
        int screen_height = 200;
        int screen_depth  =   8;
        int iconsize      =  32;
    Begin

        map = new_map(iconsize,iconsize,screen_depth);
        map_clear(0,map,rgb(0,255,255));

        set_icon(0,map);
        set_title("<-- Look at the cyan block!");
        set_mode(screen_width,screen_height,screen_depth);

        unload_map(0,map);

        Repeat
            frame;
        Until(key(_esc))

    End

Used in example: [new\_map](new_map "wikilink")(),
[map\_clear](map_clear "wikilink")(),
[set\_icon](set_icon "wikilink")(), [set\_mode](set_mode "wikilink"),
[unload\_map](unload_map "wikilink")(), [key](key "wikilink")()

<Category:functions> <Category:programinteraction> <Category:mod_wm>
