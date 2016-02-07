Header
------

  Name                                      Size (Bytes)   Description
  ----------------------------------------- -------------- --------------------------------------------------------------------------------------------------------------------------------
  Magic                                     3              character string that must containg "fnx"
  MSDOS-END                                 4              the four bytes 1Ah,0Dh,0Ah,00h
  Bits Per Pixel                            1              Font color depht can be equal to: 1,8,16,32
  Colors Palette                            768            256 RGB colors using 1 byte for each component where the two first bits are ignored, so a component can be from 0 to 63 value.
  [Color Gamuts](Color_Gamuts "wikilink")   576            16 color gamuts (sutsets of colors) useful to quickly paint.NOTE: currenly ignored
  charset                                   4              Characters set, can be 0 or 1 to ISO8859 or CP850.

Now goes 256 character Descriptors. one for each ASCII letter

Characters Desciptor
--------------------

  Name                Size (Bytes)   Description
  ------------------- -------------- -------------
  width               4              
  height              4              
  width offset        4              
  height offset       4              
  horizontal offset   4              
  vertical offset     4              
  data offset         4              

And finaly the graphics data

Graphics Data
-------------

The size of each graphic will be width \* height \* bits\_per\_pixel /
8, except to 1 bit that use a rounded byte line formula,
round(width/8)\*8 \* height. To optain the exact position you need use
the data offset stored in the descriptor of each data.
