<category:variables> <category:predefined> [category:global
variables](category:global_variables "wikilink") <category:libvideo>

[**Up to Global Variables**](Global_variables "wikilink")

------------------------------------------------------------------------

**INT** scale\_resolution = WWWWHHHH

Where WWWW is the Width and HHHH the Height.
[Resolution\_modes](Resolution_modes "wikilink") can be used.

Description
-----------

**Scale\_resolution** is a [global variable](global_variable "wikilink")
used to resize the screen without changing the real resolution. That
means the game still uses the resolution indicated by
[set\_mode](set_mode "wikilink")() but it's displayed on the screen at
the one assigned to scale\_resolution. Unlike
[scale\_mode](scale_mode "wikilink") can work with 32bits but doesn't
use any filter.

Scale\_resolution takes effect after [set\_mode](set_mode "wikilink")()
only and cannot be used togheter with
[scale\_mode](scale_mode "wikilink"). Assigning NULL will cancel the use
of scale\_resolution.

Example
-------

    //This example is a modification of an example taken from Oscar's Manual
    Import "mod_video";
    Import "mod_text";
    Import "mod_key";
    Import "mod_map";
    Import "mod_proc";
    Import "mod_draw";

    Process Main()
    begin
      set_mode(800,600,32);
      write(0,100,80,0,"SCALE_RESOLUTION's value:");
      write_var(0,300,80,0,scale_resolution);
      proceso();
      repeat
        if(key(_a)) scale_resolution=03200240;end
        if(key(_s)) scale_resolution=06400480;end
        if(key(_d)) scale_resolution=08000600;end
        if(key(_f)) scale_resolution=10240768;end
        if(key(_c)) scale_resolution=NULL;end
        set_mode(800,600,32);
        frame;
      until(key(_esc))
      let_me_alone();
    end

    Process proceso()
    begin
      x=180;y=150;
      graph=map_new(60,60,32);
      drawing_map(0,graph);
      drawing_color(rgb(255,255,0));
      draw_fcircle(25,25,25);
      loop
        frame;
      end
    end

Used in example: [set\_mode](set_mode "wikilink")(),
[write](write "wikilink")(), [write\_var](write_var "wikilink")(),
[map\_new](map_new "wikilink")(),
[drawing\_map](drawing_map "wikilink")(),
[drawing\_color](drawing_color "wikilink")(),
[draw\_fcircle](draw_fcircle "wikilink")().

See also
--------

[scale\_resolution\_orientation](scale_resolution_orientation "wikilink"),
[scale\_resolution\_aspectratio](scale_resolution_aspectratio "wikilink").
