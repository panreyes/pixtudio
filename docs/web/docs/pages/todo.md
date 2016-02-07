Fixing existing pages
---------------------

Lot of things to do, but luckily they are pretty easy.

Things to be done:

-   Every reference to "Fenix" needs to be adjusted and altered
    to "Bennu".
-   Code must be adjusted to import modules.
-   Function, locals, globals, constants, etc in modules need to have
    their module navbox at the bottom of the page, like:

<!-- -->

    {{Moduledocbox
      | module = Mod_math
    }}

-   The old style using a chapter *Definition* needs to be separated in
    *Syntax* and *Description*. [Here's an
    example](http://wiki.bennugd.org/index.php?title=Map_put&diff=7711&oldid=6604)

Adding content
--------------

Don't know where to start? Checkout the [most
wanted](Special:WantedPages "wikilink") page.

The DPL part of the site will be done by the administrators of the wiki,
so don't worry about that. Just copy an existing page and use it as a
template.

List of functions known to not be completely documented
-------------------------------------------------------

Below you can find a list of undocumented/partially documented BennuGD
features as reported by forum user Kloppix. Comments in Spanish will
soon be translated into English and all of the following should be
checked.

------------------------------------------------------------------------

~~[Mod\_cd](Mod_cd "wikilink")~~ DONE

<strike>\*Globals

` STRUCT cdinfo`</strike>

------------------------------------------------------------------------

~~[Mod\_dir](Mod_dir "wikilink")~~ DONE

<strike>\*Functions:

` STRING DIRREAD(INTEGER)`</strike>

------------------------------------------------------------------------

~~[Mod\_draw](Mod_draw "wikilink")~~ DONE

<strike>\*Functions:

` INT PUT_PIXEL(INTEGER, INTEGER, INTEGER)`\
` INT GET_PIXEL(INTEGER, INTEGER)`</strike>

------------------------------------------------------------------------

~~[Mod\_effects](Mod_effects "wikilink")~~ DONE

<strike>\*Constants::

` INT GSCALE_RGB = 0`\
` INT GSCALE_R = 1`\
` INT GSCALE_G = 2`\
` INT GSCALE_B = 3`\
` INT GSCALE_RG = 4`\
` INT GSCALE_RB = 5`\
` INT GSCALE_GB = 6`\
` INT GSCALE_OFF = -1`

-   Functions:

` INT FILTER(INTEGER, INTEGER, POINTER)`</strike>

------------------------------------------------------------------------

~~[`Mod_file`](Mod_file "wikilink")~~` DONE`

~~\*Functions:~~

` `~~`UNDEFINED` `FREWIND(INTEGER)`~~\
` `~~`INT` `FILE_EXISTS(STRING)`~~\
` `~~`INT` `FREMOVE(STRING)`~~\
` `~~`INT` `FMOVE(STRING,` `STRING)`~~

------------------------------------------------------------------------

~~[`Mod_flic`](Mod_flic "wikilink")~~` DONE`

~~\*Functions:~~

