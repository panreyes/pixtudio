Syntax
------

'''INT ''' path\_wall ( &lt;**INT** wall\_color&gt; )

Description
-----------

This function changes the wall color. Normally,
[Path\_find](Path_find "wikilink")() only uses two colors, i.e. black
and white. By using this function before making a call to Path\_find,
Path\_find will use the color indiated by this function instead. The
color may **not** be a **zero**, bcause that is usually black. ''For
more information, see the
[http://bennugd.svn.sourceforge.net/viewvc/bennugd/modules/mod\_path/mod\_path.c?revision=277&view=markup
bennu mod\_path.c
sourcecode](http://bennugd.svn.sourceforge.net/viewvc/bennugd/modules/mod_path/mod_path.c?revision=277&view=markup_bennu_mod_path.c_sourcecode "wikilink").
''

Parameters
----------

  --------------- ----------------------
  **INT** Color   - The palette color.
  --------------- ----------------------

Returns
-------

**INT** : - The color value.

<Category:functions> <Category:Pathfind> <Category:mod_path>
