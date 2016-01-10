Definition
----------

**INT** save ( &lt;**STRING** filename&gt; , &lt;**VARSPACE** data&gt; )

Saves the data from the specified variable to the specified file.

Parameters
----------

  --------------------- ---------------------------------------------------------------------------------------
  **STRING** filename   - The name of the file that will be saved.
  **VARSPACE** data     - The variable (of any [datatype](datatype "wikilink")) that will be saved in a file.
  --------------------- ---------------------------------------------------------------------------------------

Returns
-------

**INT** : The number of bytes written to the file.

Notes
-----

Attempting to use "?","\*","&lt;","&gt;" or "|" in a filename will
result in no file at all on Windows, while using ":" in a filename
results in everything from the ":" and beyond being cut off from the
file name and the resulting file will be of size 0.

Using the characters "/" or "\\" in the filename (without directories
that can be accessed that way) results in everything from this character
and before being cut off from the filename. The file will be saved
successfully nonetheless.

Example
-------

    Program test;
    Global
        struct My_struct
            Level_number="99";
            string Map_name="Amazing map";
        End
    Begin
            Save("myfile.sav",My_struct); // The content of My_struct is saved in myfile.sav
            Write(0,10,10,0,"Data saved!");

        While (!key(_ESC))
            Frame;
        End
    End

Used in example: [save](save "wikilink")(), [write](write "wikilink")(),
[key](key "wikilink")()

<Category:functions> <Category:files> <Category:mod_file>