` `~~`INT` `START_FLI(STRING,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `END_FLI()`~~\
` `~~`INT` `FRAME_FLI()`~~\
` `~~`INT` `RESET_FLI()`~~\
` `~~`INT` `FLI_START(STRING,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `FLI_START(STRING,` `INTEGER,` `INTEGER,` `INTEGER,`
`INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `FLI_END(INTEGER)`~~\
` `~~`INT` `FLI_FRAME(INTEGER)`~~\
` `~~`INT` `FLI_RESET(INTEGER)`~~\
` `~~`INT` `FLI_PARAMS(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER,`
`INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `FLI_MOVE(INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `FLI_ANGLE(INTEGER,` `INTEGER)`~~\
` `~~`INT` `FLI_SIZE(INTEGER,` `INTEGER)`~~\
` `~~`INT` `FLI_FLAGS(INTEGER,` `INTEGER)`~~\
` `~~`INT` `FLI_Z(INTEGER,` `INTEGER)`~~\
` `~~`INT` `FLI_GETINFO(INTEGER,` `POINTER,` `POINTER,` `POINTER,`
`POINTER,` `POINTER,` `POINTER,` `POINTER,` `POINTER,` `POINTER)`~~

------------------------------------------------------------------------

[Mod\_joy](Mod_joy "wikilink")

-   Functions:

` `~~`INT` `JOY_GETPOSITION(INTEGER)`~~\
` `~~`INT` `JOY_GETPOSITION(INTEGER,` `INTEGER)`~~\
` INT JOY_GETACCEL(POINTER, POINTER, POINTER)`\
` INT JOY_GETACCEL(INTEGER, POINTER, POINTER, POINTER)`\
` `~~`INT` `NUMBER_JOY()`~~\
` `~~`INT` `SELECT_JOY(INTEGER)`~~\
` `~~`INT` `GET_JOY_BUTTON(INTEGER)`~~\
` `~~`INT` `GET_JOY_BUTTON(INTEGER,` `INTEGER)`~~

1.  Según entendí, en la Wiki se dice que JOY\_GETBALL acepta 2 o 3
    parámetros en lugar de 3 o 4. \[\[Joy\_getball)
2.  INT JOY\_GETBALL(INTEGER, POINTER, POINTER)
3.  INT JOY\_GETBALL(INTEGER, INTEGER, POINTER, POINTER)

------------------------------------------------------------------------

~~[Mod\_m7](Mod_m7 "wikilink")~~ DONE

<strike>\*Globals:

` STRUCT m7[9]`</strike>

-   Functions:

` `~~`INT` `MODE7_START(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER,`
`INTEGER,` `INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `MODE7_START(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER,`
`INTEGER,` `INTEGER)`~~\
` `~~`INT` `MODE7_STOP(INTEGER)`~~\
` `~~`INT` `START_MODE7(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER,`
`INTEGER,` `INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `START_MODE7(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER,`
`INTEGER,` `INTEGER)`~~\
` `~~`INT` `STOP_MODE7(INTEGER)`~~

------------------------------------------------------------------------

[Mod\_map](Mod_map "wikilink")

<strike>\*Constants::

` INT G_Y_CENTER = 3`\
` INT B_CLEAR = 1`\
` INT CHARSET_ISO8859 = 0`\
` INT CHARSET_CP850 = 1`\
` INT NFB_VARIABLEWIDTH = 0`\
` INT NFB_FIXEDWIDTH = 1`</strike>

-   Functions:

` `~~`INT` `MAP_NEW(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER)`
`#Aparece` `en` `la` `Wiki` `pero` `dice` `que` `sólo` `acepta` `3`
`parámetros` `en` `lugar` `de` `3` `o` `4`
[`Map_new`](Map_new "wikilink") `#parcialmente` `hecho,` `falta`
`detallar` `flags`~~\
` `~~`INT` `MAP_DEL(INTEGER,` `INTEGER)`~~\
` `~~`POINTER` `MAP_BUFFER(INTEGER,` `INTEGER)`~~\
` `~~`INT` `FPG_LOAD(STRING,` `POINTER)` `#` `Según` `la` `WIKI`
`acepta` `sólo` `1` `parámetro`~~\
` `~~`INT` `FPG_DEL(INTEGER)`~~\
` `~~`INT` `PAL_NEW()`~~\
` `~~`INT` `PAL_DEL(INTEGER)`~~\
` `~~`INT` `PAL_UNLOAD(INTEGER)`~~\
` `~~`INT` `PAL_CLONE(INTEGER)`~~\
` `~~`INT` `PAL_REFRESH()`~~\
` `~~`INT` `PAL_REFRESH(INTEGER)`~~\
` `~~`INT` `PAL_MAP_GETID(INTEGER,` `INTEGER)`~~\
` `~~`INT` `PAL_MAP_ASSIGN(INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `PAL_MAP_REMOVE(INTEGER,` `INTEGER)`~~\
` `~~`INT` `PAL_GET(INTEGER,` `INTEGER,` `POINTER)`~~\
` `~~`INT` `PAL_GET(INTEGER,` `INTEGER,` `INTEGER,` `POINTER)`~~\
` INT PAL_SYS_SET(INTEGER)`\
` INT PAL_SYS_SET(POINTER)`\
` `~~`INT` `PAL_SET(INTEGER,` `INTEGER,` `POINTER)`~~\
` `~~`INT` `PAL_SET(INTEGER,` `INTEGER,` `INTEGER,` `POINTER)`~~\
` `~~`INT` `PAL_SAVE(STRING)`~~\
` `~~`INT` `PAL_SAVE(STRING,` `INTEGER)`~~\
` `~~`INT` `COLORS_SET(INTEGER,` `INTEGER,` `POINTER)`~~\
` `~~`INT` `COLORS_SET(INTEGER,` `INTEGER,` `INTEGER,` `POINTER)`~~\
` `~~`INT` `COLORS_GET(INTEGER,` `INTEGER,` `POINTER)`~~\
` `~~`INT` `COLORS_GET(INTEGER,` `INTEGER,` `INTEGER,` `POINTER)`~~\
` `~~`INT` `PALETTE_ROLL(INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `PALETTE_CONVERT(INTEGER,` `INTEGER,` `POINTER)`~~\
` `~~`INT` `COLOR_FIND(BYTE,` `BYTE,` `BYTE)`~~\
` `~~`INT` `RGB(BYTE,` `BYTE,` `BYTE,` `INTEGER)` `#Según` `Wiki` `sólo`
`acepta` `3` `parámetros` `en` `lugar` `de` `3` `o` `4`~~`   `\
` `~~`INT` `RGBA(BYTE,` `BYTE,` `BYTE,` `BYTE,` `INTEGER)` `#Según`
`Wiki` `sólo` `acepta` `4` `parámetros` `en` `lugar` `de` `4` `o`
`5`~~`   `\
` `~~`INT` `RGB_GET(INTEGER,` `POINTER,` `POINTER,` `POINTER,`
`INTEGER)`~~\
` `~~`INT` `RGB_GET(INTEGER,` `POINTER,` `POINTER,` `POINTER)`~~\
` `~~`INT` `RGBA_GET(INTEGER,` `POINTER,` `POINTER,` `POINTER,`
`POINTER,` `INTEGER)`~~\
` `~~`INT` `RGBA_GET(INTEGER,` `POINTER,` `POINTER,` `POINTER,`
`POINTER)`~~\
` `~~`INT` `MAP_INFO_SET(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `MAP_INFO_GET(INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `MAP_INFO(INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `GRAPHIC_SET(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `FNT_NEW(INTEGER,` `INTEGER)` `#` `Según` `la` `Wiki` `solo`
`acepta` `1` `parámetro`~~\
` `~~`INT` `FNT_NEW(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER,`
`INTEGER,` `INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `BDF_LOAD(STRING)`~~\
` `~~`INT` `PCX_LOAD(STRING)`~~\
` `~~`INT` `NEW_MAP(INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `LOAD_MAP(STRING)`~~\
` `~~`INT` `UNLOAD_MAP(INTEGER,` `INTEGER)`~~\
` `~~`INT` `SAVE_MAP(INTEGER,` `INTEGER,` `STRING)`~~\
` `~~`INT` `NEW_PAL()`~~\
` `~~`INT` `LOAD_PAL(STRING)`~~\
` `~~`INT` `UNLOAD_PAL(INTEGER)`~~\
` `~~`INT` `SAVE_PAL(STRING)`~~\
` `~~`INT` `SAVE_PAL(STRING,` `INTEGER)`~~\
` `~~`INT` `SET_COLORS(INTEGER,` `INTEGER,` `POINTER)`~~\
` `~~`INT` `SET_COLORS(INTEGER,` `INTEGER,` `INTEGER,` `POINTER)`~~\
` `~~`INT` `GET_COLORS(INTEGER,` `INTEGER,` `POINTER)`~~\
` `~~`INT` `GET_COLORS(INTEGER,` `INTEGER,` `INTEGER,` `POINTER)`~~\
` `~~`INT` `ROLL_PALETTE(INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `CONVERT_PALETTE(INTEGER,` `INTEGER,` `POINTER)`~~\
` `~~`INT` `FIND_COLOR(BYTE,` `BYTE,` `BYTE)`~~\
` `~~`INT` `GET_RGB(INTEGER,` `POINTER,` `POINTER,` `POINTER,`
`INTEGER)`~~\
` `~~`INT` `GET_RGBA(INTEGER,` `POINTER,` `POINTER,` `POINTER,`
`POINTER,` `INTEGER)`~~\
` `~~`INT` `GET_RGB(INTEGER,` `POINTER,` `POINTER,` `POINTER)`~~\
` `~~`INT` `GET_RGBA(INTEGER,` `POINTER,` `POINTER,` `POINTER,`
`POINTER)`~~\
` `~~`INT` `NEW_FPG()`~~\
` `~~`INT` `LOAD_FPG(STRING)`~~\
` `~~`INT` `LOAD_FPG(STRING,` `POINTER)`~~\
` `~~`INT` `SAVE_FPG(INTEGER,` `STRING)`~~\
` `~~`INT` `UNLOAD_FPG(INTEGER)`~~\
` `~~`INT` `GET_POINT(INTEGER,` `INTEGER,` `INTEGER,` `POINTER,`
`POINTER)`~~\
` `~~`INT` `SET_POINT(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER,`
`INTEGER)`~~\
` `~~`INT` `SET_CENTER(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `NEW_FNT(INTEGER)`~~\
` `~~`INT` `NEW_FNT(INTEGER,` `INTEGER)`~~\
` `~~`INT` `NEW_FNT(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER,`
`INTEGER,` `INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `LOAD_FNT(STRING)`~~\
` `~~`INT` `UNLOAD_FNT(INTEGER)`~~\
` `~~`INT` `SAVE_FNT(INTEGER,` `STRING)`~~\
` `~~`INT` `LOAD_BDF(STRING)`~~\
` `~~`INT` `GET_GLYPH(INTEGER,` `INTEGER)`~~` `\
` `~~`INT` `SET_GLYPH(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `LOAD_PNG(STRING)`~~\
` `~~`INT` `LOAD_PCX(STRING)`~~\
` `~~`INT` `SAVE_PNG(INTEGER,` `INTEGER,` `STRING)`~~

------------------------------------------------------------------------

MOD\_MATHI \# En la Wiki solo hay MOD\_MATH. Nada de MOD\_MATHI Las
funciones de los 2 módulos son las mismas pero trabajan con otro tipo de
variables. No se que hacer acá.

------------------------------------------------------------------------

~~[Mod\_math](Mod_math "wikilink")~~ DONE

~~\*Functions:~~

` `~~`FLOAT` `ATAN2(FLOAT,` `FLOAT)`~~\
` `~~`INT` `ISINF(FLOAT)`~~\
` `~~`INT` `ISNAN(FLOAT)`~~\
` `~~`INT` `FINITE(FLOAT)`~~\
` `~~`INT` `NEAR_ANGLE(INTEGER,` `INTEGER,` `INTEGER)`~~

------------------------------------------------------------------------

~~[Mod\_mem](Mod_mem "wikilink")~~ DONE

~~\*Functions:~~

` `~~`POINTER` `MEM_CALLOC(INTEGER,` `INTEGER)`~~\
` `~~`POINTER` `MEM_ALLOC(INTEGER)`~~\
` `~~`INT` `MEM_FREE(POINTER)`~~\
` `~~`POINTER` `MEM_REALLOC(POINTER,` `INTEGER)`~~\
` `~~`INT` `MEM_CMP(POINTER,` `POINTER,` `INTEGER)`~~\
` `~~`INT` `MEM_SET(POINTER,` `BYTE,` `INTEGER)`~~\
` `~~`INT` `MEM_SETW(POINTER,` `WORD,` `INTEGER)`~~\
` `~~`INT` `MEM_SETI(POINTER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `MEM_COPY(POINTER,` `POINTER,` `INTEGER)`~~\
` `~~`INT` `MEM_MOVE(POINTER,` `POINTER,` `INTEGER)`~~\
` `~~`INT` `MEM_AVAILABLE()`~~\
` `~~`INT` `MEM_TOTAL()`~~\
` `~~`POINTER` `CALLOC(INTEGER,` `INTEGER)`~~

------------------------------------------------------------------------

~~[Mod\_path](Mod_path "wikilink")~~ DONE

<strike>\*Functions:

` INT PATH_FIND(INTEGER, INTEGER, INTEGER, INTEGER, INTEGER, INTEGER, INTEGER)`\
` INT PATH_GETXY(POINTER, POINTER)`\
` INT PATH_WALL(INTEGER)`</strike>

------------------------------------------------------------------------

~~[Mod\_proc](Mod_proc "wikilink")~~ DONE

~~\*Constants::~~

` `~~`INT` `S_FORCE` `=` `50`~~` Internal use`\
` `~~`INT` `S_TREE` `=` `100`~~` Internal use`\
` `~~`INT` `S_KILL_TREE` `=` `100`~~\
` `~~`INT` `ALL_PROCESS` `=` `0`~~` Internal use`

~~Locals:~~ Internal use

` `<strike>`STRUCT mod_proc_reserved`

-   Functions:

` INT GET_STATUS(INTEGER)`</strike>

------------------------------------------------------------------------

~~[Mod\_regex](Mod_regex "wikilink")~~ DONE

<strike>\*Globals:

` STRING regex_reg[15];`

-   Functions:

` INT REGEX(STRING, STRING)`\
` STRING REGEX_REPLACE(STRING, STRING, STRING)`\
` STRING JOIN(STRING, POINTER, INTEGER)`</strike>

------------------------------------------------------------------------

~~[Mod\_say](Mod_say "wikilink")~~ DONE

<strike>\*Functions:

` UNDEFINED SAY_FAST(STRING)`</strike>

------------------------------------------------------------------------

~~[Mod\_screen](Mod_screen "wikilink")~~ DONE

~~\*Functions:~~

` `~~`INT` `DEFINE_REGION(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER,`
`INTEGER)`~~\
` `~~`INT` `OUT_REGION(INTEGER,` `INTEGER)`~~\
` `~~`INT` `PUT_SCREEN(INTEGER,` `INTEGER)`~~\
` `~~`INT` `CLEAR_SCREEN()`~~\
` `~~`INT` `GET_SCREEN()`~~

------------------------------------------------------------------------

~~[Mod\_scroll](Mod_scroll "wikilink")~~ DONE

~~\*Functions:~~

` `~~`INT` `SCROLL_START(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER,`
`INTEGER,` `INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `SCROLL_START(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER,`
`INTEGER,` `INTEGER)`~~\
` `~~`INT` `SCROLL_STOP(INTEGER)`~~\
` `~~`INT` `SCROLL_MOVE(INTEGER)`~~\
` `~~`INT` `START_SCROLL(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER,`
`INTEGER,` `INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `START_SCROLL(INTEGER,` `INTEGER,` `INTEGER,` `INTEGER,`
`INTEGER,` `INTEGER)`~~\
` `~~`INT` `STOP_SCROLL(INTEGER)`~~\
` `~~`INT` `MOVE_SCROLL(INTEGER)`~~

------------------------------------------------------------------------

~~[Mod\_sound](Mod_sound "wikilink")~~ DONE

~~\*Functions:~~

` `~~`INT` `SOUND_INIT()`~~\
` `~~`INT` `SOUND_CLOSE()`~~\
` `~~`INT` `STOP_SONG()`~~\
` `~~`INT` `STOP_WAV(INTEGER)`~~\
` `~~`INT` `PAUSE_WAV(INTEGER)`~~\
` `~~`INT` `RESUME_WAV(INTEGER)`~~\
` `~~`INT` `IS_PLAYING_WAV(INTEGER)`~~\
` `~~`INT` `FADE_MUSIC_IN(INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `FADE_MUSIC_OFF(INTEGER)`~~\
` `~~`INT` `SET_CHANNEL_VOLUME(INTEGER,` `INTEGER)`~~\
` `~~`INT` `RESERVE_CHANNELS(INTEGER)`~~\
` `~~`INT` `SET_PANNING(INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `SET_POSITION(INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `SET_DISTANCE(INTEGER,` `INTEGER)`~~\
` `~~`INT` `REVERSE_STEREO(INTEGER,` `INTEGER)`~~\
` `~~`INT` `PLAY_WAV(INTEGER,` `INTEGER,` `INTEGER)`~~\
` `~~`INT` `SET_MUSIC_POSITION(FLOAT)`~~

` `<strike>`# INT UNLOAD_SONG(POINTER)`\
` # INT UNLOAD_WAV(POINTER)  `\
` # Las funciones de arriba aceptan INT y POINTER, pero en la wiki sólo sale lo primero. No se si es un error o es normal puesto que no entiendo mucho de pointers`</strike>` `

------------------------------------------------------------------------

~~[Mod\_string](Mod_string "wikilink")~~ DONE

<strike>\*Functions:

` INT STRLEN(STRING)`\
` STRING FORMAT(INTEGER)`\
` STRING FORMAT(FLOAT)`\
` STRING FORMAT(FLOAT, INTEGER)`</strike>

------------------------------------------------------------------------

~~[Mod\_text](Mod_text "wikilink")~~ DONE

<strike>\*Constants::

` INT ALL_TEXT = 0`</strike>

------------------------------------------------------------------------

~~[Mod\_timers](Mod_timers "wikilink")~~ DONE

<strike>\*Globals:

` timer[9];`</strike>

------------------------------------------------------------------------

~~[Mod\_video](Mod_video "wikilink")~~ DONE

~~\*Functions:~~

` `~~`INT` `SET_MODE(INTEGER)` `#` `Segun` `la` `wiki` `acepta` `2,3`
`o` `4` `parámetros.` `pero` `no` `dice` `que` `también` `1` `sólo` `(O`
`eso` `entendí)`~~

~~\*Module Dependency:~~

` `~~`libgrbase`~~\
` `~~`libvideo`~~\
` `~~`librender`~~

------------------------------------------------------------------------

~~[Mod\_wm](Mod_wm "wikilink")~~ DONE

<strike>\*Functions:

` INT SET_WINDOW_POS(INTEGER, INTEGER)`</strike>
