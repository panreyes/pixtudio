Definition
----------

**INT** fpg\_add ( &lt;**INT** destFileID&gt; , &lt;**INT**
destGraphID&gt; , &lt;**INT** origFileID&gt; , &lt;**INT**
origGraphID&gt; )

Copies a certain [graphic](graphic "wikilink") in a certain
[file](file "wikilink") to a certain file with a certain
[graphID](graphID "wikilink").

Parameters
----------

  --------------------- -------------------------------------------------------------------------------------------------------------
  **INT** destFileID    - The [fileID](fileID "wikilink") of the destination [file](file "wikilink").
  **INT** destGraphID   - The [graphID](graphID "wikilink") in the destination file where to add the [graphic](graphic "wikilink").
  **INT** origFileID    - The [fileID](fileID "wikilink") of the original file where the graphic is located.
  **INT** origGraphID   - The [graphID](graphID "wikilink") of the graphic to add.
  --------------------- -------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : [graphID](graphID "wikilink")

  ------- -------------------------------------------
  -1      - Invalid destination file or graphID.
  0       - Invalid original file or graphID.
  &gt;0   - The GraphID of the destination graphic.
  ------- -------------------------------------------

<Category:functions> <Category:fpg> <Category:mod_map>
