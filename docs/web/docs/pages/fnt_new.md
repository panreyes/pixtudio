Definition
----------

**INT** fnt\_new ( &lt;**INT** depth&gt; )

Creates a new [font](font "wikilink") with a certain color depth. There
exists three variants of this function:

- **INT** fnt\_new ( &lt;**INT** depth&gt; )

- **INT** fnt\_new ( &lt;**INT** charset&gt; , &lt;**INT** depth&gt; )

- **INT** fnt\_new ( &lt;**INT** file&gt; , &lt;**INT** graph&gt;,
&lt;**INT** charset&gt; , &lt;**INT** width&gt; , &lt;**INT** height&gt;
, &lt;**INT** first&gt; , &lt;**INT** last&gt; , &lt;**INT** flags&gt; )

- The first variant is a simple version wich uses the systemfont and the
[CP850 character set](http://en.wikipedia.org/wiki/Code_page_850).

- The second version allows the user to select a different characterset.

- The third function allows custom fonts to made, from bitmaps in
memory. It is similair to DIV gamestudio's font generator. In this
variant, the depth cannot be set.

The previous name [new\_fnt](new_fnt "wikilink")() is deprecated.

Parameters
----------

  ----------------- -------------------------------------------------------------------------------------------
  **INT** charset   - The color characterset of the font, CHARSET\_ISO8859 or CHARSET\_CP850.
  **INT** depth     - The color depth of the [glyphs](glyph "wikilink") of the font.
  **INT** file      - The [fileID](fileID "wikilink") of the file wich contains the bitmaps with the letters.
  **INT** graph     - The [graphID](graphID "wikilink") of the bitmap wich contains the character set.
  **INT** width     - The width of the [glyph](glyph "wikilink").
  **INT** height    - The height of the [glyph](glyph "wikilink").
  **INT** first     - The first character.
  **INT** last      - The last character.
  **INT** flags     - The kind of [glyph](glyph "wikilink") width, NFB\_VARIABLEWIDTH or NFB\_FIXEDWIDTH.
  ----------------- -------------------------------------------------------------------------------------------

Returns
-------

**INT** : [FontID](FontID "wikilink")

  -------- ----------------------------------------------------
  -1       - Error: could not create [font](font "wikilink").
  &gt;=0   - The FontID.
  -------- ----------------------------------------------------

Errors
------

  --------------------- ---------------------------------------------------------------------------
  Insufficient memory   - There is insufficient memory available. This error doesn't occur often.
  Too many fonts        - There are too many fonts loaded (255).
  --------------------- ---------------------------------------------------------------------------

Example
-------

    IMPORT "mod_video";
    IMPORT "mod_wm";
    IMPORT "mod_text";
    IMPORT "mod_map";
    IMPORT "mod_key";

    GLOBAL
       int a;
       int b;
       int c;
       
       int graph_id;
       
       int font_id1;
       int font_id2;

    PROCESS main();    
        
    BEGIN

        set_mode(640,480);
        
        graph_id=png_load("font.png");
        
        // new font, variable width
        font_id1=fnt_new(0,graph_id,CHARSET_ISO8859,16,16,0,255,NFB_VARIABLEWIDTH);
        
        write_int(font_id1,0,0,0,&a);
        write_int(font_id1,0,20,0,&b);
        write_int(font_id1,0,40,0,&c);
        write(font_id1,0,60,0,"hello world!");

        
        // new font, fixed width
        font_id2=fnt_new(0,graph_id,CHARSET_ISO8859,16,16,0,255,NFB_FIXEDWIDTH); 
        
        write_int(font_id2,0,100,0,&a);
        write_int(font_id2,0,120,0,&b);
        write_int(font_id2,0,140,0,&c);
        write(font_id2,0,160,0,"hello world!");
        
        
        
        // write texts in standard system font
        write_int(0,320,0,0,&a);
        write_int(0,320,20,0,&b);
        write_int(0,320,40,0,&c);
        write(0,320,60,0,"hello world!");

        WHILE (NOT key(_ESC) AND NOT exit_status)
        
            a++;
            b--;
            c*=2;
            
            IF (c==0) 
               c=1; 
            END
            
            FRAME;
        END
    END

Used in example: [Png\_load](Png_load "wikilink")(),
[Write](Write "wikilink")(), [Write\_int](Write_int "wikilink")()

Notes
-----

If only one argument is used, the [CP850 character
set](http://en.wikipedia.org/wiki/Code_page_850) is used. The
charactermap is a bitmap, with the characters arranged in a grid. See
[this post](http://www.bennugd.org/node/118)

<Category:functions> <Category:fonts> <Category:mod_map>
