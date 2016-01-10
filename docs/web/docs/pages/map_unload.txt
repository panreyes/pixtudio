Definition
----------

**INT** map\_unload ( &lt;**INT** fileID&gt; , &lt;**INT** graphID&gt; )

Frees the memory used by the specified [graphic](graphic "wikilink").
The associated
([fileID](fileID "wikilink"),[graphID](graphID "wikilink")) combination
is no longer valid afterwards.

Also called [map\_del](map_del "wikilink")(). The previous name
[unload\_map](unload_map "wikilink") is deprecated.

Parameters
----------

  ----------------- ------------------------------------------------------------------------------------------
  **INT** fileID    - The [fileID](fileID "wikilink") of the [file](file "wikilink") that holds the graphic.
  **INT** graphID   - The [graphID](graphID "wikilink") of the graphic to unload.
  ----------------- ------------------------------------------------------------------------------------------

Returns
-------

**INT** : Successrate

  --------------------------- ---------------------
  [false](false "wikilink")   - Invalid graphic.
  [true](true "wikilink")     - Graphic unloaded.
  --------------------------- ---------------------

<Category:functions> <Category:maps> <Category:mod_map>
