Definition
----------

**INT** mkdir ( &lt;**STRING** directoryname&gt; )

Creates a new directory in the current path of execution with a certain
name.

Parameters
----------

  -------------------------- --------------------------------------------
  **STRING** directoryname   - The name of the directory to be created.
  -------------------------- --------------------------------------------

Returns
-------

**INT** : Success

  ------------------------------- ---------------------------------------------------------------
  0 ([false](false "wikilink"))   - Creating a new directory with the specified name failed.
  !0 ([true](true "wikilink"))    - Creating a new directory with the specified name succeeded.
  ------------------------------- ---------------------------------------------------------------

<Category:functions> <Category:files> <Category:mod_dir>
