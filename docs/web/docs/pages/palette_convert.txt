Syntax
------

**INT** palette\_convert ( &lt;**INT** fileID&gt; , &lt;**INT**
graphID&gt; , &lt;**POINTER** palette\_data&gt; )

Description
-----------

This function changes the colormap of an image, but does not change the
color index values it self. That is, that the individual pixels will
keep their color indexes, but the r,g,b values in the palette are
modified. This function requires an [Array](Array "wikilink") of maximum
255 bytes (or integers), to store the palette values. The array is
accessed with the [Offset](Offset "wikilink") operator.

The previous name [Convert\_palette](Convert_palette "wikilink")() is
deprecated.

Parameters
----------

  --------------------------- -------------------------------------------------------------------------------------------------------------------------------------
  **INT** fileID              - The handle of the file containing the graphics.
  **INT** graphID             - The handle of the graphic.
  **POINTER** palette\_data   - Pointer to the [Array](Array "wikilink") with the new palette data, to be accessed with the [Offset](Offset "wikilink") operator.
  --------------------------- -------------------------------------------------------------------------------------------------------------------------------------

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

      int map_id;
      int clonemap_id;
      
      int palette_table[255];
      int color;
      
      int status;
      
      
    PROCESS main();  

    BEGIN

     
      set_mode(320,240,16);
      
      map_id=load_map("MAP.MAP");
      
      clonemap_id=map_clone(0,map_id); // create a copy of the map
      
      write(0,80,30,4,"Original image:");
      write(0,240,30,4,"Converted image (clone):");
      write(0,160,140,4,"Spacebar: Change the palette of the clone...");
      write(0,160,190,4,"Press ESC to quit...");
      
      // palette color 0 (the transparant color) will be not changed, that's why the 
      // count starts at 1. 
      // values that go beyond 255 will be cut off by the MOD (%). So, 256, becomes 0, 
      // 257 becomes 2 etc. The fist 16 colors will stay untouched.
      FROM color=1 TO 255; 
         palette_table[color]=(color+16) MOD 255; 
         say("palette_table["+color+"]");
      END
      
      xput(0,map_id,80,70,0,25,0,0);
      
      x=240; 
      y=70; 
      graph=clonemap_id; 
      size=25;
      
      REPEAT
      
         IF (key(_space)) 
            // let's do the conversion
            status=palette_convert(0,clonemap_id,&palette_table); 
            say("status: "+status);
         END
         
         FRAME;
      UNTIL(key(_esc))
       
    END

Used in example: [Say](Say "wikilink")(), [Key](Key "wikilink")(),
[Write](Write "wikilink")(), [Map\_clone](Map_clone "wikilink")(),
[Xput](Xput "wikilink")()

<Category:functions> <Category:palettes> <Category:mod_map>
