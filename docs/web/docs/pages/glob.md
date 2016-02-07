Definition
----------

**STRING** glob ( &lt;**STRING** criteria&gt; )

Gets a single filename or directoryname matching the criteria. If the
same criteria is specified, it keeps returning new items on subsequent
calls until it can't find any more, in which case it returns "". When
different criteria are specified, the search is 'reset'. To reset the
search without returning an item, use `""` as criteria.

After a call to glob(), the global struct
[fileinfo](fileinfo "wikilink") is filled with information about the
last file/directory entry returned.

Parameters
----------

  --------------------- ------------------------------------------------------------------------------------
  **STRING** criteria   - The search criteria to which the returned filenames apply. `""` to reset search.
  --------------------- ------------------------------------------------------------------------------------

Returns
-------

**STRING** : Filename or directoryname

  ----- --------------------------------------------------------------------
  ""    - No (new) file/directory entries.
  !""   - The name of a file/directory entry matching the search criteria.
  ----- --------------------------------------------------------------------

Notes
-----

The search criteria can hold many criteria: the folder in which you want
to look, simple requirements for filenames, such as extensions, and
directory names. A few examples:

  ---------------------- ----------------------------------------------------------------------------------------------
  `*`                    - Returns the filename of any file/directory in the current directory.
  `*.dat`                - Returns the filename of any file/directory with extension `.dat` in the current directory.
  `MyDir/*`              - Returns the filename of any file/directory in `MyDir\` relative to the current directory.
  `C:/Program Files/*`   - Returns the filename of any file/directory in `C:\Program Files\*`.
  ---------------------- ----------------------------------------------------------------------------------------------

Example
-------

    import "mod_dir"

    Process Main()
    Private
        String filename;
    Begin

        // method one:
        Loop
            filename = Glob("levels/*.tul"); // Looks for a file in the relative folder
                                             // "levels" that has the file extension "tul".
            if(filename!="")
                load_level(filename); // load_level() would load the level file
            else
                break;
            end

        End

        //Reset search
        glob("");

        // method two:
        While( (filename = Glob("levels/*.tul")) != "" )
            load_level(filename);
        End

    End

Both methods result in the same, but the second one is less code.

<Category:functions> <Category:files> <Category:mod_dir>
