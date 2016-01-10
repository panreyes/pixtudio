Definition
----------

**STRING** fgets ( &lt;**INT** filehandle&gt; )

Reads a line from a certain file and returns it. Subsequent calls will
return the next line, until the end of the file is reached.

Parameters
----------

  -------------------- ------------------------------------------------------------------------------------------------
  **INT** filehandle   - The [FileHandle](FileHandle "wikilink") of the file returned by [fopen](fopen "wikilink")().
  -------------------- ------------------------------------------------------------------------------------------------

Returns
-------

**STRING**: The line read.

Notes
-----

The returned string normally does not contain the '\\n' or '\\r','\\n'
charactersets.

When a line ends with the character '\\', the next line will be joined
with the current one, changing the '\\' character to a '\\n' character.

If you want to read multiple lines from a textfile, put this function in
a loop.

<Category:functions> <Category:files> <Category:mod_file>
