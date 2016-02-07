Definition
----------

**INT** fnt\_save ( &lt;**INT** fontID&gt; , &lt;**STRING** filename&gt;
)

Saves a [font](font "wikilink") as a file. A font is usually with the
extension ".fnt".

If the specified filename contains no extension, ".fnt" is added to it.

The previous name [save\_fnt](save_fnt "wikilink")() is deprecated.

Parameters
----------

  --------------------- -------------------------------------------------------------------------------
  **INT** fontID        - The [fontID](fontID "wikilink") of the [font](font "wikilink") to be saved.
  **STRING** filename   - The name of the font file to be saved, including a possible path.
  --------------------- -------------------------------------------------------------------------------

Returns
-------

**INT** : Successrate

  --------------------------- ---------------------------------------------------------------------------------------------------------------------------------
  [false](false "wikilink")   - Filename could not be obtained from the specified string (doesn't happen usually) or one of the [errors](#Errors "wikilink").
  [true](true "wikilink")     - Font successfully saved.
  --------------------------- ---------------------------------------------------------------------------------------------------------------------------------

Errors
------

  ----------------------- ---------------------------------------------------------------------------
  Invalid fontID          - The specified [fontID](fontID "wikilink") was invalid.
  Unable to create file   - The file could not be created.
  Font corrupt            - The font trying to be saved is corrupt.
  Insufficient memory     - There is insufficient memory available. This error doesn't occur often.
  ----------------------- ---------------------------------------------------------------------------

<Category:functions> <Category:fonts> <Category:mod_map>
