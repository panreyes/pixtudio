Definition
----------

**INT** map\_save ( &lt;**INT** fileID&gt; , &lt;**INT** graphID&gt; ,
&lt;**STRING** filename&gt; )

Saves the specified [graphic](graphic "wikilink") as *filename* with the
format [MAP](MAP "wikilink").

The previous name [save\_map](save_map "wikilink")() is deprecated.

Parameters
----------

  --------------------- ------------------------------------------------------------------------------------------
  **INT** fileID        - The [fileID](fileID "wikilink") of the [file](file "wikilink") that holds the graphic.
  **INT** graphID       - The [graphID](graphID "wikilink") of the graphic to unload.
  **STRING** filename   - The name of the [MAP](MAP "wikilink") file to be saved, including a possible path.
  --------------------- ------------------------------------------------------------------------------------------

Returns
-------

**INT** : Successrate

  --------------------------- ---------------------------------------------------
  [false](false "wikilink")   - An error: Invalid graphic; could not open file.
  [true](true "wikilink")     - Graphic saved.
  --------------------------- ---------------------------------------------------

<Category:functions> <Category:maps> <Category:mod_map>
