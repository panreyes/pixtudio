Definition
----------

**INT** map\_clone ( &lt;**INT** fileID&gt; , &lt;**INT** graphID&gt; )

Clones a certain [graphic](graphic "wikilink") and puts it in the
[system file](system_file "wikilink").

Parameters
----------

  ----------------- ---------------------------------------------------------------------------------------
  **INT** fileID    - The [fileID](fileID "wikilink") of the [file](file "wikilink") holding the graphic.
  **INT** graphID   - The [graphID](graphID "wikilink") of the graphic to be cloned.
  ----------------- ---------------------------------------------------------------------------------------

Returns
-------

**INT** : [GraphID](GraphID "wikilink")

  ------- -------------------------------------
  0       - Invalid graphic specified;
  &gt;0   - The graphID of the clone graphic.
  ------- -------------------------------------

Errors
------

  ------------------------- ---------------------------------------------------------------------------------------
  Unsupported color depth   - The specified graph has a not supported color depth. *(Console)*
  Insufficient memory       - There is insufficient memory available. This error doesn't occur often. *(Console)*
  ------------------------- ---------------------------------------------------------------------------------------

<Category:functions> <Category:maps> <Category:mod_map>
