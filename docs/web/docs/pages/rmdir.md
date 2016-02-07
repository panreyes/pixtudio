Definition
----------

**INT** rmdir ( &lt;**STRING** directoryname&gt; )

Removes (deletes) the directory in the current path of execution with a
certain name.

Parameters
----------

  -------------------------- ------------------------------------------------------
  **STRING** directoryname   - The name of the directory to be removed (deleted).
  -------------------------- ------------------------------------------------------

Returns
-------

**INT** : Success

  ------------------------------- -------------------------------------------------------------
  0 ([false](false "wikilink"))   - Removing the directory with the specified name failed.
  !0 ([true](true "wikilink"))    - Removing the directory with the specified name succeeded.
  ------------------------------- -------------------------------------------------------------

<Category:functions> <Category:files> <Category:mod_dir>
