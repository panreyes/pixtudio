Definition
----------

**INT** region\_define ( &lt;**INT** regionID&gt; , &lt;**INT** x&gt; ,
&lt;**INT** y&gt; , &lt;**INT** width&gt; , &lt;**INT** height&gt; )

Defines the boundaries of a [region](region "wikilink").

There are 32 regions, range `0..31`. Region *0* is always the whole
screen and cannot be changed. Defining regions can be useful for the
function [out\_region](out_region "wikilink")(), the [local
variable](local_variable "wikilink") [region](region "wikilink") and
using them with [scrolls](scrolls "wikilink").

Also called [define\_region](define_region "wikilink")().

Parameters
----------

  ------------------ ----------------------------------------------------------------
  **INT** regionID   - The [regionID](regionID "wikilink") of the region to define.
  **INT** x          - The x coordinate of the top left corner of the region.
  **INT** y          - The y coordinate of the top left corner of the region.
  **INT** width      - The width of the region.
  **INT** height     - The height of the region.
  ------------------ ----------------------------------------------------------------

Returns
-------

**INT** : The [regionID](regionID "wikilink") specified.

<Category:functions> <Category:Regions> <Category:mod_screen>
