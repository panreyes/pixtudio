Definition
----------

**INT** fpg\_save( &lt;**INT** fileID&gt; , &lt;**STRING** filename&gt;
)

Saves a certain [file](file "wikilink") to disk.

The previous name [save\_fpg](save_fpg "wikilink")() is deprecated.

Parameters
----------

  --------------------- ------------------------------------------------------------------------------------------------------
  **INT** fileID        - The [fileID](fileID "wikilink") of the [file](file "wikilink") to save.
  **STRING** filename   - The name of the [file](file "wikilink") to be saved, including a possible [path](path "wikilink").
  --------------------- ------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : Success

  --------------------------- ---------------------------------------------------------------------------------------------------
  [false](false "wikilink")   - Invalid [fileID](fileID "wikilink") or filename; The errors under [Errors](#Errors "wikilink").
  [true](true "wikilink")     - Success.
  --------------------------- ---------------------------------------------------------------------------------------------------

Errors
------

  ------------------------- ------------------------------------------------------------------------------------------------------------
  Insufficient memory       - There is insufficient memory available. This error doesn't occur often.
  Empty library             - The specified [file](file "wikilink") contains no [graphics](graphic "wikilink").
  Unsupported color depth   - A [graphic](graphic "wikilink") in the specified [file](file "wikilink") has an unsupported color depth.
  Differing color depths    - An [FPG](FPG "wikilink") can't hold [graphics](graphic "wikilink") of different color depths.
  ------------------------- ------------------------------------------------------------------------------------------------------------

<Category:functions> <Category:fpg> <Category:mod_map>
