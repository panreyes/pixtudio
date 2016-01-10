Syntax
------

**INT** map\_exists ( &lt;**INT** fileID&gt; , &lt;**INT** graphID&gt; )

Description
-----------

Checks if a [graphic](graphic "wikilink") exists in the specified
[File](File "wikilink") with the specified
[graphID](graphID "wikilink").

Parameters
----------

  ----------------- ---------------------------------------------------------------------------------------------------
  **INT** fileID    - The [fileID](fileID "wikilink") of the [file](file "wikilink") that holds the graphic (or not).
  **INT** graphID   - The [graphID](graphID "wikilink").
  ----------------- ---------------------------------------------------------------------------------------------------

Returns
-------

**INT** : Whether the [graphic](graphic "wikilink") exists

  --------------------------- ---------------------------------------------------------------
  [false](false "wikilink")   - The specified [graphic](graphic "wikilink") does not exist.
  [true](true "wikilink")     - The specified [graphic](graphic "wikilink") exists.
  --------------------------- ---------------------------------------------------------------

<Category:functions> <Category:maps> <Category:mod_map>
