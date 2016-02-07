Definition
----------

**INT** Start\_scroll ( &lt;**INT** scrollnumber&gt; , &lt;**INT**
fileID&gt; , &lt;**INT** graphID&gt; , &lt;**INT** backgroundgraphID&gt;
, &lt;**INT** regionnumber&gt; , &lt;**INT** lockindicator&gt; , \[
&lt;**INT** destination fileID &gt;, &lt;**INT** destination graphID
&gt; \] )

This creates a [scroll window](scroll_window "wikilink") in which it
will perform a view against a background [graphic](graphic "wikilink").
That is, by using a graphic bigger than the display window, a part of
this graphic can be shown and shifted in any direction. After this
function, the use of the struct [scroll](scroll "wikilink") makes sense.

The parameters *destination fileID* and *destination graphID* are
optional and may be omitted.

Also called [scroll\_start](scroll_start "wikilink")().

Parameters
----------

  ----------------------------- ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  **INT** scrollnumber          - The ID for the new scroll window, so it can be referenced to later
  **INT** fileID                - The [fileID](fileID "wikilink") of the [file](file "wikilink") containing the scroll graphics
  **INT** graphID               - The [graphID](graphID "wikilink") of the [graphic](graphic "wikilink") of the main graphic to be scrolled
  **INT** backgroundgraphID     - The graphID of the graphic for the background of the scroll window
  **INT** regionnumber          - The [region](region "wikilink") in which to put the scroll window
  **INT** lockindicator         - A [bit flag](bit_flag "wikilink") defining whether each of the two scroll planes is horizontally/vertically cyclical
  **INT** destination flileID   - The [fileID](fileID "wikilink") of the [file](file "wikilink") containing the destination graphics used in the scroll window, i.e. the systemfile. **(optional)**
  **INT** destination graphID   - The [graphID](graphID "wikilink") of the [graphic](graphic "wikilink") of the destination graphic where the scroll window will be drawn on. **(optional)**
  ----------------------------- ---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Notes
-----

The locking indicator can be combinations of the following flags:

  --- ----------------------------------------------------------
  1   - The foreground will be displayed horizontally cyclical
  2   - The foreground will be displayed vertically cyclical
  4   - The background will be displayed horizontally cyclical
  8   - The background will be displayed vertically cyclical
  --- ----------------------------------------------------------

Combine them using the [bitwise OR](BOR "wikilink") operator.

Using Scrolling
---------------

For each [process](process "wikilink") that you want to be part of a
[scroll window](scroll_window "wikilink"), you must set the [local
variable](local_variable "wikilink") [ctype](ctype "wikilink") to value
[C\_SCROLL](C_SCROLL "wikilink"). It should also be noted that the local
variable [c\_number](c_number "wikilink") is used for selecting in which
scroll a process should be displayed. Additionally, you must set the
camera property of the [scroll structure](scroll "wikilink") to the
[processID](processID "wikilink") of the process you wish to be
followed.

Example (scroll drawn on map)
-----------------------------

In this example, a scroll is drawn on a map, so the advanced version
with the parameters *destination fileID* and *destination graphID* are
used.

    // import modules
    IMPORT "mod_say";
    IMPORT "mod_debug";
    IMPORT "mod_proc";
    IMPORT "mod_grproc";
    IMPORT "mod_map";
    IMPORT "mod_text";
    IMPORT "mod_key";
    IMPORT "mod_video";
    IMPORT "mod_screen";
    IMPORT "mod_draw";
    IMPORT "mod_scroll";



    GLOBAL

       int graphics_lib;
     
       int object1_id;
       
       int scroll_window;  
       int scroll_blit_graph;
       
     
    PROCESS int main(); 

    PRIVATE

    BEGIN

        set_mode(640,480,8);
        set_fps(50,0);
        
        // load the fpg file with the graphics
        graphics_lib=load_fpg("graf2.fpg");
      

        // create a map to blit the scroll window on
        scroll_blit_graph=new_map(640,480,8);
        
        // display the "scroll_blit_graph".
        blit_graph();
        
        // (standard version)
        // int start_scroll (int scrollnumber, 
        //                   int file, 
        //                   int graph, 
        //                   int backgroundgraph, 
        //                   int regionnumber, 
        //                   int lockindicator); 

        // (advanced, extended version)
        // int start_scroll (int scrollnumber, 
        //                   int file, 
        //                   int graph, 
        //                   int backgroundgraph, 
        //                   int regionnumber, 
        //                   int lockindicator, 
        //                   int destination file, 
        //                   int destination graph); 
       
       
        // create an extended scroll, drawn on the "scroll_blit_graph".
        scroll_window=start_scroll(0,graphics_lib,1,0,0,3,0,scroll_blit_graph); 
        
          
        say("scroll_window status: "+scroll_window);
            
        // create the two objct processes.
        object1_id=object1(graphics_lib); 
       
        
        
        // write instructions  
        write(0 ,20,30,ALIGN_CENTER_LEFT,"Scroll extended (with destination map) test demo, instructions"); 
        
        write(0 ,20,40,ALIGN_CENTER_LEFT,"F3 and F4: decrease/increase size of destination map"); 
        write(0 ,20,50,ALIGN_CENTER_LEFT,"F5 and F6: decrease/increase angle of destination map"); 
        write(0 ,20,60,ALIGN_CENTER_LEFT,"F7 and F8: decrease/increase x of destination map"); 
        write(0 ,20,70,ALIGN_CENTER_LEFT,"F9 and F10: decrease/increase y of destination map"); 
       
        
        WHILE (NOT key(_esc))
                  
            FRAME;
        END
        
        // stop scroll window.
        stop_scroll(0);

        
        // kill all processes, execpt the "main" process.
        let_me_alone();
    END



    PROCESS int object1 (int file);

    PRIVATE

    BEGIN
        
        graph=3;
        
        ctype=c_scroll;
        cnumber=c_0; // make this process visible in window 0
        
        scroll[0].camera=id;
        
        x=100;  
        y=100;
            
        LOOP
            
            // move main object
            IF (key(_up) AND y >0) 
               y-=5; 
            END
            IF (key(_down) AND y <800) 
               y+=5; 
            END
            IF (key(_left) AND x >0)  
               x-=5; 
            END
            IF (key(_right) AND x <2000) 
               x+=5; 
            END
                   
            FRAME;
        END
    END


    // Process for handling the "destination graph" feature, i.e. the map on wich
    // the mode7 windows are drawn.
    PROCESS int blit_graph();

    PRIVATE

    BEGIN

       x=320;
       y=240;
       
       ctype=c_screen;
       
       file=0;
       graph=scroll_blit_graph; // set the graph to the map created in memory.
       
       LOOP
       
          // the controls for the "fancy stuff".
          IF (key(_f3) AND size >20)
             size-=10;
          END
          
          IF (key(_f4) AND size <1000)
             size+=10;
          END
          
          IF (key(_f5) AND angle >0)
             angle-=100;
          END
          
          IF (key(_f6) AND angle <360000)
             angle+=100;
          END
          
          IF (key(_f7) AND x >0)
             x-=10;
          END
          
          IF (key(_f8) AND x <1000)
             x+=10;
          END
          
          IF (key(_f9) AND y >0)
             y-=10;
          END
          
          IF (key(_f10) AND y <1000)
             y+=10;
          END
          
          
          FRAME;
       END
    END

<Category:functions> <Category:scrolls> <Category:mod_scroll>
