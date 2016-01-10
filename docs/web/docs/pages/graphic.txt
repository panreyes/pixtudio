Definition
----------

A graphic (graph or map) is a bitmap with certain properties, like
width, height, depth and of course the pixel data. It is used to give
the program a graphical look. One can load graphics from files with for
example [load\_png](load_png "wikilink")() or use
[Image.DLL](Image.DLL "wikilink"). They can also be obtained from within
[FPG](FPG "wikilink")'s or [FGC](FGC "wikilink")'s files, which are
graphic collection files. To create one on the fly, the function
[new\_map](new_map "wikilink")() can be used.
[Here](:Category:maps "wikilink")'s a list of functions related to
graphics and maps.

Displaying a Graphic
--------------------

To display a graphic on the screen, there are two main ways of doing
this:

-   Using drawing operations listed [here](:Category:maps "wikilink").
-   Using [processes](process "wikilink") and assigning graphics to
    their graph variable.

Combinations can also be used naturally.

### Drawing Operations

Graphics can be drawn onto each other, by the use of various [map
functions](:Category:maps "wikilink"). The functions use
[blitting](blit "wikilink") as the method for drawing, which is a
reasonably fast way, as Bennu makes use of MMX capabilities. A function
like [put](put "wikilink")() will draw a picture on the background,
displaying it on the screen (if [restore\_type](restore_type "wikilink")
is not [NO\_RESTORE](NO_RESTORE "wikilink")).

### Process Graphs

Graphics can be assigned to processes, which also have coordinate and
transformation data. This is done by the use of the [local
variables](local_variables "wikilink") [graph](graph "wikilink"), which
holds the [GraphID](GraphID "wikilink") of a graph. The graphic is
displayed, according to a few local variables influencing the graphic,
like [x](x "wikilink"), [y](y "wikilink"), [z](z "wikilink"),
[angle](angle "wikilink"), etc.

<Category:general>
