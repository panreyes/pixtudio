Syntax
------

**INT** color\_find ( &lt;**BYTE** red&gt; , &lt;**BYTE** green&gt; ,
&lt;**BYTE** blue&gt; )

Description
-----------

Match an RGB value to a particular palette index. This is usefull in 8
bit mode.

The previous name [find\_color](find_color "wikilink")() is deprecated.

Parameters
----------

  ---------------- ------------------------------------------------------
  **BYTE** red     - Level of red in the desired color from 0 to 255.
  **BYTE** green   - Level of green in the desired color from 0 to 255.
  **BYTE** blue    - Level of blue in the desired color from 0 to 255.
  ---------------- ------------------------------------------------------

Returns
-------

**INT** : Returns the palette inxed of the color that corresponds with
the rgb combination.

Example
-------

    IMPORT "mod_say";
    IMPORT "mod_debug";
    IMPORT "mod_key";
    IMPORT "mod_map";
    IMPORT "mod_video";
    IMPORT "mod_wm";
    IMPORT "mod_draw";
    IMPORT "mod_screen";
    IMPORT "mod_text";

    GLOBAL

       int map_id;    // id code of the map to load

       int status;    // status for debugging

       
    PROCESS main();

    BEGIN

       set_mode(320,200,32);
       
       // load the map
       map_id=load_map("3COCHE.MAP");
       
       status=color_find(0,0,0);
       say("color: "+status);
       status=color_find(0,252,0);
       say("color: "+status);
       status=color_find(0,67,0);
       say("color: "+status);
       status=color_find(0,243,0);
       say("color: "+status);
       status=color_find(0,10,0);
       say("color: "+status);
       status=color_find(255,252,0);
       say("color: "+status);
       status=color_find(100,252,100);
       say("color: "+status);
      
      
    END

<Category:functions> <Category:palettes> <Category:mod_map>
