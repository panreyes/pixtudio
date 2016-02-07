Definition
----------

**POINTER** map\_buffer ( &lt;**INT** fileID&gt; , &lt;**INT**
graphID&gt; )

Get access to the memory buffer of the map. This function is usefull in
combination with [Memset](Memset "wikilink")(). This way you can
manipulate the actual bytes of the map.

Parameters
----------

  ----------------- ----------------------------------------------------------
  **INT** fileID    - The [file](file "wikilink") that holds the graph.
  **INT** graphID   - The [graph](graph "wikilink") to get information from.
  ----------------- ----------------------------------------------------------

Returns
-------

**POINTER** : Pointer to the memory contents of the map.

Example
-------

In this example I'm going to demonstrate how you can manipulate the
pixel buffer of the map. I load the same map twice (each with their own
ID), and one of them is butchered by messing with it's pixel buffer. By
assiging that map to a [Pointer](Pointer "wikilink") with map\_buffer(),
we can use [Memset](Memset "wikilink")() to change the bytes in the
memory area that the map occupies.

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
       int map_id2;

       pointer p_map; // pointer to the map_buffer

    PROCESS main();

    BEGIN

       set_mode(320,200,32);
       
       
       write(0,10,10,3,"map_buffer example, press 'ESC' to quit.");
       
       write(0,10,30,3,"press '1' to show the modified map.");
       write(0,10,40,3,"press '2' to show the orginial map.");

       // load two maps, this map can be found in bennupack: 2 Medium\IA\PATH.FIND\3COCHE.MAP
       // it is a the "car" graphic of the pathfind tutorial for TYCO. Both maps are the same,
       // but one of them we're going to modify with map_buffer().
       map_id=load_map("3COCHE.MAP");
       map_id2=load_map("3COCHE.MAP"); // same map, but this one is left intact
       
       
       graph=map_id2; // original map
       x=100; 
       y=100;
       
       
       // get the memory adress of the "raw" pixel buffer of the map.
       p_map=map_buffer(0,map_id);
         

       // now that we've got acccess to the pixel buffer, we can change individual bytes.
       // with memset we can modify memory contents of individual bytes. 
       // in this case, we change the first 1000 bytes into the color #100.
       memset(p_map,100,1000); 
       
       // no, we're offsetting 200 adresses from the start of the memory block, and change another
       // 1000 bytes into a different color.
       memset(p_map+200,150,1000); 

       
       LOOP
          IF (key(_esc))
             BREAK;
          END
          
          IF (key(_1))     // show the "butchered" map
             FRAME(100);
             graph=map_id;
             say("showing map modified with map_buffer()");
          END
          
          IF (key(_2))    // show the original map
             FRAME(100);
             graph=map_id2;
             say("showing original map");
          END
                
          FRAME;
       END
    END

Used in example: [Load\_map](Load_map "wikilink")(),
[Memset](Memset "wikilink")(), [Write](Write "wikilink")(),
[Say](Say "wikilink")(), [Pointer](Pointer "wikilink")()

Notes
-----

In the [Memset](Memset "wikilink")() function, indiviual bytes are used.
The amount of bytes to store the color of one pixel depends on it's
colordepth. In 8 bit mode, you need only one byte per pixel, in rgb mode
3 bytes and in rgba mode 4 bytes per pixel. So that is something you
should be aware of. This is a similair caveat as with the
[Alloc](Alloc "wikilink")() function, because you're dealing with raw
memory contents here.

<Category:functions> <Category:maps> <Category:mod_map>
