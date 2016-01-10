Definition
----------

**INT** filter ( &lt;**INT** fileID&gt; , &lt;**INT** graphID&gt; ,
&lt;**POINTER** filter\_table&gt; )

This function allows the colors of a graphic to be filtered with a
nummerical range, defined as an [array](array "wikilink").

Parameters
----------

  ---------------------------- --------------------------------------------------------------------------------------------------------------------
  **INT** fileID               - The [fileID](fileID "wikilink") of the [file](file "wikilink") that holds the graphics.
  **INT** graphID              - The [graphID](graphID "wikilink") of the [graphic](graphic "wikilink").
  **POINTER** fileter\_table   - Pointer to a table [array](array "wikilink") with values that are applied to the [graphic](graphic "wikilink")).
  ---------------------------- --------------------------------------------------------------------------------------------------------------------

Returns
-------

**INT**

  --- ----------------------------------------------
  0   - Invalid graphic or non 16bit graphic used.
  1   - Success.
  --- ----------------------------------------------

Example
-------



    /* Example converted from bennupack, fenix test section, 2 Medium\fenix test\Fenix Test3\Test_FILTER.prg */

    // import modules
    IMPORT "mod_say";
    IMPORT "mod_debug";
    IMPORT "mod_map";
    IMPORT "mod_effects";
    IMPORT "mod_proc";
    IMPORT "mod_grproc";
    IMPORT "mod_map";
    IMPORT "mod_key";
    IMPORT "mod_video";
    IMPORT "mod_screen";


    GLOBAL
    int fpg;
    int png;
    int filter[]=8,20,3,4,5,6,7,8,9,70;
    //int filter[]=448,20,3,4,5,6,7,8,9,70,255,344,255,1,0,0;
    //int filter[]=5,30,20,40,60,80,100,1,1,2,3;
      

    PROCESS main();
      
    BEGIN


      scale_mode=scale_normal2x; 
      set_mode(320,200,mode_16bits);
      
      fpg=load_fpg("FPG2.FPG");
      png=load_png("PNG-1.PNG");
      
      say("Filter test...");
      say("Press ESC to quit...");
      
      put_screen(fpg,1);
      
      bola(100,100,"Normal",0);
      bola(200,100,"Filtered",1);
      
      REPEAT
         FRAME;
      UNTIL (key(_esc))
      
      let_me_alone();
    END


    PROCESS bola(int x,int y,string txt,int use_filter);



    BEGIN
      say(txt);
      size=200; 
      graph=map_clone(0,png);
      
      IF (use_filter==TRUE) 
         filter(0,graph,&filter); 
      END
      
      LOOP
        FRAME;
      END
    END

<Category:functions> [Category:graphical
effects](Category:graphical_effects "wikilink") <Category:mod_effects>
