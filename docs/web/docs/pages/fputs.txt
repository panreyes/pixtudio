Definition
----------

**INT** fputs ( &lt;**INT** filehandle&gt; , &lt;**STRING** line&gt; )

Writes a line to a certain file.

Parameters
----------

  -------------------- ------------------------------------------------------------------------------------------------
  **INT** filehandle   - The [FileHandle](FileHandle "wikilink") of the file returned by [fopen](fopen "wikilink")().
  -------------------- ------------------------------------------------------------------------------------------------

Returns
-------

**INT**: Number of bytes written.

  ------- ----------------------------
  0       - There was an error.
  &gt;0   - Number of bytes written.
  ------- ----------------------------

Notes
-----

The character '\\' will be put in front of every newline character, so
that [fgets](fgets "wikilink")() reads the lines like they were written.

<Category:functions> <Category:files> <Category:mod_file>
