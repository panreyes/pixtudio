Syntax
------

**INT** pal\_clone ( &lt;**INT** paletteID&gt; )

Description
-----------

This function is creates a copy of palette loaded with
[Pal\_load](Pal_load "wikilink")(). It can be used for the functions
[Pal\_get](Pal_get "wikilink")(), [Pal\_set](Pal_set "wikilink")() and
[Pal\_map\_assign](Pal_map_assign "wikilink")().

Parameters
----------

  ------------------- -----------------------------------------------------------------------------------
  **INT** paletteID   - The handle of the color palette loaded with [Pal\_load](Pal_load "wikilink")().
  ------------------- -----------------------------------------------------------------------------------

Returns
-------

**INT** : Error.

  --- ----------------------------------------------------------------------------------------------------
  0   - Error: could not open file; corrupt or truncated file; file doesn't contain palette information.
  1   - The identifier of the [palette](palette "wikilink").
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
[pal\_get](pal_get "wikilink")(), [Pal\_set](Pal_set "wikilink")(),
[Pal\_map\_assign](Pal_map_assign "wikilink")(),
[Pal\_refresh](Pal_refresh "wikilink")(), [Say](Say "wikilink")(),
[Set\_fps](Set_fps "wikilink")(), [Set\_mode](Set_mode "wikilink")(),
[Write](Write "wikilink")(), [Write\_int](Write_int "wikilink")()

<Category:functions> <Category:palettes> <Category:mod_map>
