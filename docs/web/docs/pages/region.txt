<category:General> <category:variables> <category:predefined>
[category:local variables](category:local_variables "wikilink")
<category:librender>

[**Up to Local Variables**](Local_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

### Local variable

**INT** region = 0

**Region** is a predefined [local variable](local_variable "wikilink").
**Region** holds the [RegionID](RegionID "wikilink") of the
[region](region "wikilink") in which the [process](process "wikilink")'
[graphic](graphic "wikilink") should only be displayed in. By default
this is region *0*, the whole screen.

The graphic of the process is only displayed in its region, even if the
x and y coordinates are outside of the region, the part inside the
region will still be displayed.

### Concept

A region is a rectangular field inside the screen. It can be defined
with [define\_region](define_region "wikilink")() and can be useful for
displaying graphics in only certain parts of the screen and for the
function [region\_out](region_out "wikilink")(). There are 32 regions
(*0..31*) and region *0* is the whole screen.
