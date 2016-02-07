Syntax
------

**DWORD** rgba ( &lt;**BYTE** red&gt; , &lt;**BYTE** green&gt; ,
&lt;**BYTE** blue&gt;, &lt;**BYTE** alpha&gt; , \[&lt;**INT**
depth&gt;\] )

Description
-----------

Finds the single [color](color "wikilink") in the current color mode
closest to the combined red, green, blue and alpha values specified.
This function is useful in 32 bpp modes.

Parameters
----------

  ---------------- ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  **BYTE** red     - Level of red in the desired color from 0 to 255.
  **BYTE** green   - Level of green in the desired color from 0 to 255.
  **BYTE** blue    - Level of blue in the desired color from 0 to 255.
  **BYTE** alpha   - Level of alpha in the desired color from 0 to 255, 0 being completely transparent and 255 completely opaque.
  **INT** depth    - Optional parameter, wich may be omitted. Only usefull in 16 and 32 bit modes, ensures that the function returns a colorcode that is valid for the specified mode.
  ---------------- ---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Returns
-------

**DWORD** : Returns the best matched color code.

Notes
-----

Different color depths have different color codes, this is why rgba() is
useful: it returns the appropriate code, based on the current color
depth. When in 8bit mode, this code is 0..255 and when in 16bit mode
0..65535. In 32bit mode the code is 0xRRGGBBAA, two letters meaning one
byte.

Using this function in different color depths can be tricky. This is
because rgba() will return a different color code under different color
depths. For example, when at 8bit, we do:

    my_color = rgba(100,100,100,255);

my\_color will most likely have the value *6* at this time. Suppose we
change the color depth to 16bit now, using
[set\_mode](set_mode "wikilink")(). Now, my\_color holds a totally
different color value than before, as *6* is nowhere near
rgba(100,100,100,255) in 16bit mode. To counter this effect, my\_color
needs to be reinitialized:

    my_color = rgba(100,100,100,255);

The same code, but rgba() now returns the proper code, as it always
returns the code belonging to the current color depth. my\_color will
now be about *25388*.

Example
-------

    import "mod_text"
    import "mod_map"
    import "mod_key"
    import "mod_video"
    import "mod_wm"

    Const
        SCREEN_WIDTH  = 320;
        SCREEN_HEIGHT = 200;
        SCREEN_DEPTH  = 16;
    End

    Process Main()
    Private
        int r=0;
        int g=255;
        int b=0;
        int a=0;
        int da=10;
    Begin

        set_mode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH);

        graph = map_new(100,100,SCREEN_DEPTH);
        map_clear(0,graph,rgba(r,g,b,a));

        x = y = 100;

        Repeat
            a += da;
            if(a<0)
                da = -da;
                a = 0;
            elseif(a>255)
                da = -da;
                a = 255;
            end
            map_clear(0,graph,rgba(r,g,b,a));
            frame;
        Until(key(_ESC)||exit_status)

    End

Used in example: [set\_mode](set_mode "wikilink")(),
[map\_new](map_new "wikilink")(), [map\_clear](map_clear "wikilink")(),
[key](key "wikilink")(), [rgba](rgba "wikilink")(),
[graph](graph "wikilink"), [exit\_status](exit_status "wikilink")

<Category:functions> <Category:palettes> <Category:mod_map>
