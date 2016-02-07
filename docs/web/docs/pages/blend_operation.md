Description
-----------

A blend operation is the act of executing the blending of a
[graphic](graphic "wikilink") (source) with the pixels the graphic is
drawn on (target) using a [blend table](blend_table "wikilink").

This is done in two ways:

-   The blendop is performed explicitly using
    [blendop\_apply](blendop_apply "wikilink")(), modifying the graphic.
-   The blendop is [assigned](blendop_assign "wikilink") to a
    [graphic](graphic "wikilink") and performed implicitly when that
    graphic is drawn. This method is not available for modes lower
    than 16bit.

Blendops are not supported in 32bit mode.

<Category:blendops>
