Syntax
------

**INT** pal\_load ( &lt;**STRING** filename&gt;, \[ &lt;**POINTER**
id&gt;\] )

Description
-----------

Loads a color palette from a file.

The current [palette](palette "wikilink") is switched to the loaded one.
Note that one can load a palette from an 8bit [FPG](FPG "wikilink") or
[MAP](MAP "wikilink") file (the remaining graphic data will not be
loaded) or a [PAL](PAL "wikilink") file.

The previous name [load\_pal](load_pal "wikilink")() is deprecated.

Parameters
----------

  --------------------- ----------------------------------------------------------------------------------------------------------------------------------
  **STRING** filename   - The filename of the file that you wish to load the [palette](palette "wikilink") from (including extension and possible path).
  **POINTER** id        - Optional parameter, for loading a palette in the background.
  --------------------- ----------------------------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : [graphID](graphID "wikilink")

  -------- -------------------------------------------------
  -2       - Waiting for the file to be loaded, see notes.
  -1       - There was an error loading the file.
  &gt;=0   - The graphID of the newly created palette.
  -------- -------------------------------------------------

*the following applies for versions prior rc282:*

**INT** : Error.

  ---- ----------------------------------------------------------------------------------------------------
  -1   - Error: could not open file; corrupt or truncated file; file doesn't contain palette information.
  0    - Error: could not obtain filename; some [FPL](FPL "wikilink") error.
  1    - No error: [palette](palette "wikilink") was loaded with success.
  ---- ----------------------------------------------------------------------------------------------------

Example
-------

    Program example;
    Begin

        load_pal("example.pal");

        Loop
            frame;
        End

    End

Notes
-----

The optional parameter **id** was introduced in version rc282 and allows
you to load resources in the background. It used with the
[Offset](Offset "wikilink") operator. See example below:

          load_pal("archivo_gordo.pal", &idpal);
          while(idpal==-2)
                say("Big File Loading ....");
                frame;
          end
          if(idpal==-1)
              say("Something went wrong!!");
              exit(); // o return
          end

          say("Big file loaded ok!!");

<Category:functions> <Category:palettes> <Category:mod_map>
