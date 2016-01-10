Definition
----------

**INT** png\_load ( &lt;**STRING** filename&gt;, \[ &lt;**POINTER**
id&gt;\] )

Creates a new [graphic](graphic "wikilink"), using the specified
[PNG](PNG "wikilink") file as contents and puts it in the [system
file](system_file "wikilink"). Returns the [graphID](graphID "wikilink")
of the created graphic. The [color depth](color_depth "wikilink") of the
created graphic will be the same as the loaded PNG file.

The previous name [load\_png](load_png "wikilink")() is deprecated.

Parameters
----------

  --------------------- ----------------------------------------------------------------------------------------------------------
  **STRING** filename   - The name of the [PNG](PNG "wikilink") file to be loaded, including a possible [path](path "wikilink").
  **POINTER** id        - Optional parameter, for loading a map in the background.
  --------------------- ----------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : [graphID](graphID "wikilink")

  -------- -------------------------------------------------
  -2       - Waiting for the file to be loaded, see notes.
  -1       - There was an error loading the file.
  &gt;=0   - The graphID of the newly created graphic.
  -------- -------------------------------------------------

*the following applies for versions prior rc282:*

**INT** : [graphID](graphID "wikilink")

  ------- ---------------------------------------------
  0       - There was an error loading the file.
  &gt;0   - The graphID of the newly created graphic.
  ------- ---------------------------------------------

Notes
-----

The optional parameter **id** was introduced in version rc282 and allows
you to load resources in the background. It used with the
[Offset](Offset "wikilink") operator. See example below:

          load_png("archivo_gordo.png", &idpng);
          while(idpng==-2)
                say("Big File Loading ....");
                frame;
          end
          if(idpng==-1)
              say("Something went wrong!!");
              exit(); // o return
          end

          say("Big file loaded ok!!");

Example
-------

Checkout the [PNG\_LoadDirectory](Tutorial:PNG_LoadDirectory "wikilink")
tutorial.

<Category:functions> <Category:maps> <Category:mod_map>
