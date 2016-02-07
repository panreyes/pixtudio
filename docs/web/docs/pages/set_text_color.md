Definition
----------

**INT** set\_text\_color ( \[**INT** &lt; textID&gt;\] , &lt;**WORD**
color&gt; )

Sets the current text color (the color where texts will be written in).
This only affects 1 bit (2 color) fonts, which can be loaded with
[load\_font](load_font "wikilink")() or
[load\_bdf](load_bdf "wikilink")(). 8 bit and 16 bit fonts already
contain color information themselves and thus aren't affected.

Parameters
----------

  ---------------- ---------------------------------------------------
  **INT** textID   - The identification code of the text (optional).
  **WORD** color   - The [color](color "wikilink") to use for text.
  ---------------- ---------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink") if successful and
[false](false "wikilink") if failed. (*Needs confirmation.*)

**VOID**: in version rc282 this function returns nothing.

Notes
-----

Be warned that values returned by the [Rgb](Rgb "wikilink")() function
differ with the video card. So, directly filling out color numbers as
color parameter in 16 bit color mode without using
[Rgb](Rgb "wikilink")() is a bad idea, as RGB returns the correct color
code for every video card

*The optional argument textID is fairly new. It is introduced in version
rc282.*

Errors
------

None.

Example
-------

    Program awesome;
    Global
        byte red=0;
        byte green=255;
        byte blue=0;

    Begin
        
        set_text_color(rgb(red,green,blue));
        write(0,1,1,0,"Mijn potlood is bruin"); //this text will be green as an Irishman's ejecta

        set_text_color(rgb(255,0,0));
        write(0,1,11,0,"Je moeder"); //this text will be red
            
        Loop
      
            frame;
        End
    End

Used in example: [write](write "wikilink")(), [rgb](rgb "wikilink")()

This results in something like this:\
![](set_text_color.png "fig:set_text_color.png")

Example 2
---------

    import "mod_text";
    import "mod_mouse";
    import "mod_key";
    import "mod_video";
    import "mod_rand";
    import "mod_map";

    private
        txt[10];
        counter;
        tz;
    begin
        set_mode(640,480,32);

        txt[0]=write_int(0,10,10,10,0,&counter);
        txt[1]=write_int(0,10,20,-5,0,&tz);
        txt[2]=write(0,10,10,0,0,"hello world");

        set_text_color(txt[1], rgb(255,0,0));


        while(!key(_ESC))

            counter++;

            move_text(txt[2], mouse.x, mouse.y, tz );

            set_text_color(txt[0], rand(0101010h, 0ffffffh));

            if ( key( _DOWN ) ) tz--; end
            if ( key( _UP ) ) tz++; end

            frame;
        end
    end

Used in example: [write](write "wikilink")(),
[write\_int](write_int "wikilink")(), [rgb](rgb "wikilink")(),
[key](key "wikilink")(), [set\_mode](set_mode "wikilink")(),
[move\_text](move_text "wikilink")()

<Category:functions> <Category:texts> <Category:mod_text>
