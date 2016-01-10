Definition
----------

**INT** near\_angle ( &lt;**INT** angle&gt; , &lt;**INT** final
angle&gt; , &lt;**INT** increment&gt; )

Returns an [angle](angle "wikilink") closer to another angle, with the
indicated increment. It is used for aiming the original angle and it
gradually changes into the final angle. The increment controls the rate
in wich the final angle is added or subtracted from the orginal angle.
The returned angle will be ranging from 0 to 360000 (0-360º).

Parameters
----------

  --------------------- ------------------------------------------------------------
  **INT** angle         - The original angle.
  **INT** final angle   - The new angle.
  **INT** increment     - The addition or subtraction rate between the two angles.
  --------------------- ------------------------------------------------------------

Returns
-------

**INT** : An angle nearer the final angle.

Notes
-----

The [angle](angle "wikilink") value returned by this function is in
thousandths of degrees, as most angles within [Bennu](Bennu "wikilink")
are.

Example
-------

    /* Modified example converted from bennupack, fenix test section, 2 Medium\fenix test\Fenix Test3\Test_NEAR_ANGLE.prg */

    // import modules
    IMPORT "mod_say";
    IMPORT "mod_debug";
    //IMPORT "mod_math";
    IMPORT "mod_mathi";
    IMPORT "mod_map";
    IMPORT "mod_key";
    IMPORT "mod_video";
    IMPORT "mod_screen";
    IMPORT "mod_mouse";
    IMPORT "mod_proc";
    IMPORT "mod_grproc";

    GLOBAL

       int fpg;
       int ang;
       //int increment=5000;
       int increment=10000;
       //int increment=25000;
       //int increment=50000;
        
      
    PROCESS main();
      
    BEGIN
      
      full_screen=false;
      fpg=load_fpg("Fpg.fpg");
      
      say("Test near_angle...");
      say("Press ESC to quit, and use mouse to move triangle.");
       
      put_screen(fpg,2);
      
      // set the mouse cursor 
      mouse.graph=200;
      mouse.x=0;
      mouse.y=0;
      
      graph=101;
      
      REPEAT
      
        // Returns the angle between two certain points. The returned angle will be ranging from 0 to 360000 (0-360º). 
        ang=fget_angle(x,y,mouse.x,mouse.y);
        
        // int near_angle (int <angle>, int <final angle>, int <increment>)
        angle=near_angle(angle,ang,increment);
             
        say("angle: "+angle);
        say("ang: "+ang);
        say("increment: "+increment);   
        
        advance(5);
        FRAME;
      UNTIL(key(_esc))
      
    END

Used in example: [say](say "wikilink")(),
[fget\_angle](fget_angle "wikilink")(), [key](key "wikilink")(),
[Advance](Advance "wikilink")(), [mouse](mouse "wikilink"),
[graph](graph "wikilink"), [x](x "wikilink"), [y](y "wikilink"),
[angle](angle "wikilink")

<Category:functions> <Category:math> <Category:mod_math>
