Definition
----------

**FLOAT** sin ( &lt;**FLOAT** angle&gt; )

Returns the sine of the specified [angle](angle "wikilink").

This [function](function "wikilink") performs a sine calculation on a
certain angle and returns a value between -1 and 1.

Parameters
----------

  ----------------- --------------------------------------------------------------------------
  **FLOAT** angle   - [Angle](Angle "wikilink"), in thousandths of degrees. i.e. 75000 = 75º
  ----------------- --------------------------------------------------------------------------

Returns
-------

**FLOAT** : The sine result of the specified [angle](angle "wikilink").

Notes
-----

The [angle](angle "wikilink") value used in this function should be in
thousandths of degrees, as most angles within [Bennu](Bennu "wikilink")
are.

To read about all aspects of trigonometry, you can click on Wikipedia's
[Trigonometric
function](http://en.wikipedia.org/wiki/Trigonometric_function) page.

Example
-------

    Const
        screen_width  = 320;
        screen_height = 200;
        screen_border = 15;
    End

    Global
        float value;
    End

    Process Main()
    Begin

        // Modes
        set_title("Sine Graph");
        set_mode(screen_width,screen_height);

        // X axis
        for(x=1;x<=8;x++)
            write( 0,
                   screen_border+x*(screen_width-screen_border)/8+3,
                   screen_height-1,
                   8,
                   itoa(x*360/8 )+"^" );
        end
        draw_line(1,screen_height-screen_border,screen_width,screen_height-screen_border);

        // Y axis
        write(0,screen_border-1,20,5,"1");
        write(0,screen_border-1,screen_height/2,5,"0");
        write(0,screen_border-1,screen_height-20,5,"-1");
        draw_line(screen_border,1,screen_border,screen_height-1);

        // Draw tangent
        for(angle=0;angle<360;angle++)
            value=sin(angle*1000)*(screen_height/2-20);
            put_pixel( screen_border+angle*(screen_width-screen_border)/360,
                       screen_height/2-value,
                       rgb(255,255,255) );
            // screen_height/2-value because the screen's origin (0,0) is topleft instead of downleft.
        end

        Repeat
            frame;
        Until(key(_ESC))

    End

Used in example: [set\_title](set_title "wikilink")(),
[set\_mode](set_mode "wikilink")(), [write](write "wikilink")(),
[draw\_line](draw_line "wikilink")(), [sin](sin "wikilink")(),
[put\_pixel](put_pixel "wikilink")(), [key](key "wikilink")()

This will result in something like:\

<Category:functions> <Category:math> <Category:mod_math>
