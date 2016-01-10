Definition
----------

**INT** Move\_scroll ( &lt;**INT** scrollnumber&gt;)

The move\_scroll function is a slighty more advanced function. It allow
the scroll's internal coordinates x0, y0, x1 and y1 of the [scroll
structure](scroll "wikilink") to be updated in a forcefull way. This
gives great flexibility when multiple [scroll
windows](scroll_window "wikilink") are used.

For instance, in a situation where multiple scroll windows are active on
screen, and one scroll is controlled by the main player, the other
scrolls can be updated manually. However, the function can also be
usefull when there's only one scroll active. In that case you can have
any process take control over the scroll.

Also called [scroll\_move](scroll_move "wikilink")().

Parameters
----------

  ---------------------- --------------------------------------------
  **INT** scrollnumber   - The ID for the scroll window to be moved
  ---------------------- --------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Example
-------


    IMPORT "mod_video";
    IMPORT "mod_map";
    IMPORT "mod_scroll";
    IMPORT "mod_screen";
    IMPORT "mod_key";
    IMPORT "mod_proc";

    GLOBAL

    int graphics;
    int counter;

    PRIVATE



    PROCESS main();


    BEGIN
        set_fps(100, 0);
        graphics=load_fpg("help.fpg");
        start_scroll(0, graphics, 103, 102, 0, 15);

        scroll.camera=id; // assign the "main" process instance (this one) to the scroll's camera.
        priority=100;

        FROM counter=-2000 TO 2000 step 100;
            movable_process(counter);
        END

        say("Use the right and left cursors to move");

        graph=101;
        ctype=c_scroll;


        LOOP
            if (key(_right))
                x+=2;
                flags=0;
            END
            if (key(_left))
                x-=2;
                flags=1;
            END

            move_scroll(0); // Updates the scroll structure[], in this case affect scroll 0.

            FRAME;
        END
    END

    PROCESS movable_process(x_scroll);

    PRIVATE

    BEGIN
        ctype=c_scroll;
        z=100;
        graph=104;
        LOOP
            x=x_scroll-scroll.x0; 
            FRAME;
        END
    END

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

<Category:functions> <Category:scrolls> <Category:mod_scroll>
