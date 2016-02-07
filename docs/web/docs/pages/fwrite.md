Definition
----------

**INT** fwrite ( &lt;**INT** filehandle&gt; , &lt;**VARIABLE** data&gt;
)

**INT** fwrite ( &lt;**VOID POINTER** data\_pos&gt; , &lt;**INT**
length&gt; , &lt;**INT** filehandle&gt;)

Writes the variable *data* to a file loaded with
[fopen](fopen "wikilink").

*to be extended...*

Parameters
----------

  -------------------- -----------------------------------------------------------------
  **INT** filehandle   - Identifier of the file loaded with [fopen](fopen "wikilink").
  **VARIABLE** data    - The data to write to the file (any type of variable).
  -------------------- -----------------------------------------------------------------

Returns
-------

**INT** : The number of bytes written to the file.

Example
-------

    Process writething(STRING loadpath);
    Private
        handle;   // handle for the loaded file 
        druppels; // the data to write to the file

    Begin

        druppels=rand(1,10);

        handle=fopen(loadpath,O_WRITE); // opens the file in writing mode
        fwrite(handle,druppels);        // writes the druppels variable to the file
        fclose(handle);                 // zipping up after business is done

    End

Used in example: [fopen](fopen "wikilink")(),
[fclose](fclose "wikilink")(), [rand](rand "wikilink")()

<Category:functions> <Category:files> <Category:mod_file>
