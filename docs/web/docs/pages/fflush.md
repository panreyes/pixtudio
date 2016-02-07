Definition
----------

**INT** fflush ( &lt;**INT** filehandle&gt; )

Clears internal data buffers for the file associated with the
filehandle. The file has to be opened for output with the
[Readwrite\_modes](Readwrite_modes "wikilink"). This function comes from
the standard C library, this is a miscellaneous function.

Parameters
----------

  -------------------- ------------------------------------------------------------------------------------------------
  **INT** filehandle   - The [FileHandle](FileHandle "wikilink") of the file returned by [fopen](fopen "wikilink")().
  -------------------- ------------------------------------------------------------------------------------------------

Returns
-------

**INT** : - the status result of the action.

  ---------- -----------------------------------------------------------
  EOF (-1)   - an error was detected, or end of file has been reached.
  0          - normal condition, everything is fine.
  ---------- -----------------------------------------------------------

<Category:functions> <Category:files> <Category:mod_file>
