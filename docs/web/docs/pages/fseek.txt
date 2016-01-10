Definition
----------

**INT** fseek ( &lt;**INT** filehandle&gt; , &lt;**INT** position&gt; ,
&lt;**INT** seek\_mode&gt; )

Sets the byte offset (reading position) of a certain file. This means
where a function will start reading in that file.

Parameters
----------

  -------------------- ------------------------------------------------------------------------------------------------
  **INT** filehandle   - The [FileHandle](FileHandle "wikilink") of the file returned by [fopen](fopen "wikilink")().
  **INT** position     - Number of bytes from the point indicated by *seek\_mode*.
  **INT** seek\_mode   - Set the offset relative to a certain point (see [seek modes](seek_modes "wikilink")).
  -------------------- ------------------------------------------------------------------------------------------------

Returns
-------

**INT**: The new reading position.

<Category:functions> <Category:files> <Category:mod_file>
