Definition
----------

**INT** ftell ( &lt;**INT** filehandle&gt; )

Returns the current reading position of a certain file.

The reading position can be altered by [fseek](fseek "wikilink")().

Parameters
----------

  -------------------- ------------------------------------------------------------------------------------------------
  **INT** filehandle   - The [FileHandle](FileHandle "wikilink") of the file returned by [fopen](fopen "wikilink")().
  -------------------- ------------------------------------------------------------------------------------------------

Returns
-------

**INT**: The current reading position of the specified file.

<Category:functions> <Category:files> <Category:mod_file>
