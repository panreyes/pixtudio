Definition
----------

**INT** drawing\_stipple ( &lt;**INT** stipples&gt; )

Tells [Bennu](Bennu "wikilink") which pixels to draw of the coming
[drawings](drawing "wikilink").

This is done by passing a 32bit value, each bit representing a pixel.
Bit 0 represents the first pixels drawn, bit 1 represents the second,
etc. When a 33rd pixel is to be drawn or not, bit 0 is checked and the
cycle starts over. This means a value of `0xFFFFFFFF` (=`2^32-1`) means
normal operation, meaning all the pixels will be drawn.

Note that this works only for non-filled drawings. For
[draw\_curve](draw_curve "wikilink")(), the pattern is not always
visible for the higher smoothness levels.

Parameters
----------

  -------------------------------------------------------------
  **INT** stipples - Which pixels to draw, repetitive 32bits.
  -------------------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Example
-------

    Program example;         
    Private
    //    int draw_id;
    Begin

        // Draw in background
        drawing_map(0,background);

        // Set stipplemode to display every other pixel.
        // binary code 0101 0101 0101 0101 0101 0101 0101 0101
        // hex code 55555555h
        drawing_stipple(55555555h);

        // Draw two lines
        draw_line(10,10,190,10);
        draw_line(11,12,190,12);

        // Draw this funky pattern
        // binary code 0011 1100 0111 1100 1010 0001 1101 0011
        // hex code 3C7CA1D3h
        drawing_stipple(3C7CA1D3h);

        // Draw two lines
        draw_line(10,20,190,20);
        draw_line(11,22,190,22);

        // Draw a circle
        draw_circle(100,100,50);

        // Draw a rectangle
        draw_rect(50,50,150,150);

        // Draw some lines
        draw_line( 50, 50,100,150);
        draw_line(100,150,150, 50);
        draw_line( 50,150,100, 50);
        draw_line(100, 50,150,150);

        // Draw two curves: one with high smoothness (bit pattern not visible) and one with low smoothness
        draw_curve( 200,200,
                    100,200,
                    100,150,
                    300,100,15);
        draw_curve( 200,200,
                    100,200,
                    100,150,
                    300,100,1);

        // Draw a filled circle
        draw_fcircle(20,180,15);

        // Draw a filled rectangle
        draw_box(50,180,80,195);

        // Wait for key ESC
        Repeat
            frame;
        Until(key(_ESC))

    End

Used in example: [drawing\_map](drawing_map "wikilink")(),
[draw\_line](draw_line "wikilink")(),
[draw\_circle](draw_circle "wikilink")(),
[draw\_rect](draw_rect "wikilink")(),
[draw\_curve](draw_curve "wikilink")(),
[draw\_fcircle](draw_fcircle "wikilink")(),
[draw\_box](draw_box "wikilink")(), [key](key "wikilink")()

This will result in something like:\

<Category:functions> <Category:drawing> <Category:mod_draw>
