Definition
----------

Graphical infotypes are used in
[graphic\_info](graphic_info "wikilink")(), to specify what information
about a graph is wanted.

List
----

  --------------------- ----------- ------------------------------------------------------------------------------------------------------------------------------------------
  *Constant*            - *Value*   - *Description*
  G\_WIDTH              - 0         - Width in [pixels](pixels "wikilink"). G\_WIDE is equivalent, but deprecated.
  G\_HEIGHT             - 1         - Height in pixels.
  G\_X\_CENTER          - 2         - X-axis center. Also called G\_CENTER\_X
  G\_Y\_CENTER          - 3         - Y-axis center. Also called G\_CENTER\_Y
  G\_PITCH              - 4         - Width in bytes.
  G\_DEPTH              - 5         - [Color depth](Color_depth "wikilink") in bits per pixel.
  G\_FRAMES             - 6         - Number of frames.
  G\_ANIMATION\_STEP    - 7         - Current frame in animation.
  G\_ANIMATION\_STEPS   - 8         - Number of frames in animation.
  G\_ANIMATION\_SPEED   - 9         - Current speed of animation.
  B\_CLEAR              - 1         - Used in function [map\_new](map_new "wikilink")(), indicates if a bitmap is cleared.
  CHARSET\_ISO8859      - 0         - Used to select [iso8859](http://en.wikipedia.org/wiki/ISO/IEC_8859-15) character set in the function [fnt\_new](fnt_new "wikilink")().
  CHARSET\_CP850        - 1         - Used to select [cp850](http://en.wikipedia.org/wiki/Code_page_850) character set in the function [fnt\_new](fnt_new "wikilink")().
  NFB\_VARIABLEWIDTH    - 0         - Flag for the function [fnt\_new](fnt_new "wikilink")().
  NFB\_FIXEDWIDTH       - 1         - Flag for the function [fnt\_new](fnt_new "wikilink")().
  --------------------- ----------- ------------------------------------------------------------------------------------------------------------------------------------------

<Category:constantcategories> <Category:mod_map>
