Syntax
------

**INT** pal\_map\_assign ( &lt;**INT** fileID&gt; , &lt;**INT**
graphID&gt;, &lt;**INT** paletteID&gt; )

Description
-----------

Changes the color palette of an 8 bit (256 color) graphic, with the
palette that is loaded with [Pal\_load](Pal_load "wikilink")(). This
[palette](palette "wikilink") can also be loaded from
[MAP](MAP "wikilink")'s, [FPG](FPG "wikilink")'s,
[FNT](FNT "wikilink")'s and other image formats, provided that they are
8 bit images. Unlike [Pal\_set](Pal_set "wikilink")(), the change is
immediately visible.

Parameters
----------

  ------------------- ----------------------------------------------------------------------------------------------------------------
  **INT** fileID      - The fileID of the graphic(s), i.e. 0 for the systemfile, or the id code of an [FPG](FPG "wikilink") archive.
  **INT** graphID     - The graphic (or mapcode) to modify.
  **INT** paletteID   - The handle of the color palette loaded with [Pal\_load](Pal_load "wikilink")().
  ------------------- ----------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : Error.

  --- ----------------------------------------------------------------------------------------------------
  0   - Error: could not open file; corrupt or truncated file; file doesn't contain palette information.
  1   - No error: [palette](palette "wikilink") was loaded with success.
  --- ----------------------------------------------------------------------------------------------------

Example
-------

    /* Original example from bennupack: 2 Medium\fenix test\palettes\rbear8_1.prg (from bomberlink) */

    IMPORT "mod_debug";
    IMPORT "mod_say";
    IMPORT "mod_map";
    IMPORT "mod_key";
    IMPORT "mod_video";
    IMPORT "mod_text";

    GLOBAL
       int pal_orange;  // palette 1
       int pal_green;   // palette 2
       
       int map_count;

       int fpg_id;

    PROCESS main();

    BEGIN

        set_fps(10,0);
        set_mode(320,200,16);

        // load the fpg archive
        fpg_id=fpg_load("rbear8.fpg");
        
        // load the two palettes
        pal_orange=pal_load("rbear8-orange.pal");
        pal_green=pal_load("rbear8-green.pal");

        write_int(0,10,10,0,&fps);
        write(0,10,20,0,"F1/F2 - change palette");

        x=160;
        y=120;

        WHILE (NOT key(_ESC))
        
            FROM graph=1 TO 3;
            
              FRAME;
               
               IF (key(_F1))
                  FROM map_count=1 TO 102;
                     say("changing colors: "+map_count);
                     pal_map_assign(fpg_id,map_count,pal_green);  // apply palette 1
                  END
               END
               
               IF (key(_F2))
                  FROM map_count=1 TO 102;
                     say("changing colors: "+map_count);
                     pal_map_assign(fpg_id,map_count,pal_orange); // apply palette 2
                  END
               END
            
               IF (key(_ESC)) 
                  BREAK; 
               END
            END
        END

    END

Used in example: [Pal\_load](Pal_load "wikilink")(),
[Say](Say "wikilink")(), [Set\_fps](Set_fps "wikilink")(),
[Set\_mode](Set_mode "wikilink")(), [Write](Write "wikilink")(),
[Write\_int](Write_int "wikilink")()

<Category:functions> <Category:palettes> <Category:mod_map>
