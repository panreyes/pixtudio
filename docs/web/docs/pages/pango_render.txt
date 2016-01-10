This function is part of the [Pango library](DLL:Pango.dll "wikilink").

Syntax
------

**INT** pango\_render ( &lt;**STRING** markup&gt; )

Description
-----------

Returns a [graphic](graphic "wikilink") with the specified markup
rendered on it. The markup is expected to be a UTF-8 encoded string;
markup accepted by the Pango BennuGD binding is the same as upstream
Pango's and can be consulted
[here](http://library.gnome.org/devel/pango/stable/PangoMarkupFormat.html).

In case of failure, a 0x0 sized graphic will be returned.

After usage, unload the graphic with
[map\_unload](map_unload "wikilink")().

Parameters
----------

  ------------------- --------------------------------------
  **STRING** markup   - The markup to render to a graphic.
  ------------------- --------------------------------------

Returns
-------

**INT** : [GraphID](GraphID "wikilink")

  ------- -----------------------------------------------------------------------------------------------
  0       - There was some error. Pango tends to drop error on stdout, so check your terminal for them.
  &gt;0   - The graphID of a new graphic with the specified markup rendered on it.
  ------- -----------------------------------------------------------------------------------------------

Example
-------

    import "mod_say";
    import "mod_key";
    import "mod_video";
    import "mod_map";
    import "mod_mouse";
    import "mod_text";

    import "pango";

    Process main()
    Private
        int retval=0;
        string markup = '<span foreground="blue" background="black">e=mc<sup>2</sup></span>';
    Begin

        set_mode(640, 480, 32, MODE_WINDOW);

        // If given and argument, render that instead of the default text
        if(argc == 2)
            markup = '<span font_family="Serif" size="xx-large" foreground="blue" background="black"><u>'+argv[1]+'</u></span>';
        end;

        say("Going to render:");
        say(markup);

        // Render the markup and move it with the mouse
        graph = pango_render(markup);
        write_var(0, 0, 0, 0, x);
        write_var(0, 0, 10, 0, y);

        // Wait for escape key
        while(! key(_ESC))
            x = mouse.x;
            y = mouse.y;
            FRAME;
        End;

    OnExit

        unload_map(0, graph);

    End

Used in example: [import](import "wikilink")(),
[set\_mode](set_mode "wikilink")(), [say](say "wikilink")(),
[pango\_render](pango_render "wikilink")(),
[write\_var](write_var "wikilink")(), [key](key "wikilink")(),
[unload\_map](unload_map "wikilink")(), [mouse](mouse "wikilink")

<Category:functions> <Category:pangodll>
