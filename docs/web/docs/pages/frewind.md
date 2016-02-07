Definition
----------

**UNDEFINED** frewind ( &lt;**INT** filehandle&gt; )

Sets the byte offset (reading position) to the begin of a certain file.
This is similair to using:

    fseek(file_id,0,SEEK_SET);

Parameters
----------

  -------------------- ------------------------------------------------------------------------------------------------
  **INT** filehandle   - The [FileHandle](FileHandle "wikilink") of the file returned by [fopen](fopen "wikilink")().
  -------------------- ------------------------------------------------------------------------------------------------

Returns
-------

**INT**

  --- -----------------------------------
  1   - The begin position of the file.
  --- -----------------------------------

See also
--------

[fseek](fseek "wikilink")()

<Category:functions> <Category:files> <Category:mod_file>
