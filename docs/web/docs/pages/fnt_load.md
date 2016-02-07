Definition
----------

**INT** fnt\_load ( &lt;**STRING** filename&gt;, \[ &lt;**POINTER**
id&gt;\] )

Loads a [FNT](FNT "wikilink") file into memory as a
[font](font "wikilink"). A font is usually with the extension *.fnt*.

The previous name [load\_fnt](load_fnt "wikilink")() is deprecated.

Parameters
----------

  --------------------- -----------------------------------------------------------------------------------------------------------------
  **STRING** filename   - The filename of the [FNT](FNT "wikilink") file that you wish to load (including extension and possible path).
  **POINTER** id        - Optional parameter, for loading a font in the background.
  --------------------- -----------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : [graphID](graphID "wikilink")

  -------- -------------------------------------------------
  -2       - Waiting for the file to be loaded, see notes.
  -1       - There was an error loading the file.
  &gt;=0   - The graphID of the newly created font.
  -------- -------------------------------------------------

*the following applies for versions prior rc282:*

**INT** : [FontID](FontID "wikilink")

  ------- --------------------------------------------------------------------------------------
  -1      - Error: file does not exist.
  0       - Filename could not be obtained from the specified string (doesn't happen usually).
  &gt;0   - The FontID.
  ------- --------------------------------------------------------------------------------------

Errors
------

  ----------------------- -------------------------------------------------------------
  Format not recognized   - The format of the specified file could not be recognized.
  ----------------------- -------------------------------------------------------------

Notes
-----

The optional parameter **id** was introduced in version rc282 and allows
you to load resources in the background. It used with the
[Offset](Offset "wikilink") operator. See example below:

          load_fnt("archivo_gordo.fnt", &idfnt);
          while(idfnt==-2)
                say("Big File Loading ....");
                frame;
          end
          if(idfnt==-1)
              say("Something went wrong!!");
              exit(); // o return
          end

          say("Big file loaded ok!!");

<Category:functions> <Category:fonts> <Category:mod_map>
