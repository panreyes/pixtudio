Definition
----------

**INT** move\_text ( &lt;**INT** TextID&gt; , &lt;**INT** x&gt; ,
&lt;**INT** y&gt;, &lt;**INT** z&gt;)

Moves an existing [text](text "wikilink") to another place on the
screen.

Parameters
----------

  ---------------- ----------------------------------------------------------------------------------------------------------------------------------
  **INT** TextID   - [Identifier of the text](TextID "wikilink") you want to move. This identifier should have been appointed to a text earlier on.
  **INT** x        - The new horizontal coordinate (of the control point) of your text.
  **INT** y        - The new vertical coordinate (of the control point) of your text.
  **INT** z        - The new depthplane (of the control point) of your text. *(introduced in version r282)*
  ---------------- ----------------------------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : TRUE

Notes
-----

The "z" argument is a newer feature, so it is not anvailible in all
versions.

Errors
------

None.

Example
-------

    Program test;
    Global
        My_text;
    Begin
        My_text=write(0,320/2,200/2,4,"Press space to move this.");
        Loop
            If (key(_space))
                Move_text(My_text,rand(0,319),rand(0,199));
            End
            Frame;
        End
    End

Used in example: [write](write "wikilink")(), [key](key "wikilink")(),
[rand](rand "wikilink")()

This will result in something like:\
![](Move_text.png "fig:Move_text.png")

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
[write\_int](write_int "wikilink")(), [key](key "wikilink")(),
[rand](rand "wikilink")(), [set\_mode](set_mode "wikilink")(),
[set\_text\_color](set_text_color "wikilink")()

<Category:functions> <Category:texts> <Category:mod_text>
