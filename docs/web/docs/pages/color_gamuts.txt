BennuGD ignores this 576 set of bytes. But Are 576 bytes to save 16
color gamuts (sutsets of colors) useful to quickly paint. Each color
gamuts is composed by the next information

  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  Name                Size (Bytes)   Description
  ------------------- -------------- -------------------------------------------------------------------------------------------------------------------------------------------------------
  Number of colours   1              Number of colours that will compose this color gamut. Only support 8,16 and 32 values.

  Mode                1              Sais how will be stored the color gamut.
                                     
                                     `0 - Direct pixel: You select the first color gamut in the palette, and the next colors gamut will be used sequencialy to this.`\
                                     `1 - Editable each color: You need select each color gamut in the palette.`\
                                     `2 - Editable each 2 colours: You need select each 2 colours gamut in the palette, the colors of middle will be search automatically in the palete.`\
                                     `4 - Editable each 4 colours: Similar to each 2 colours but each 4 colors.`\
                                     `48- Editable each 8 colours: Similar to each 2 colours but each 8 colors.`

  Not Editable        1              Sais if this gamut can be editable or dont.

  Unused              1              1 unused byte

  Colours Gamut       32             Each palete index that use this gamut.
  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


