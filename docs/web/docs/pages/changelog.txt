This page is aimed to contain a gathering of all information about the
changes to [Bennu](Bennu "wikilink") in the different releases.
Information about what exactly has changed is spread out over several
sources making some new features and functions go unnoticed. These
features should be in this wiki but as the updates to this wiki are
rather sparse it's probably a good idea to have the changes made at
least somewhere written down neatly.

Information is retrieved from the Spanish and English worklog topics on
the Bennu forums, as well as from the commit messages in the SVN system.

State of this page
------------------

This page contains the information shared by
[SplinterGU](SplinterGU "wikilink") in the English worklog topic and
some information from the Spanish topic. The Spanish topic is huge
however, and contains a lot of talk between devs and users. Filtering
out the useful info will take some time. The first WIP to get it's own
changelog is WIP14, which means in the Spanish topic page 21 is the page
to start. I also have yet to create links.

Bennu's early days
------------------

On the 16th of April 2008, SplinterGU reports work has begun on Bennu:
The first big development is creating a separation between the bare
interpreter/compiler and the functionality with which they can be
extended. The core will no longer contain code that depends on
peripherals like a keyboard and mouse.

The support for Fenix' fgc, fbm and fpl file formats is also quickly
dropped in favor of good old DIVs [FPG](FPG "wikilink"),
[MAP](MAP "wikilink") and [PAL](PAL "wikilink") files. The never fully
finished support for animated graphics is also dropped as its effect is
easy to replicate in code.

The changelog starts at WIP14, this is the one where the English worklog
topic starts. In the first WIPs a lot of issues were straightened out
that arose while breaking up the big chunk of code that was Fenix into a
more elegant modular structure. Lots of general bugs were squashed and
the rendering system was fixed after not being usable in the earlier
WIPs.

WIP 14
------

Released: October 18th, 2008

*Core*

-   args fix, now argc (argument count) say count of argv... and
    argv\[0\] is dcbname in not stub version, and executable

name in stub version.

*Modules*

-   Several casts added
-   Add some includes
-   Indent
-   Some pointers size fix
-   Remove unused vars
-   Fix in use of grlib\_destroy when error creation.
-   Somes casts in palette module
-   Linux port of libvideo
-   Load map functions return 0 on fail
-   Split MAGIC used in
    [FPG](FPG "wikilink")/[MAP](MAP "wikilink")/[PAL](PAL "wikilink") to
    MAGIC of 7 bytes and 1 byte for version

WIP 15a
-------

Released: October 26th, 2008

*Core*

-   Linux Port (need tested)
-   Prohibit unload font 0
-   Fix controls points + mirrors + angle
-   Check if graph exist on gr\_save\_png
-   Fix on 32 bits collision
-   Fix on 32 bits blits

*Modules*

-   New [set\_window\_pos](set_window_pos "wikilink"),
    [get\_window\_pos](get_window_pos "wikilink") and
    [get\_window\_size](get_window_size "wikilink") functions
-   [get\_window\_size](get_window_size "wikilink") now makes a
    difference between window size and client area
-   [get\_desktop\_size](get_desktop_size "wikilink") added
-   [mod\_debug](mod_debug "wikilink") added!
-   Some [debug](mod_debug "wikilink") fixes

SVN r22
-------

Released: Februari 4th, 2009 (This was the first binary release from
SVN)

*Core*

-   Add core's functions bgdrtm\_entry and bgdrtm\_exit to bgdrtm...
-   Now exit code can be return at finish execution of bgdi

*Modules*

-   Now division by zero is allowed in float expressions, new functions
    are added:
    -   int [isinf](isinf "wikilink")(float x);
    -   int [isnan](isnan "wikilink")(float x);
    -   int [finite](finite "wikilink")(float x);
-   Ternary condition fixed... improved speed in ternary condition when
    expression is constant.
-   Lib windowmanager(WM) now doesn't exit when close button is clicked,
    only sets [exit\_status](exit_status "wikilink") to true
