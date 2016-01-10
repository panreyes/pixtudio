Definition
----------

**INT** load ( &lt;**STRING** filename&gt; , &lt;**VARSPACE** data&gt; )

Loads the data read from the specified file into the specified variable.

Parameters
----------

  --------------------- --------------------------------------------------------------------------------------------------------------
  **STRING** filename   - The name of the file to be loaded.
  **VARSPACE** data     - The variable (of any [datatype](datatype "wikilink")) in which the data read from the file will be loaded.
  --------------------- --------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : The number of bytes read from the file.

Notes
-----

To check whether a file exists before it is loaded,
[file\_exists](file_exists "wikilink")() can be used.

Example
-------

    Program test;
    Global
        struct My_struct
            Level_number;
            string Map_name;
        End
    Begin
        If (file_exists("myfile.sav")) 
            Load("myfile.sav",My_struct);            // Content from myfile.sav is loaded into My_struct
            Write(0,10,10,0,My_struct.level_number); // A variable from the loaded struct is shown on screen
            Write(0,10,20,0,My_struct.map_name);     // Another variable loaded is shown on screen
        Else
            Write(0,10,10,0,"File couldn't be loaded, it doesn't exist.");
        End

        While (!key(_esc))
            Frame;
        End
    End

Used in example: [file\_exists](file_exists "wikilink")(),
[load](load "wikilink")(), [write](write "wikilink")(),
[key](key "wikilink")()

<Category:functions> <Category:files> <Category:mod_file>
