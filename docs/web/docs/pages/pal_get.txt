Syntax
------

**INT** pal\_get ( \[&lt;**INT** paletteID&gt;\] , &lt;**INT**
first\_color&gt; , &lt;**INT** num\_colors&gt; , &lt;**POINTER**
palette\_data&gt;)

Description
-----------

This function is used in conjuction with
[Pal\_set](Pal_set "wikilink")() to load palette data that was loaded
with [Pal\_load](Pal_load "wikilink")() into an array, for later use
with [Pal\_set](Pal_set "wikilink")(). This
[palette](palette "wikilink") can also be loaded from
[MAP](MAP "wikilink")'s, [FPG](FPG "wikilink")'s,
[FNT](FNT "wikilink")'s and other image formats, provided that they are
8 bit images.

Also called [colors\_get](colors_get "wikilink")(). The previous name
[get\_colors](get_colors "wikilink")() is deprecated.

Parameters
----------

  --------------------------- --------------------------------------------------------------------------------------------------------------
  **INT** paletteID           - The handle of the color palette loaded with [Pal\_load](Pal_load "wikilink")(). This paramter is optional.
  **INT** first\_color        - The first color number of the palette. This doesn't necessarily have be the first color.
  **INT** num\_colors         - The number of colors you want to replace, wich counts from the first\_color to the num\_colors. See notes.
  **POINTER** palette\_data   - Pointer ([Offset](Offset "wikilink")) to an array where the color values will be stored.
  --------------------------- --------------------------------------------------------------------------------------------------------------

Note
----

The maximum number of colors cannot be bigger the 255. The num\_colors
starts counting from first\_color, so if the first\_color is 7, and
num\_colors is 7, the color value's 7-13 are changed. So logically, the
value num\_colors can only be 255 when first\_color is 0. This range
gives you all the colors. To be safe, the formula for the number of
colors to modified is: num\_colors-first\_color.

I.e. num\_colors: 55 - first\_color: 4 = 51 colors are changed, the
range from color index 4 up to color index 55.

Returns
-------

**INT** : Error.

  --- ----------------------------------------------------------------------------------------------------
  0   - Error: could not open file; corrupt or truncated file; file doesn't contain palette information.
  1   - No error: [palette](palette "wikilink") was set with success.
  --- ----------------------------------------------------------------------------------------------------

Example
-------


    /* original bennupack example FROM: \2 Medium\fenix test\palettes\rbear8-2.prg (from bomberlink) */

    /* this program demonstrates the use of the functions: pal_load(), pal_clone(), pal_get(),       */
    /* pal_map_assign(), pal_set() and pal_refresh().                                                */


    IMPORT "mod_debug";
    IMPORT "mod_say";
    IMPORT "mod_map";
    IMPORT "mod_key";
    IMPORT "mod_video";
    IMPORT "mod_text";


    GLOBAL
       
       // palette identifiers
       int pal_orange;
       int pal_green;
       int pal_normal;
       
       int status1;
       int status2;
       
       // identifier of the fpg archive
       int fpg_id;
       
       // arrays for the data of the two color palettes.
       byte pal_orange_data[255]; 
       byte pal_green_data[255];  
       
       int map_count;

    PROCESS main();

    BEGIN

        set_fps(10,0);
        set_mode(320,200,16);  // we use a 16 bit color mode

        // load two color palettes and duplicate one
        pal_green=pal_load("rbear8-green.pal");
        pal_orange=pal_load("rbear8-orange.pal");
        
        // pal_clone (int pal_id);
        pal_normal=pal_clone(pal_orange); // duplicate palette, i.e. make a copy of it.

        // load the fpg file
        fpg_id=fpg_load("rbear8.fpg");

        write_int(0,10,10,0,&fps);
        write(0,10,20,0,"F1/F2 - change palette");

        x = 160;
        y = 120;

        // pal_get (int pal_id, int start_color, int num_colors, pointer pal_data);
        pal_get(pal_green,7,7,&pal_green_data);    // get colors 7 - 13 and store them in the array
        pal_get(pal_orange,7,7,&pal_orange_data);        

        FROM map_count=1 TO 102; // there are 102 frames in the animation
            
            // pal_map_assign (int fileid, int graph, int pal_id);
            pal_map_assign(fpg_id,map_count,pal_normal); // assign the "normal (original source)" color 
                                                         // palette that we duplicated earlier.
        END

        WHILE (NOT key(_ESC))
        
            FROM graph=1 TO 13;
            
                FRAME;
                
                IF (key(_F1))
                    say("switched to green palette");
                    
                    // pal_set (int pal_id, int start_color, int num_colors, pointer pal_data);
                    status1=pal_set(pal_normal,7,7,&pal_green_data); // change colors 7 - 13 in the "normal" 
                                                                     // palette, by using the values from the
                                                                     // "green" color palette.

                    say("pal_set_status: "+status1);                                                                 
                    
                    // pal_refresh (int pal_id);
                    status2=pal_refresh(pal_normal); // apply the modified color palette to the graphics.
                                                     // this function is required to make the change visible.  

                    say("pal_refresh_status: "+status2);                                                   

                    // conclusion: the difference between pal_map_assign() and pal_set() is that pal_map_assign()
                    // works immediately, and that pal_set() requires the palette to be refreshed to make the 
                    // change visible.                
                END
                
                IF (key(_F2))
                    say("switched to orange palette");
                    pal_set(pal_normal,7,7,&pal_orange_data);  // colors 7 - 13
                    pal_refresh(pal_normal);
                END
                
                IF (key(_ESC)) 
                    BREAK; 
                END
            END
        END

    END

Used in example: [Pal\_load](Pal_load "wikilink")(),
[pal\_clone](pal_clone "wikilink")(), [Pal\_set](Pal_set "wikilink")(),
[Pal\_map\_assign](Pal_map_assign "wikilink")(),
[Pal\_refresh](Pal_refresh "wikilink")(), [Say](Say "wikilink")(),
[Set\_fps](Set_fps "wikilink")(), [Set\_mode](Set_mode "wikilink")(),
[Write](Write "wikilink")(), [Write\_int](Write_int "wikilink")()

<Category:functions> <Category:palettes> <Category:mod_map>
