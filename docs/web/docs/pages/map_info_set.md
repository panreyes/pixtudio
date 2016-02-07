Definition
----------

**INT** map\_info\_set ( &lt;**INT** fileID&gt; , &lt;**INT**
graphID&gt; , &lt;**INT** info\_type&gt; , &lt;**INT** value&gt; )

Changes the x or y coordinate of the center pixel (controlpoint 0). This
function is also known as [Graphic\_set](Graphic_set "wikilink")().

Parameters
----------

  -------------------- --------------------------------------------------------------------------------------------
  **INT** fileID       - The [file](file "wikilink") that holds the graph.
  **INT** graphID      - The [graph](graph "wikilink") to get information from.
  **INT** info\_type   - What [type of information](Graphical_infotypes "wikilink") you want to change, see note.
  **INT** value        - The new x or y coordinate of the center pixel.
  -------------------- --------------------------------------------------------------------------------------------

Returns
-------

**INT** : Returns the information you want.\
If the specified graph was invalid it returns 0.\
If the specified infotype was not recognized it returns 1.

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


    GLOBAL

       int map_id;
       
       int status;


    PROCESS main();

    BEGIN

       set_mode(320,200,32);

       map_id=load_map("3COCHE.MAP");
       
       // print the original data.
       say("width of the map: "+graphic_info(0,map_id,G_WIDTH));
       say("height of the map: "+graphic_info(0,map_id,G_HEIGHT));
       say("g_x_center of the map: "+graphic_info(0,map_id,G_X_CENTER));
       say("g_y_center of the map: "+graphic_info(0,map_id,G_Y_CENTER));
       
       // change the x and y coordinates of the center pixel and display it.
       status=map_info_set(0,map_id,G_X_CENTER,20);
       status=map_info_set(0,map_id,G_Y_CENTER,10);
       say("center pixel changed:");
       say("g_x_center of the map: "+graphic_info(0,map_id,G_X_CENTER));
       say("g_y_center of the map: "+graphic_info(0,map_id,G_Y_CENTER));
       
       say("status: "+status);
       
       graph=map_id;
       x=100; 
       y=100;
       
       LOOP
          IF (key(_esc))
             BREAK;
          END
          FRAME;
       END
    END

Notes
-----

As infotype, only two options are valid:

  ------------------ ------------------------------------------------
  **G\_X\_CENTER**   - Change the x coordinate of the center pixel.
  **G\_Y\_CENTER**   - Change the y coordinate of the center pixel.
  ------------------ ------------------------------------------------

<Category:functions> <Category:maps> <Category:mod_map>
