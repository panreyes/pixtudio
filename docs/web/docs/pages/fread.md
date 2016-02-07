Definition
----------

**INT** fread ( &lt;**INT** filehandle&gt; , &lt;**VARIABLE** data&gt; )

**INT** fread ( &lt;**VOID POINTER** data\_pos&gt; , &lt;**INT**
length&gt; , &lt;**INT** filehandle&gt; )

Reads the information from a file loaded with
[fopen](fopen "wikilink")() to the variable *data*.

The second version reads *length* bytes to the memory pointed to by
*data\_pos*.

Parameters
----------

  ---------------------------- ------------------------------------------------------------------------------------------------
  **INT** filehandle           - The [FileHandle](FileHandle "wikilink") of the file returned by [fopen](fopen "wikilink")().
  **VARIABLE** data            - The data to read from the file (any type of variable). It will be loaded into this variable.
  **VOID POINTER** data\_pos   - The pointer to which the bytes read will be written to.
  **INT** length               - The number of bytes to read from the specified file.
  ---------------------------- ------------------------------------------------------------------------------------------------

Returns
-------

**INT** : The number of bytes read from the file.

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
[fclose](fclose "wikilink")(), [write](write "wikilink")()

<Category:functions> <Category:files> <Category:mod_file>
