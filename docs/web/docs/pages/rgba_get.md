Syntax
------

**DWORD** rgba\_get ( &lt;**INT** pixel\_color &gt; , &lt;**POINTER**
red&gt; , &lt;**POINTER** green&gt; , &lt;**POINTER** blue&gt; ,
&lt;**POINTER** alpha&gt; , \[&lt;**INT** depth&gt;\] )

Description
-----------

Get access to the memory sections of the color components, these can be
accessed with the [Offset](Offset "wikilink") operator.

The previous name [Get\_rgba](Get_rgba "wikilink")() is deprecated.

Parameters
----------

  ---------------------- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  **INT** pixel\_color   - The color value of a pixel .
  **POINTER** red        - Pointer to the level of red in the desired color from 0 to 255.
  **POINTER** green      - Pointer to the level of green in the desired color from 0 to 255.
  **POINTER** blue       - Pointer to the level of blue in the desired color from 0 to 255.
  **POINTER** alpha      - Pointer to the alpha channel in the from 0 to 255.
  **INT** depth          - Depth (optional paramter that may be omitted, only in 16 and 32 bit mode). When this parameter is used, the function returns the correct color code for the indicated depth.
  ---------------------- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Returns
-------

**1** : This function always returns a 1.

Notes
-----

The color value's have to be obtained with the
[Offset](Offset "wikilink") operator, and the pixel color value can be
obtained with [Map\_get\_pixel](Map_get_pixel "wikilink")().

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
    IMPORT "mod_mem";
    IMPORT "mod_text";

    GLOBAL

       int map_id;    // id code of the map to load

       int status;    // status for debugging
       
       // color components
       int my_r;      
       int my_g;
       int my_b; 
       int my_a;
       
    PROCESS main();

    BEGIN

       set_mode(320,200,32);
       
       // load the map
       map_id=load_map("3COCHE.MAP");
       
       // first, we're going to check the r,g,b,a values of 5 pixels, with the optional
       // depth parameter.
       status=get_rgba(map_get_pixel(0,map_id,0,0), &my_r, &my_g, &my_b, &my_a,32);
       
       say("my_r: "+my_r+" my_g: "+my_g+" my_b: "+my_b+" my_a: "+my_a);  
       say("status: "+status);
       
       status=get_rgba(map_get_pixel(0,map_id,4,0), &my_r, &my_g, &my_b, &my_a,32);
       
       say("my_r: "+my_r+" my_g: "+my_g+" my_b: "+my_b+" my_a: "+my_a);  
       say("status: "+status);
       
       status=get_rgba(map_get_pixel(0,map_id,50,1), &my_r, &my_g, &my_b, &my_a,32);
       
       say("my_r: "+my_r+" my_g: "+my_g+" my_b: "+my_b+" my_a: "+my_a);  
       say("status: "+status);
       
       status=get_rgba(map_get_pixel(0,map_id,13,24), &my_r, &my_g, &my_b, &my_a,32);
       
       say("my_r: "+my_r+" my_g: "+my_g+" my_b: "+my_b+" my_a: "+my_a);  
       say("status: "+status);
       
       status=get_rgba(map_get_pixel(0,map_id,84,40), &my_r, &my_g, &my_b, &my_a,32);
       
       say("my_r: "+my_r+" my_g: "+my_g+" my_b: "+my_b+" my_a: "+my_a);  
       say("status: "+status);
      
       // second, we use the simpler way, that is valid for a bit maps
       say("");
       say("8 bit color codes");
       say(map_get_pixel(0,map_id,0,0));
       say(map_get_pixel(0,map_id,4,0));
       say(map_get_pixel(0,map_id,50,1));
       say(map_get_pixel(0,map_id,13,24));
       say(map_get_pixel(0,map_id,84,40));

       
       LOOP
          IF (key(_esc))
             BREAK;
          END
                      
          FRAME;
       END
    END

See also
--------

The articles about the functions, [Rgb](Rgb "wikilink")() and
[Rgba](Rgba "wikilink")() for more information, since this function is
related to some extend.

<Category:functions> <Category:palettes> <Category:mod_map>
