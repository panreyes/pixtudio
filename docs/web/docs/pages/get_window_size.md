Syntax
------

**INT** get\_window\_size ( &lt;**INT POINTER** window\_width&gt; ,
&lt;**INT POINTER** window\_height&gt; , &lt;**INT POINTER**
client\_width&gt; , &lt;**INT POINTER** client\_height&gt; )

Description
-----------

Get the window and client size.

Parameters
----------

  -------------------------------- -----------------------------------------------------------------
  **INT POINTER** window\_width    - Pointer to where the window width will be written.
  **INT POINTER** window\_height   - Pointer to where the window height will be written.
  **INT POINTER** client\_width    - Pointer to where the client width of window will be written.
  **INT POINTER** client\_height   - Pointer to where the client height of window will be written.
  -------------------------------- -----------------------------------------------------------------

Returns
-------

**INT** : Successrate

  --------------------------- ----------
  [false](false "wikilink")   - Error.
  [true](true "wikilink")     - Ok.
  --------------------------- ----------

Example
-------

    import "mod_key"
    import "mod_video"
    import "mod_text"
    import "mod_wm"
    Global
        desktop_width = 640;
        desktop_height = 480;
        window_width = 0;
        window_height = 0;
        client_width = 0;
        client_height = 0;
    End

    Process Main()
    Begin
      
        get_desktop_size(& desktop_width,& desktop_height);
        get_window_size ( & window_width,  &window_height , & client_width ,  & client_height );
        set_mode (desktop_width-window_width+client_width,desktop_height-window_height+client_height,32);
        set_window_pos(0,0);
      
        write(0,desktop_width/2,desktop_height/2+30,0,"ESC to exit");
        while (!key(_ESC) )
            frame;
        end
    End

Used in example: [get\_desktop\_size](get_desktop_size "wikilink")(),
[get\_window\_size](get_window_size "wikilink")(),
[set\_mode](set_mode "wikilink")(),
[set\_window\_pos](set_window_pos "wikilink")(),
[write](write "wikilink")(), [key](key "wikilink")()

<Category:functions> <Category:programinteraction> <Category:mod_wm>
