Description
-----------

A **FileHandle** is an identifier for a file, for use in functions
requiring a FileHandle, like [fread](fread "wikilink")(),
[fwrite](fwrite "wikilink")() and [fclose](fclose "wikilink")().

Consider the following code:

    handle = fopen("file.txt",O_READ);

The [fopen](fopen "wikilink")() function will try to open the "file.txt"
for reading. If it fails to open the file for whatever reason (e.g. file
not found or insufficient user rights) `handle` will have the value of
0. If opening the file for reading succeeded, the `handle` will have a
value other than 0. What the value will be depends on the OS and runtime
circumstances. It represents an OS internal pointer to the actual file.

The file will remain open for reading, until it is closed using
[fclose](fclose "wikilink")():

    fclose(handle);

This is important, because else the operating system and other programs
think you are still using it and this can result in them not being able
to open the file.

Example
-------

So always check if a file has been successfully opened and close the
file when you are done with it.

    import "mod_file"
    import "mod_say"

    Process Main()
    Private
        int handle;   // handle for the loaded file
        string first_line; // here's where the first line of the file will go
    Begin

        // Open the file "file.txt"
        handle = fopen( "file.txt",O_READ);

        if (handle == 0)
            say( "Could not open file" );
            return;
        end

        // Read the first line form the file
        first_line = fgets(handle);

        // Output the read line
        say( "Read from file:" );
        say('"' + first_line + '"');

        // Close the file (important!)
        fclose(handle);

    End

Used in example: [fopen](fopen "wikilink")(), [say](say "wikilink")(),
[fgets](fgets "wikilink")(), [fclose](fclose "wikilink")()

<Category:general> <Category:mod_file>
