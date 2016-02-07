[**Up to Modules**](Modules "wikilink")

------------------------------------------------------------------------

Pango.dll is a [Pango](http://www.pango.org) wrapper for BennuGD.

Description
-----------

Pango is a [Pango](http://www.pango.org) wrapper for BennuGD. It can
render complex text with HTML-like markup and UTF-8 encoded text in most
alphabets through [SDL\_Pango](http://sdlpango.sourceforge.net).

The library works well in both 16 and 32 bit color modes.

On 16 bit color mode, the background color must be manually specified or
otherwise, a solid color rectangle will be returned.

How to use
----------

To be able to use it, you must import the module, like any other:

    import "pango"

There is only one function you can use:
[pango\_render](pango_render "wikilink")(). With this, you can create
pango graphics.

Download
--------

-   [Pango (win32, mingw)](Media:Pango-mingw-win32.zip "wikilink")
    (Source & example included)
-   [Pango (linux)](Media:Pango.zip "wikilink") (Source &
    example included)

<Category:modules> [Category:3rd party](Category:3rd_party "wikilink")
<Category:pangodll>