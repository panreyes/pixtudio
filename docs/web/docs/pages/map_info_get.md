Definition
----------

**INT** map\_info\_get ( &lt;**INT** fileID&gt; , &lt;**INT**
graphID&gt; , &lt;**INT** infotype&gt; )

Gets some information about the [graph](graph "wikilink") specified.
This function is also known as
[Graphic\_info](Graphic_info "wikilink")() and
[Map\_info](Map_info "wikilink")().

Parameters
----------

  ------------------ ------------------------------------------------------------------------
  **INT** fileID     - The [file](file "wikilink") that holds the graph.
  **INT** graphID    - The [graph](graph "wikilink") to get information from.
  **INT** infotype   - What [type of information](graphical_infotypes "wikilink") you want.
  ------------------ ------------------------------------------------------------------------

Returns
-------

**INT** : Returns the information you want.\
If the specified graph was invalid it returns 0.\
If the specified infotype was not recognized it returns 1.

Example
-------

See [Graphic\_info](Graphic_info "wikilink")() for example.

<Category:functions> <Category:maps> <Category:mod_map>
