Definition
----------

**INT** png\_save ( &lt;**INT** fileID&gt; , &lt;**INT** graphID&gt; ,
&lt;**STRING** filename&gt; )

Saves the specified [graphic](graphic "wikilink") as *filename* with the
format [PNG](PNG "wikilink").

The previous name [save\_png](save_png "wikilink")() is deprecated.

Parameters
----------

  --------------------- ---------------------------------------------------------------------------------------------------------
  **INT** fileID        - The [fileID](fileID "wikilink") of the [file](file "wikilink") that holds the graphic.
  **INT** graphID       - The [graphID](graphID "wikilink") of the graphic to save.
  **STRING** filename   - The name of the [PNG](PNG "wikilink") file to be saved, including a possible [path](path "wikilink").
  --------------------- ---------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : Successrate

  --------------------------- ------------
  [false](false "wikilink")   - Error.
  [true](true "wikilink")     - Success.
  --------------------------- ------------

Example
-------

    //here's a cool thing to save a screenshot
    import "mod_map"
    import "mod_screen"
    import "mod_key"

    Global
        int takingscreenshot;
    End

    Process Main()
    Begin

        Loop
            
            If (key(_F12)) 
                If (takingscreenshot==0)
                    takingscreenshot=1;
                    graph=screen_get(); // grabs the screen and sets it as the program graphic
                    png_save(0,graph,"shot"+rand(0,9999)+".png"); // saves the graphic as a png with a
                                                                  // random number in the filename to
                                                                  // prevent overwriting 
                    map_unload(0,graph);  //frees the graphic
                Else
                    takingscreenshot=0;
                End
                While(key(_F12)) Frame; End
           End

            frame;
        End
    End

Used in example: [key](key "wikilink")(),
[screen\_get](screen_get "wikilink")(),
[png\_save](png_save "wikilink")(),
[map\_unload](map_unload "wikilink")()

<Category:functions> <Category:maps> <Category:mod_map>
