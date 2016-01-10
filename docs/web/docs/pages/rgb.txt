Syntax
------

**DWORD** rgb ( &lt;**BYTE** red&gt; , &lt;**BYTE** green&gt; ,
&lt;**BYTE** blue&gt; , \[&lt;**INT** depth&gt;\] )

Description
-----------

Finds the single [color](color "wikilink") in the current color mode
closest to the combined red, green, and blue values specified. In 32bit
mode, the alpha is set to 255.

Equal to `[[rgba]](''red'',''green'',''blue'',255)`

Parameters
----------

  ---------------- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  **BYTE** red     - Level of red in the desired color from 0 to 255.
  **BYTE** green   - Level of green in the desired color from 0 to 255.
  **BYTE** blue    - Level of blue in the desired color from 0 to 255.
  **INT** depth    - Depth (optional paramter that may be omitted, only in 16 and 32 bit mode). When this parameter is used, the function returns the correct color code for the indicated depth.
  ---------------- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Returns
-------

**DWORD** : Returns the best matched color code.

Notes
-----

Different color depths have different color codes, this is why rgb() is
useful: it returns the appropriate code, based on the current color
depth. When in 8bit mode, this code is 0..255 and when in 16bit mode
0..65535. In 32bit mode the code is 0xRRGGBBAA, two letters meaning one
byte.

Using this function in different color depths can be tricky. This is
because rgb() will return a different color code under different color
depths. For example, when at 8bit, we do:

    my_color = rgb(100,100,100);

my\_color will most likely have the value *6* at this time. Suppose we
change the color depth to 16bit now, using
[set\_mode](set_mode "wikilink")(). Now, my\_color holds a totally
different color than before, as *6* is nowhere near rgb(100,100,100) in
16bit mode. To counter this effect, my\_color needs to be reinitialized:

    my_color = rgb(100,100,100);

The same code, but rgb() now returns the proper code, as it always
returns the code belonging to the current color depth. my\_color will
now be about *25388*.

Example
-------

    import "mod_map"
    import "mod_text"
    import "mod_key"
    import "mod_wm"

    Process Main()
    Private
        byte red=0;
        byte green=255;
        byte blue=0;
    Begin
        
        set_text_color(rgb(red,green,blue)); // rgb finds the color closest to pure green and
                                             // passes it to set_text_color

        write(0,1,1,0,"Green text for everybody!"); //this text will be green
            
        Repeat
            frame;
        Until(key(_ESC)||exit_status)

    End

Used in example: [set\_text\_color](set_text_color "wikilink")(),
[rgb](rgb "wikilink")(), [write](write "wikilink")(),
[key](key "wikilink")(), [exit\_status](exit_status "wikilink")

<Category:functions> <Category:palettes> <Category:mod_map>
