Definition
----------

**INT** map\_set\_name ( &lt;**INT** fileID&gt; , &lt;**INT**
graphID&gt; , &lt;**STRING** name&gt;)

Sets the name of a [graphic](graphic "wikilink") in an
[FPG](FPG "wikilink"). Useful in combination with
[map\_name](map_name "wikilink")() to retrieve names of files and
[save\_fpg](save_fpg "wikilink")() to save any changed values.

Parameters
----------

  ----------------- ------------------------------------------------------------------------------------------
  **INT** fileID    - The [fileID](fileID "wikilink") of the [file](file "wikilink") that holds the graphic.
  **INT** graphID   - The [graphID](graphID "wikilink") of the graphic.
  **STRING** name   - The new name of the graphic specified.
  ----------------- ------------------------------------------------------------------------------------------

Returns
-------

**INT** : 0

<Category:functions> <Category:maps> <Category:mod_map>
