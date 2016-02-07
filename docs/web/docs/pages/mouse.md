<category:variables> <category:predefined> [category:global
variables](category:global_variables "wikilink") <category:libmouse>

[**Up to Global Variables**](Global_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**Struct** Mouse

Mouse is a [global variable](global_variable "wikilink")
[struct](struct "wikilink"), containing information about the current
state of the mouse. Also graphical settings can be configured to display
a [graphic](graphic "wikilink") following the mouse in a certain way.

Members
-------

  ------------------- --------------------------------------------------------------------------------------------------------------------------------------
  *Member name*       - *Description*
  **INT** x           - The [X](X "wikilink")-coordinate of the mouse.
  **INT** y           - The [Y](Y "wikilink")-coordinate of the mouse.
  **INT** graph       - The [graphID](graphID "wikilink") of the [graphic](graphic "wikilink") of the mouse.
  **INT** file        - The [fileID](fileID "wikilink") of the [file](file "wikilink") in which the [graphic](graphic "wikilink") of the mouse is located.
  **INT** z           - The [Z](Z "wikilink")-coordinate of the mouse.
  **INT** angle       - The [angle](angle "wikilink") of the mouse process.
  **INT** size        - The [size](size "wikilink") of the mouse process.
  **INT** flags       - The [render flags](render_flags "wikilink") of the mouse process.
  **INT** region      - The [region](region "wikilink") of the mouse process.
  **INT** left        - [true](true "wikilink")/[false](false "wikilink"): whether the left mouse button is pressed.
  **INT** middle      - [true](true "wikilink")/[false](false "wikilink"): whether the middle mouse button is pressed.
  **INT** right       - [true](true "wikilink")/[false](false "wikilink"): whether the right mouse button is pressed.
  **INT** wheelup     - [true](true "wikilink")/[false](false "wikilink"): whether the mouse wheel is scrolled upwards.
  **INT** wheeldown   - [true](true "wikilink")/[false](false "wikilink"): whether the mouse wheel is scrolled downwards.
  ------------------- --------------------------------------------------------------------------------------------------------------------------------------

Example
-------

    import "mod_map"
    import "mod_mouse"
    import "mod_wm"

    Process Main()
    Private
        int dmap;
        int rmap;
        int gmap;
        int bmap;
        int ymap;
        int cmap;
        int mmap;
        int wmap;
    Begin

        // Create a dark graph
        dmap = new_map(100,100,8);
        map_clear(0,dmap,rgb(50,50,50));

        // Create a red graph
        rmap = new_map(100,100,8);
        map_clear(0,rmap,rgb(255,0,0));

        // Create a green graph
        gmap = new_map(100,100,8);
        map_clear(0,gmap,rgb(0,255,0));

        // Create a blue graph
        bmap = new_map(100,100,8);
        map_clear(0,bmap,rgb(0,0,255));

        // Create a yellow graph
        ymap = new_map(100,100,8);
        map_clear(0,ymap,rgb(255,255,0));

        // Create a cyan graph
        cmap = new_map(100,100,8);
        map_clear(0,cmap,rgb(0,255,255));

        // Create a magenta graph
        mmap = new_map(100,100,8);
        map_clear(0,mmap,rgb(255,0,255));

        // Create a white graph
        wmap = new_map(100,100,8);
        map_clear(0,wmap,rgb(255,255,255));

        Repeat
            if(mouse.left) // +Red
                if(mouse.right) // +Green
                    if(mouse.middle) // +Blue
                        mouse.graph = wmap;
                    else
                        mouse.graph = ymap;
                    end
                else
                    if(mouse.middle) // +Blue
                        mouse.graph = mmap;
                    else
                        mouse.graph = rmap;
                    end
                end
            elseif(mouse.right) // +Green
                if(mouse.middle) // +Blue
                    mouse.graph = cmap;
                else
                    mouse.graph = gmap;
                end
            elseif(mouse.middle) // +Blue
                mouse.graph = bmap;
            else // Dark
                mouse.graph = dmap;
            end
            frame;
        Until(exit_status)

    End

Used in example: [Mouse](Mouse "wikilink"),
[new\_map](new_map "wikilink")(), [map\_clear](map_clear "wikilink")(),
[graph](graph "wikilink"), [exit\_status](exit_status "wikilink")

Shows some use of maps and the mouse.
