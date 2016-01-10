Definition
----------

**INT** set\_fps ( &lt;**INT** fps&gt; , &lt;**INT** skip&gt; )

Sets the frames per second ([framerate](framerate "wikilink")) your
program aims to display. The more frames per second, the faster your
program runs. Some computers might not be able to display the amount of
frames you specified, and will show a lower fps. Therefore, it is
important you choose a fps that is reasonable and can also be displayed
by the somewhat slower computers. If you don't use this function then
the default fps will be used (25 fps).

Parameters
----------

  -------------- ------------------------------------------------------------------------------------------------------------------------------------------
  **INT** fps    - Frames per second to use. The default is 25.
  **INT** skip   - Frames the program is allowed to skip to keep up with the specified framerate if it's running low on processor time. The default is 0.
  -------------- ------------------------------------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : The FPS entered.

Notes
-----

If you use Set\_fps(0,0), then your program will run at the maximum
speed your computer can possibly handle.

The current FPS can be read from the [global
variable](global_variable "wikilink") [fps](fps "wikilink").

Errors
------

None.

Example
-------

    Program test;
    Begin
        Set_fps(60,0);
        Loop
            Frame;
        End
    End

<Category:functions> <Category:programinteraction> <Category:mod_video>
