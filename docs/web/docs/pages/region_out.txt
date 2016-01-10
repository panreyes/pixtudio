Definition
----------

**INT** out\_region ( &lt;**INT** processID&gt; , &lt;**INT**
regionID&gt; )

Checks if the specified [process](process "wikilink") is completely
outside of the specified [region](region "wikilink").

The check is not pixel perfect, but uses the [bounding
box](bounding_box "wikilink") of the process.

Also called [out\_region](out_region "wikilink")().

Parameters
----------

  ------------------- --------------------------------------------------------------------
  **INT** processID   - The [processID](processID "wikilink") of the process to check.
  **INT** regionID    - The [regionID](regionID "wikilink") of the region to check with.
  ------------------- --------------------------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")/[false](false "wikilink"): whether the
process is completely outside the region.

  --------------------------- -------------------------------------------------------------------------------------
  [true](true "wikilink")     - The process is completely outside the region.
  [false](false "wikilink")   - The process is (partly) inside the region or invalid region or process specified.
  --------------------------- -------------------------------------------------------------------------------------

<Category:functions> <Category:Regions> <Category:mod_screen>
