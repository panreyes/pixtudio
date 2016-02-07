Description
-----------

Blur modes are used to specify the mode of blurring in the
[blur](blur "wikilink")().

List
----

  ---------------- ----------- --------------------------------------------------------------------------------
  *Constant*       - *Value*   - *Description*
  BLUR\_NORMAL     - 0         - single pixel: considers pixels located to the left and above of each pixel.
  BLUR\_3X3        - 1         - 3x3: considers all 8 adjacent pixels.
  BLUR\_5X5        - 2         - 5x5: considers the 24 pixels that surrounds each pixel.
  BLUR\_5X5\_MAP   - 3         - 5x5 with additional map: Just as the previous one but using a temporary map.
  ---------------- ----------- --------------------------------------------------------------------------------

Examples
--------

<Category:constantcategories> <Category:mod_effects>
