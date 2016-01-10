Syntax
------

**INT** pal\_map\_getid ( &lt;**INT** fileID&gt; , &lt;**INT**
graphID&gt; )

Description
-----------

This function returns the identification code of the palette of a
specific graphic.

Parameters
----------

  ----------------- ----------------------------
  **INT** fileID    - The handle of the file.
  **INT** graphID   - The handle of the graph.
  ----------------- ----------------------------

Returns
-------

**INT** : Error/status.

  ---- ----------------------------------------------------------------------------------------------------
  0    - Error: could not open file; corrupt or truncated file; file doesn't contain palette information.
  id   - The identifier of the [palette](palette "wikilink").
  ---- ----------------------------------------------------------------------------------------------------

Example
-------

    /* original bennupack example FROM: \2 Medium\fenix test\palettes\rbear8-5.prg (from bomberlink) */

    /* this program demonstrates the use of the functions: pal_load(), pal_map_get_id()              */
    /* pal_map_assign(), pal_set() and pal_refresh().                                                */

    /* In this example pal_get() is not used but the table is filled with data by forehand.          */


    IMPORT "mod_debug";
    IMPORT "mod_say";
    IMPORT "mod_map";
    IMPORT "mod_key";
    IMPORT "mod_video";
    IMPORT "mod_text";

    GLOBAL

       int pal_normal; // identifier of the palette
       
       int fpg_id;     // identifier of the fpg file
       
       // the arrays with data (pre-filled)   
       byte orange_palette_data[21] =
                                    80,0,0,
                                   110,0,0,
                                   140,0,0,
                                   170,0,0,
                                   190,0,0,
                                   220,0,0,
                                   250,0,0;
       byte green_palette_data[21] =
                                   0, 80,0,
                                   0,110,0,
                                   0,140,0,
                                   0,170,0,
                                   0,190,0,
                                   0,220,0,
                                   0,250,0;
                                   
       int count;

    PROCESS main();   
       
    BEGIN

        set_fps(10,0);
        set_mode(320,200,16);



        // load the fpg
        fpg_id=fpg_load("rbear8.fpg");

        write_int(0,10,10,0,&fps);
        write(0,10,20,0,"F1/F2 - change palette");

        x=160;
        y=120;

        pal_normal=pal_map_getid(fpg_id,1); // file,graph   
        say("pal_normal: "+pal_normal);

        WHILE (NOT key(_ESC))
        
            FROM graph=1 TO 13;
            
                FRAME;
                
                IF (key(_F1))
                    pal_set(pal_normal,7,7,&green_palette_data);    // colors 7 - 13
                    pal_refresh(pal_normal);
                END
                
                IF (key(_F2))
                    pal_set(pal_normal,7,7,&orange_palette_data);  // colors 7 - 13
                    pal_refresh(pal_normal);
                END
                
                IF (key(_ESC)) 
                   BREAK; 
                END
            END
        END

    END

Used in example: , [Pal\_set](Pal_set "wikilink")(),
[Pal\_map\_assign](Pal_map_assign "wikilink")(),
[Pal\_refresh](Pal_refresh "wikilink")(), [Say](Say "wikilink")(),
[Set\_fps](Set_fps "wikilink")(), [Set\_mode](Set_mode "wikilink")(),
[Write](Write "wikilink")(), [Write\_int](Write_int "wikilink")()

See also
--------

[Pal\_set](Pal_set "wikilink")(), [Pal\_get](Pal_get "wikilink")()

<Category:functions> <Category:palettes> <Category:mod_map>
