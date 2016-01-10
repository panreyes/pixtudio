Syntax
------

**INT** palette\_roll ( &lt;**INT** start\_color&gt; , &lt;**INT**
end\_color&gt; , &lt;**INT** increment&gt; )

Description
-----------

Cycles the colors in the [palette](palette "wikilink") by rotating them.
This function shifts colors between the range specified by the start
color and the end color, at a given increment. This can be used to
create a very old school waterfall animation effect. This technique is
called [color cycling](http://en.wikipedia.org/wiki/Color_cycling). It
is a very memory efficient way of doing these kinds of animations, since
only one bitmap is used and the effect is achieved by cycling through a
specific range of colors. [*Here's a nice (web based) example of this
technique in
action*](http://www.effectgames.com/demos/canvascycle/?sound=0).

To use this function, you have to create graphics that use a range of
consecutive colors of the original palette, in a perpetual cycle (i.e.,
colors ranging from 0 to 15, painting something with the colors 0, 1, 2,
3, ... , 14, 15, 0, 1, 2, ...).

Also, make sure that these colors are not used by other graphics that
are going to appear on the screen at the same time, if you do not want
to apply these effects on them, or they'll look funny.

***One important thing, this function only works in 8 bit mode.***

The previous name [roll\_palette](roll_palette "wikilink")() is
deprecated.

Parameters
----------

  ---------------------- -----------------------------------------
  **INT** start\_color   - The start color of the range (0-255).
  **INT** end\_colors    - The last color of the range (0-255).
  **INT** increment      - The cycle speed (-1, 0, 1, etc).
  ---------------------- -----------------------------------------

Notes
-----

An increment of 0 is pointless, because that will stop the cycle. The
higher the number, the faster the cycle goes. Negative values will cycle
in the opposite direction.

Returns
-------

**INT** : Status.

  --- ------------
  1   - Success.
  --- ------------

Example
-------

    IMPORT "mod_debug";
    IMPORT "mod_say";
    IMPORT "mod_map";
    IMPORT "mod_key";
    IMPORT "mod_video";
    IMPORT "mod_screen";
    IMPORT "mod_text";


    GLOBAL
       int map;
       int fnt;
       
       byte color_increment=1;
       byte initial_color;
       byte num_colors=10;
      
    PROCESS main();
      
    BEGIN
       
       set_fps(50,0);
       set_mode(640,480,8);     // for palette_roll to work is the 8 bit mode required!
       
       map=load_map("MAP.MAP");
       
       put_screen(0,map);
       
       write(0,10,10,3,"Rolling Palette demo, +/-: change number of colors, 0, 1, 2: change increment, Press ESC to quit...");
       
       REPEAT
          
          // changes the amount of colors      
          IF (key(_plus) AND num_colors<255)
             FRAME;
             num_colors+=1;
          END
          
          IF (key(_minus) AND num_colors>1)
             FRAME;
             num_colors-=1;
          END
          
          
          // change the speed 
          IF (key(_0))
             FRAME;
             color_increment=0;
          END
          
          IF (key(_1))
             FRAME;
             color_increment=1;
          END
          
          IF (key(_2))
             FRAME;
             color_increment=-1;
          END
          
          // roll the palette
          palette_roll(initial_color,num_colors,color_increment);      
          say("initial color: "+initial_color+" num color: "+num_colors+" increment: "+color_increment);
          
          
          FRAME;
       UNTIL(key(_esc))
      
    END

Used in example: [Say](Say "wikilink")(), [Key](Key "wikilink")(),
[Write](Write "wikilink")()

<Category:functions> <Category:palettes> <Category:mod_map>
