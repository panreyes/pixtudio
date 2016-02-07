Definition
----------

**INT** grayscale ( &lt;**INT** fileID&gt; , &lt;**INT** graphID&gt; ,
&lt;**BYTE** method&gt; )

This function will convert the specified [graphic](graphic "wikilink")
by using the specified method; see [notes](#Notes "wikilink") for the
details.

Parameters
----------

  ----------------- -------------------------------------------------------------------------------------------
  **INT** fileID    - The [fileID](fileID "wikilink") of the [file](file "wikilink") that holds the graphics.
  **INT** graphID   - The [graphID](graphID "wikilink") of the [graphic](graphic "wikilink") to convert.
  **BYTE** method   - The method used (see [notes](#Notes "wikilink")).
  ----------------- -------------------------------------------------------------------------------------------

Returns
-------

**INT**

  ---- --------------------
  -1   - Invalid graphic.
  1    - Success.
  ---- --------------------

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

Example
-------

    /* Example converted from bennupack, fenix test section, 2 Medium\fenix test\Fenix Test3\Test_GRAYSCALE.prg */

    // import modules
    IMPORT "mod_say";
    IMPORT "mod_debug";
    IMPORT "mod_map";
    IMPORT "mod_effects";
    IMPORT "mod_proc";
    IMPORT "mod_grproc";
    IMPORT "mod_map";
    IMPORT "mod_key";
    IMPORT "mod_video";
    IMPORT "mod_screen";


    GLOBAL

    int fpg;
    int png;



    PROCESS main();


    BEGIN
      
      scale_mode=scale_normal2x;
      set_mode(320,200,mode_16bits);
      
      fpg=load_fpg("FPG2.FPG");
      png=load_png("Triangulo_16.png");
      
      say("Grayscale test...");
      say("Press ESC to quit...");
      
      
      put_screen(fpg,1);
      
      ball(110,50,"mode 0: GSCALE_RGB",GSCALE_RGB);
      ball(160,50,"mode 1: GSCALE_R",GSCALE_R);
      ball(210,50,"mode 2: GSCALE_G",GSCALE_G);
      ball(160,100,"mode 3: GSCALE_B",GSCALE_B);
      ball(110,150,"mode 4: GSCALE_RG",GSCALE_RG);
      ball(160,150,"mode 5: GSCALE_RB",GSCALE_RB);
      ball(210,150,"mode 6: GSCALE_GB",GSCALE_GB);
      ball(260,150,"mode -1: GSCALE_OFF",GSCALE_OFF);
      
      REPEAT
        FRAME;
      UNTIL (key(_esc))
      
      let_me_alone();
      
    END


    PROCESS ball(int x,int y,string txt,int blur);

    BEGIN

      say(txt);
      graph=map_clone(0,png);
      grayscale(fpg,graph,blur);
      
      LOOP
        FRAME;
      END
    END

<Category:functions> [Category:graphical
effects](Category:graphical_effects "wikilink") <Category:mod_effects>
