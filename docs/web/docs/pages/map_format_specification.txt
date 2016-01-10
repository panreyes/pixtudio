Format Specification
--------------------

This section describes the structure of a [MAP](MAP "wikilink") file. It
is not necessary to know these details to program games in
[Bennu](Bennu "wikilink"), but they will be of help for those who want
to develop external tools which are able to read or write MAP files.

A [MAP](MAP "wikilink") file does not have compression.
[Bennu](Bennu "wikilink"), however, supports transparently
[GZIP](http://en.wikipedia.org/wiki/Gzip) compression in files and
usually MAP files are saved to disk compressed with GZIP. In the
following we will assume that the MAP file is not compressed.

### Header (+0)

[MAP](MAP "wikilink") files start with the following header (8 bytes).

  Name                 Size (bytes)   Description
  -------------------- -------------- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  MAGIC                3              Three character string identifying the [MAP](MAP "wikilink") file. Must contain "m01", "map", "m16" or "m32", in lower case. Depending on these value the information in the MAP file will refer to a 1 (m01), 8 (map), 16 (m16) or 32 (m32) bits per pixel (depth) MAP.
  MS-DOS Termination   4              The following bytes: 0x1A, 0x0D, 0x0A y 0x00. This termination will prevent a TYPE (in MS-DOS) command to show the binary data of the file.
  VERSION              1              Version number. The byte 0x00 for the specification in this document.

*Subtotal: 8 bytes*

### Descriptor (+8)

Following the header there are 40 bytes which describes the
[MAP](MAP "wikilink") file. This section can be understood as an
extension of the header.

  Name     Size (bytes)   Description
  -------- -------------- ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  WIDTH    2              The width in pixels of the graphic.
  HEIGHT   2              The height in pixels of the graphic.
  CODE     4              The [GraphID](GraphID "wikilink") of the graphic. [Bennu](Bennu "wikilink") ignores this value (a [MAP](MAP "wikilink") loaded in Bennu will not have a graphID unless it is inside an [FPG](FPG "wikilink")). This field, however, is kept for backwards compatibility with [DIV](DIV "wikilink") and [Fenix](Fenix "wikilink"). When writing MAP files for Bennu you should always use 0.
  NAME     32             A 32 bytes string which may be used to briefly identify by name the contents of the graphic. If the length of the description is less than 32 bytes, the string must be null-terminated (last character must be '\\0').

*Subtotal: 40 bytes*

### Palette (+48)

See [PAL](PAL#Palette "wikilink").

  Name      Size (bytes)   Description
  --------- -------------- ------------------------------------
  PALETTE   768            See [PAL](PAL#Palette "wikilink").

*Subtotal: 768 bytes*

### Ranges of Colours (+816)

See [PAL](PAL#Range_of_Colours "wikilink").

  Name               Size (bytes)   Description
  ------------------ -------------- ---------------------------------------------
  RANGE OF COLOURS   576            See [PAL](PAL#Range_of_Colours "wikilink").

*Subtotal: 576 bytes*

### Control Points (+1392)

A section to store [control points](control_point "wikilink").

  --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  Name                       Size (bytes)   Description
  -------------------------- -------------- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  NUMBER OF CONTROL POINTS   2              The number of control points stored in this MAP.

  CONTROL POINTS             *x*              Size   Description
                                              ------ ------------------------------------------
                                              2      X coordinate of the first control point.
                                              2      Y coordinate of the first control point.
                                              ...    ...
                                              2      X coordinate of the last control point.
                                              2      Y coordinate of the last control point.
                                            
                                            The [control points](control_point "wikilink"). The coordinates of a control point are stored together in 4 bytes: first 2 for the x coordinate, last 2 for the y coordinate. This is repeated as many times as there are control points stored.
                                            
                                            *x = 4 \* (number of control points)*
  --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

*Subtotal: 2 + (4 \* (number of control points) ) bytes*

### Graphic data (+1394+4\*(number of control points))

The actual graphic data.

  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  Name           Size (bytes)   Description
  -------------- -------------- ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  GRAPHIC DATA   *x*              ---------- ---------- ---------- ----------
                                  0 (+0)     1 (+2)     2 (+4)     3 (+6)
                                  4 (+8)     5 (+10)    6 (+12)    7 (+14)
                                  8 (+16)    8 (+18)    10 (+20)   11 (+22)
                                  12 (+24)   13 (+26)   14 (+28)   15 (+30)
                                  ---------- ---------- ---------- ----------
                                
                                The depth of the graphic (see [Header](#Header_(+0) "wikilink")) determines how the data is stored.
                                
                                1bpp graphics: Pixels are stored by rows. Each byte stores up to 8 pixels, meaning that a pixel is stored in one bit. If the width of the image in pixels is not multiple of 8, last byte of the row will contain up to 7 unused bits (least significant bits). [Bennu](Bennu "wikilink") ignores these bits so they can be set either to 0 or 1.
                                
                                8bpp graphics: Each pixel is stored in one byte. The value stored does not represent the color, but an index to the 256-color palette (see [Palette](#Palette_(+48) "wikilink")). All pixels are stored consecutively, i.e., there is no padding.
                                
                                16bpp graphics: Each pixel uses 2 bytes to store the color of the pixel. The color is in RGB565 format, meaning the first 5 most significant bits are used to store the red component, next 6 to store the green component and last 5 least significant bits store the blue component. Although this format does not contain information on alpha, [Bennu](Bennu "wikilink") understands color 0x0000 as transparent. All pixels are stored consecutively, i.e., there is no padding.
                                
                                The example to the right shows a 16bit 4x4 graphic, with pixel numbers outside and byte offset inside the parenthesis.
                                
                                32bpp graphics: Each pixel uses 4 bytes to store the color of the pixel. The color is in ARGB format, 8 bits for alpha component, 8 bits for red, 8 bits for green and 8 bits for blue. A pixel with an alpha component set to 0xFFFFFFFF is totally opaque while if set to 0x00000000 it will be completely transparent. All pixels are stored consecutively, i.e., there is no padding.
                                
                                *x = (width + ((8 - (width % 8)) & 7)) / 8 \* height* (depth in bytes -1bpp graphics-)
                                
                                *x = width \* height \* depth/8* (depth in bytes -8, 16, 32bpp graphics-)
  ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

*Subtotal: width \* height \* depth/8 bytes* (depth in bytes)

***Total: 1394 + (4\*(number of control points)) + (width \* height \*
depth/8) bytes***
