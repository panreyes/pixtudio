Syntax
------

**INT** fexists ( &lt;**STRING** filename&gt; )

Description
-----------

Checks if a certain file exists.

Also called [file\_exists](file_exists "wikilink")().

Parameters
----------

  --------------------- --------------------------------------------------------------------
  **STRING** filename   - The file to be checked for existence, including a possible path.
  --------------------- --------------------------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")/[false](false "wikilink"): the
existence of the file.

  --------------------------- -------------------------------------
  [true](true "wikilink")     - The specified file exists.
  [false](false "wikilink")   - The specified file doesn't exist.
  --------------------------- -------------------------------------

Example
-------

    import "mod_file"
    import "mod_say"

    Process Main()
    Begin

        say("> C:\Windows\notepad.exe > " + fexists("C:\Windows\notepad.exe")); // A filename with
                                                                                // absolute path
        say("> SDL.dll > " + fexists("SDL.dll")); // A filename without a path
        say("> SomeNonExistingFile > " + fexists("SomeNonExistingFile")); // A nonexisting file

    End

Used in example: [say](say "wikilink")(),
[fexists](fexists "wikilink")()

<Category:functions> <Category:files> <Category:mod_file>
