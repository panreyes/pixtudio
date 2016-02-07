Definition
----------

**INT** dirclose ( &lt;**INT** handleId&gt; )

Close a directory using a given handle id obtained with
[diropen](diropen "wikilink")().

Parameters
----------

  ------------------ ---------------------------------
  **INT** handleId   - The handle id of a directory.
  ------------------ ---------------------------------

Returns
-------

**INT** : The handle of the opened directory.

  --- ------------------------------------------
  0   - There was an error.
  1   - The directory was closed successfully.
  --- ------------------------------------------

<Category:functions> <Category:files> <Category:mod_dir>
