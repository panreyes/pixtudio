Definition
----------

**INT** Graphic\_set ( &lt;**INT** fileID&gt; , &lt;**INT** graphID&gt;
, &lt;**INT** info\_type&gt; , &lt;**INT** value&gt; )

Changes the x or y coordinate of the center pixel (controlpoint 0). This
function is also known as [Map\_info\_set](Map_info_set "wikilink")().

Parameters
----------

  -------------------- --------------------------------------------------------------------------------------------
  **INT** fileID       - The [file](file "wikilink") that holds the graph.
  **INT** graphID      - The [graph](graph "wikilink") to get information from.
  **INT** info\_type   - What [type of information](Graphical_infotypes "wikilink") you want to change, see note.
  **INT** value        - The new x or y coordinate of the center pixel.
  -------------------- --------------------------------------------------------------------------------------------

Returns
-------

**INT** : Returns the information you want.\
If the specified graph was invalid it returns 0.\
If the specified infotype was not recognized it returns 1.

Notes
-----

As infotype, only two options are valid:

  ------------------ ------------------------------------------------
  **G\_X\_CENTER**   - Change the x coordinate of the center pixel.
  **G\_Y\_CENTER**   - Change the y coordinate of the center pixel.
  ------------------ ------------------------------------------------

<Category:functions> <Category:maps> <Category:mod_map>