-   [exit](exit "wikilink")(...) functions now fixed, and use the params

SVN r28
-------

Released: March 12th, 2009

*Core*

*Modules*

-   Fixed Translucent tables in 8 bits
-   Fixed blend operations in 8 bits
-   Fixed Translucent+Blend in 8 bits

SVN r30
-------

Released: March 14th, 2009

*Core*

-   New string\_ptoa more efficient and same result in different SO.
-   Check constants already defined as variable
-   Fix variant arg for pointer vars
-   Fix unsigned comparations

*Modules*

-   32 bits drawing alpha support (alpha-pixel and drawing\_alpha)
-   speed up some drawing functions
-   [write\_var](write_var "wikilink") pointer vars support

RC? (May 11, 2009)
------------------

Released: May 11th, 2009

*Core*

-   New instances system, hash on priority, type. Speed up improved on
    iterate instances.
-   Instances now are limited to 65536 running at same time
-   Instances dirty list by change on priority is removed.
-   [Collision](Collision "wikilink"), [get\_id](get_id "wikilink"),
    [signal](signal "wikilink"),... speed up improved by use of new
    instance system and other.
-   Compiler parse number is fixed
-   Several casts are added in code
-   Several sizeof are added in code
-   libvideo now start in 32 bits as default

*Modules*

-   [get\_screen](get_screen "wikilink") now return graphic without
    control point 0, (centered)
-   speed up improved on show debug info
-   debug console parse number is fixed
-   debug console color tags fixed

RC11, r131
----------

Released: ?

*Core* ? *Modules* ?

RC18, r181
----------

Released: October 25th, 2010

*Core*

*Modules*

RC20, r?
--------

Released: ?

*Core*

-   char\[\] initialization fix
-   Full arrays copy support added
-   Better error messages
-   Multiple sources can be compiled from command line (like \#include)
-   Video blitter crash fix
-   Optimize memory used for strings in compilation
-   Fix dcb version detection
-   Several improvements in the core
-   Compilation warnings now are disabled by default
-   New lib system, now can be possible build dcl libraries.

*Modules*

-   [glyph\_set](glyph_set "wikilink") fix
-   New fonts functions, [new\_fnt](new_fnt "wikilink") or
    [fnt\_new](fnt_new "wikilink").
-   Added 1bpp png support (save/load)
-   Better debug info messages
-   Fix max sources files in debug information (before 256, now 4093)

### To be processed: mod\_debug

Debugger's new appearance(to be moved to the
[mod\_debug](mod_debug "wikilink") article):

-   New characters added to debug's system font
-   New debug's functions: breakall, breakalltypes, deleteall,
    deletealltypes, go, nextframe, nextproc.
-   Process list in brief mode
-   Process browse window, by id or by type, allowing to set/remove
    breakpoints, inspect his variables, etc...
-   Palete fix on 8 bits fpg save
-   Mirror fix on angle = 0
-   Several module's dependencies added
-   SDL\_Initializations on some modules
-   Debug info add at loading modules in runtime...
-   English messages in compiler

### To be processed: FNT\_NEW to be added

syntax:

[FNT\_NEW](FNT_NEW "wikilink") (CHARSET, DEPTH)

[FNT\_NEW](FNT_NEW "wikilink") (FILE, GRAPH, CHARSET, WITDH, HEIGHT,
FIRST, LAST, FLAGS)

where CHARSET can be:

[CHARSET\_ISO8859](CHARSET_ISO8859 "wikilink")

[CHARSET\_CP850](CHARSET_CP850 "wikilink")

where flags can be:

[NFB\_VARIABLEWIDTH](NFB_VARIABLEWIDTH "wikilink")

[NFB\_FIXEDWIDTH](NFB_FIXEDWIDTH "wikilink")

The most sexy function is the last one FNT\_NEW (FILE, GRAPH, CHARSET,
WITDH, HEIGHT, FIRST, LAST, FLAGS), this function allow us create font
from maps loaded in memory.
