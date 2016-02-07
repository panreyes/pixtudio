Description
-----------

Colors are widely used in Fenix/Bennu. They are used for example in
[text functions](Functioncategory:texts "wikilink").

In 8 bit color mode, the color corresponds with the palette index
(0..255); in 16 bit color mode the color corresponds with an RGB value
(0..65535): 5 bits for red, 6 bits for green and 5 bits for blue. In
32bit mode the code is 0xRRGGBBAA, two letters meaning one byte: 8 bits
for each component.

The RGB(A) values of a color can be obtained with
[get\_rgb](get_rgb "wikilink")() and [get\_rgba](get_rgba "wikilink")().

Transparency
------------

Note that in many cases the color 0 means **transparent**! Consider the
difference between:

-   [map\_clear](map_clear "wikilink")(file,graph,0); and
-   [map\_clear](map_clear "wikilink")(file,graph,rgb(0,0,0)).

In the first case, the graphic (file,graph) will be made fully
transparent. In the second case, the graphic will be made the blackest
black Bennu can muster, given the current color depth. In 8bit mode,
**both** will be made transparent.

Example
-------

This is a test program to show when a color is black or transparent:

    import "mod_video"
    import "mod_map"
    import "mod_key"
    import "mod_proc"

    Const
        DEPTH = 32;
    End

    Process Main()
    Private
        int map_trans;
        int map_black;
    Begin
        set_mode(320,200,DEPTH);
        
        map_trans = new_map(100,100,DEPTH);
        map_clear(0,map_trans,0);

        map_black = new_map(100,100,DEPTH);
        map_clear(0,map_black,rgb(0,0,0));
        
        map_clear(0,BACKGROUND,rgb(50,50,50));
        
        g(120,100,0,map_trans);
        g(200,100,0,map_black);

        Repeat
            frame;
        Until(key(_ESC))

        let_me_alone();
        
    End

    Process g(int x, int y, int file, int graph)
    Begin
        Loop
            frame;
        End
    End

Used in example: [set\_mode](set_mode "wikilink")(),
[map\_clear](map_clear "wikilink")(), [rgb](rgb "wikilink")(),
[new\_map](new_map "wikilink")(),
[let\_me\_alone](let_me_alone "wikilink")()

See also
--------

-   [rgb](rgb "wikilink")()
-   [rgba](rgba "wikilink")()

