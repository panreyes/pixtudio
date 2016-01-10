<category:variables> <category:predefined> [category:global
variables](category:global_variables "wikilink") <category:libvideo>

[**Up to Global Variables**](Global_variables "wikilink")

------------------------------------------------------------------------

**INT** scale\_resolution\_orientation =
[Scale\_resolution\_orientation\_modes](Scale_resolution_orientation_modes "wikilink").

Description
-----------

**Scale\_resolution\_orientation** is a global variable used to rotate a
screen resized by [scale\_resolution](scale_resolution "wikilink")
without changing the real orientation.

Example
-------

    Import "mod_video";
    Import "mod_text";
    Import "mod_key";
    Import "mod_map";
    Import "mod_proc";
    Import "mod_screen";

    Process Main()
    begin
      set_mode(800,600,32);
      write(0,20,20,0,"SCALE_RESOLUTION:");
      write_var(0,160,20,0,scale_resolution);
      write(0,20,30,0,"( Press R) ");
      write(0,20,50,0,"SCALE_RESOLUTION_ORIENTATION:");
      write_var(0,255,50,0,scale_resolution_orientation);
      write(0,20,60,0,"( Press 0, 1, 2 or  ) ");
      write(0,20,90,0,"SCALE_RESOLUTION_ASPECTRATIO:");
      write_var(0,255,90,0,scale_resolution_aspectratio);
      write(0,20,100,0,"( Press A ) ");
      Screen_put(0,png_load("mz800x600.png"));
      repeat
        //Activates/deactivates scale_resolution. 
        if(key(_r))
          while(key(_r)) frame; end   //Wait until the key is released
          if (scale_resolution==0);    //If scale_resolution is not active...
            scale_resolution=08000480; //...then resize the screen 
          else                         //If scale_resolution is already working...
            scale_resolution=NULL;     //...then stop it.
          end
        end 
        
        //This rotates the screen. Only works when SCALE_RESOLUTION is being used. 
        if(key(_0)) scale_resolution_orientation=SRO_NORMAL;end
        if(key(_1)) scale_resolution_orientation=SRO_LEFT;end
        if(key(_2)) scale_resolution_orientation=SRO_DOWN;end
        if(key(_3)) scale_resolution_orientation=SRO_RIGHT;end

        //This activates/deactivates the ASPECT RATIO. Only works when SCALE_RESOLUTION is being used. 
        if(key(_a))
          while(key(_a)) frame; end
          if (scale_resolution_aspectratio==0);
            scale_resolution_aspectratio=SRA_PRESERVE;
          else
            scale_resolution_aspectratio=SRA_STRETCH;
          end
        end 

        set_mode(800,600,32);
        frame;
      until(key(_esc))
      let_me_alone();
    end

Used in example: [write](write "wikilink")(),
[write\_var](write_var "wikilink")(),
[Screen\_put](Screen_put "wikilink")()

File used in example:
[Mz800x600.png](http://wiki.bennugd.org/images/a/a1/Mz800x600.png) by
MZ.

See also
--------

[scale\_resolution](scale_resolution "wikilink"),
[scale\_resolution\_aspectratio](scale_resolution_aspectratio "wikilink")
