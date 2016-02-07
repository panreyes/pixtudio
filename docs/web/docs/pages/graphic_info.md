Definition
----------

**INT** graphic\_info ( &lt;**INT** fileID&gt; , &lt;**INT** graphID&gt;
, &lt;**INT** infotype&gt; )

Gets some information about the [graph](graph "wikilink") specified.
This function is also known as [Map\_info](Map_info "wikilink")() and
[Map\_info\_get](Map_info_get "wikilink")().

Parameters
----------

  ------------------ ------------------------------------------------------------------------
  **INT** fileID     - The [file](file "wikilink") that holds the graph.
  **INT** graphID    - The [graph](graph "wikilink") to get information from.
  **INT** infotype   - What [type of information](graphical_infotypes "wikilink") you want.
  ------------------ ------------------------------------------------------------------------

Returns
-------

**INT** : Returns the information you want.\
If the specified graph was invalid it returns 0.\
If the specified infotype was not recognized it returns 1.

Example
-------

    Program keuken;
    Local
        gxc;
        gyc;

    Begin

        set_mode(640,480,16);
        
        graph=new_map(rand(50,150),rand(50,150),16); //makes a randomly proportioned red rectangle
        map_clear(0,graph,rgb(255,0,0));
        x=320;
        y=240;

        gxc=graphic_info(0,graph,G_X_CENTER);
        gyc=graphic_info(0,graph,G_Y_CENTER);  //finds the graphic's center coordinates

        map_put_pixel(0,graph,gxc,gyc,rgb(255,255,255)); //puts a white pixel in the center of the graphic

        Loop
      
            frame;
        End
    End

Used in example: [set\_mode](set_mode "wikilink")(),
[new\_map](new_map "wikilink")(), [map\_clear](map_clear "wikilink")(),
[map\_put\_pixel](map_put_pixel "wikilink")()

<Category:functions> <Category:maps> <Category:mod_map>
