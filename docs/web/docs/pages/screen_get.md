Definition
----------

**INT** screen\_get ( )

Creates a new [graphic](graphic "wikilink") containing a copy of the
lastly rendered frame.

The map will contain everything, including background,
[processes](process "wikilink"), [drawings](draw "wikilink") and
[text](text "wikilink"). Just like [map\_new](map_new "wikilink")(), the
newly created graphic will be located in the [System
file](System_file "wikilink") ([fileID](fileID "wikilink") of *0*); the
[graphID](graphID "wikilink") will be returned. After the use of this
graphic, it should be freed using
[map\_unload](map_unload "wikilink")().

Also called [get\_screen](get_screen "wikilink")().

Returns
-------

**INT** : [GraphID](GraphID "wikilink")

  ------- -----------------------------------------------------------------------------------
  0       - Some error.
  &gt;0   - The [GraphID](GraphID "wikilink") of the [graphic](graphic "wikilink") created.
  ------- -----------------------------------------------------------------------------------

Example
-------

    import "mod_key"
    import "mod_screen"
    import "mod_map"

    Global
        int my_map;
    End

    Process Main()
    Begin
        Repeat
            if(key(_F5))
                my_map = screen_get();
                png_save(0,my_map,"snapshot.PNG");
                map_unload(0,my_map);
                while(key(_F5)) frame; end
            end
            frame;
        Until(key(_ESC))
    End

Used in example: [key](key "wikilink")(),
[screen\_get](screen_get "wikilink")(),
[png\_save](png_save "wikilink")(),
[map\_unload](map_unload "wikilink")()

<Category:functions> <Category:screen> <Category:mod_screen>
