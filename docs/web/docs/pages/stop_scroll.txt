Definition
----------

**INT** Stop\_scroll ( &lt;**INT** scrollnumber&gt;)

This functions stops an active [scroll
window](scroll_window "wikilink"). There can be up to 10 (0-9) [scroll
windows](scroll_window "wikilink") active. When the scroll is stopped,
all the processes in it will no longer be displayed. This function is
usefull for switching the game's state from active gameplay to a loading
screen state or similair situations. Another use is, when there are
multiple scroll [regions](region "wikilink") active, and the game
changes from split screen to single screen. This way you can have
individual control over the display of the scroll.

Also called [scroll\_stop](scroll_stop "wikilink")().

Parameters
----------

  ---------------------- ----------------------------------------------
  **INT** scrollnumber   - The ID for the scroll window to be stopped
  ---------------------- ----------------------------------------------

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

    PROCESS main();


    BEGIN

        graphics=load_fpg("help.fpg");

        say("Press [ENTER] to activate the scroll window.");
        say("Press [SPACE] to stop the scroll.");


        LOOP
            IF (scan_code==_space)

                stop_scroll(0); // The scroll is stopped.

            END
            IF (scan_code==_enter)
                start_scroll(0, 0, 103, 102, 0, 15);
            END
           
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
