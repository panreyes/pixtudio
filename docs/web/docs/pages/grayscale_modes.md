Description
-----------

Greyscale modes are used to specify the mode of color scaling in the
[Grayscale](Grayscale "wikilink")().

[Grayscale modes](Grayscale_modes "wikilink")
---------------------------------------------

  ------------- ----------- ----------------------------------------------------------------
  *Constant*    - *Value*   - *Description*
  GSCALE\_RGB   - 0         - changes the graphic to monochrome.
  GSCALE\_R     - 1         - changes the graphic to RED scale.
  GSCALE\_G     - 2         - changes the graphic to GREEN scale.
  GSCALE\_B     - 3         - changes the graphic to BLUE scale.
  GSCALE\_RG    - 4         - changes the graphic to YELLOW scale.
  GSCALE\_RB    - 5         - changes the graphic to PURPLE scale.
  GSCALE\_GB    - 6         - changes the graphic to CYAN scale.
  GSCALE\_OFF   - -1        - no change, graphic stays as it is, so filter is not applied.
  ------------- ----------- ----------------------------------------------------------------

Notes
-----

The exact formula is:

    c = 0.3 * oldpixel_r + 0.59 * oldpixel_g + 0.11 * oldpixel_b

Method `0`:

    for every pixel:
        newpixel_rgb = (c,c,c)

Method `1`:

    for every pixel:
        newpixel_rgb = (c,0,0)

Method `2`:

    for every pixel:
        newpixel_rgb = (0,c,0)

Method `3`:

    for every pixel:
        newpixel_rgb = (0,0,c)

Method `4`:

    for every pixel:
        newpixel_rgb = (c,c,0)

Method `5`:

    for every pixel:
        newpixel_rgb = (c,0,c)

Method `6`:

    for every pixel:
        newpixel_rgb = (0,c,c)

Other methodnumbers:

    for every pixel:
        newpixel_rgb = oldpixel_rgb

Note that `[[rgbscale]](0,map,1,1,1) = [[grayscale]](0,map,0)` for a
valid graphic (0,map).

<Category:constantcategories> <Category:mod_effects>
