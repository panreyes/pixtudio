Definition
----------

**INT** fopen ( &lt;**STRING** filename&gt; , &lt;**INT** mode&gt; )

Opens a file on the hard drive for reading or writing.

Parameters
----------

  --------------------- ------------------------------------------------------------------------------------------------
  **STRING** filename   - The filename of the file you wish to open (including extension and possible path).
  **INT** mode          - The mode with which to access the file (see [Readwrite\_modes](Readwrite_modes "wikilink")).
  --------------------- ------------------------------------------------------------------------------------------------

Returns
-------

**INT** : [FileHandle](FileHandle "wikilink")

  ---- --------------------------------------------------------------
  0    - Could not load.
  !0   - The identifier of the file now opened for reading/writing.
  ---- --------------------------------------------------------------

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

Used in example: [fread](fread "wikilink")(),
[fclose](fclose "wikilink")(), [write](write "wikilink")()

<Category:functions> <Category:files> <Category:mod_file>
