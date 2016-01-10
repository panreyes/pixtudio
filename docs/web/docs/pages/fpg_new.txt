Definition
----------

**INT** fpg\_new ( )

Creates and initializes a new [file](file "wikilink").

To add [graphics](graphic "wikilink") to the created file, use the
returned [fileID](fileID "wikilink") in the function
[fpg\_add](fpg_add "wikilink")(). The file can be saved with
[fpg\_save](fpg_save "wikilink")(). To free a file, use
[fpg\_unload](fpg_unload "wikilink")().

The previous name [new\_fpg](new_fpg "wikilink")() is deprecated.

Returns
-------

**INT** : [fileID](fileID "wikilink")

  -------- ------------------------------------------
  -1       - Too many files or insufficient memory.
  &gt;=0   - The fileID of the new file.
  -------- ------------------------------------------

Errors
------

  --------------------- ---------------------------------------------------------------------------
  Insufficient memory   - There is insufficient memory available. This error doesn't occur often.
  --------------------- ---------------------------------------------------------------------------

<Category:functions> <Category:fpg> <Category:mod_map>
