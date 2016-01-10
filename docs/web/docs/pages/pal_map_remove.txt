Syntax
------

**INT** pal\_map\_remove ( &lt;**INT** fileID&gt; , &lt;**INT**
graphID&gt; )

Description
-----------

Removes the color palette that assigned with
[Pal\_map\_assign](Pal_map_assign "wikilink")(). It is basically an undo
function for color palette changes.

Parameters
----------

  ----------------- ----------------------------------------------------------------------------------------------------------------
  **INT** fileID    - The fileID of the graphic(s), i.e. 0 for the systemfile, or the id code of an [FPG](FPG "wikilink") archive.
  **INT** graphID   - The graphic (or mapcode).
  ----------------- ----------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : Status/Error.

  --- ----------------------------------------------------------------------------------------------------
  0   - Error: could not open file; corrupt or truncated file; file doesn't contain palette information.
  1   - No error: [palette](palette "wikilink") was reverted with success.
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
       
       int status;

    PROCESS main();

    BEGIN

        set_fps(10,0);
        set_mode(320,200,16);  // we use a 16 bit colormode

        // load the fpg archive
        fpg_id=fpg_load("rbear8.fpg");
        
        // load the two palettes
        pal_orange=pal_load("rbear8-orange.pal");
        pal_green=pal_load("rbear8-green.pal");

        write_int(0,10,10,0,&fps);
        write(0,10,20,0,"F1/F2 - change palette");
        write(0,10,30,0,"F3 - to undo palette changes");

        x=160;
        y=120;

        WHILE (NOT key(_ESC))
        
            FROM graph=1 TO 3; // cycle through 3 graphics
            
              FRAME;
               
               IF (key(_F1))
                  FROM map_count=1 TO 102; // there are 102 frames in the animation.
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
               
               IF (key(_F3))
                  FROM map_count=1 TO 102;
                     say("changing colors: "+map_count);
                     status=pal_map_remove(fpg_id,map_count); 
                     say("status: "+status);
                  END
               END
            
               IF (key(_ESC)) 
                  BREAK; 
               END
            END
        END

    END

Used in example: [Say](Say "wikilink")(),
[Pal\_load](Pal_load "wikilink")(),
[Pal\_map\_assign](Pal_map_assign "wikilink")(),
[Key](Key "wikilink")(), [Write](Write "wikilink")(),
[Write\_int](Write_int "wikilink")()

<Category:functions> <Category:palettes> <Category:mod_map>
