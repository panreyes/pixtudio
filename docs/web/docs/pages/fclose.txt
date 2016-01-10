Definition
----------

**INT** fclose ( &lt;**INT** filehandle&gt; )

Unloads a file previously loaded with [fopen](fopen "wikilink")().

Parameters
----------

  -------------------- ------------------------------------------------------------------------------------------------
  **INT** filehandle   - The [FileHandle](FileHandle "wikilink") of the file returned by [fopen](fopen "wikilink")().
  -------------------- ------------------------------------------------------------------------------------------------

Returns
-------

**INT**: [true](true "wikilink")

Example
-------

    Process loadthing(STRING loadpath);
    Private
        int handle;   // handle for the loaded file 
        int druppels; // here's where the loaded data go
    Begin

        handle=fopen(loadpath,O_READ); // opens the file in reading mode
        fread(handle,druppels);        // reads from the file and puts the data in druppels
        fclose(handle);                // zipping up after business is done
        write(0,0,0,0,druppels);       // shows the value of druppels
    End

Used in example: [fopen](fopen "wikilink")(),
[fread](fread "wikilink")(), [write](write "wikilink")()

<Category:functions> <Category:files> <Category:mod_file>
