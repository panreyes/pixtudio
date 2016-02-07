Definition
----------

**INT** fpg\_load ( &lt;**STRING** filename&gt;, \[&lt;**INT
POINTER**&gt; complete&gt;\] )

Loads a graphics library into your program.

This function loads the whole contents of an [FPG](FPG "wikilink")
graphics library into your project, enabling the contained
[graphics](graphics "wikilink") to be used in your program as
[process](process "wikilink")' graphs, screen backgrounds
([put\_screen](put_screen "wikilink")()) or other graphics.

The previous name [load\_fpg](load_fpg "wikilink")() is deprecated.

Parameters
----------

  ------------------------------ -------------------------------------------------------------------------------------------------------------------------------------------------------
  **STRING** filename            - The filename of the FPG that you wish to load (including extension and possible path).
  \[**INT POINTER** complete\]   - If this argument is specified the [FPG](FPG "wikilink") is loaded asynchroneous, setting **complete** to [FileID](FileID "wikilink") on completion.
  ------------------------------ -------------------------------------------------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : [graphID](graphID "wikilink")

  -------- ------------------------------------------------------------
  -2       - Waiting for the file to be loaded, see notes.
  -1       - There was an error loading the file.
  &gt;=0   - The [FileID](FileID "wikilink") assigned to the archive.
  -------- ------------------------------------------------------------

*the following applies for versions prior rc282:*

**INT** : [FileID](FileID "wikilink")

  -------- ------------------------------------------------------------
  -1       - The specified archive could not be loaded.
  &gt;=0   - The [FileID](FileID "wikilink") assigned to the archive.
  -------- ------------------------------------------------------------

Errors
------

  ------------------- ---------------------------------------------
  Archive not found   - The specified archive could not be found.
  ------------------- ---------------------------------------------

Notes
-----

Using an FPG file to contain all or some of the graphics used in a Bennu
program is convenient, but isn't always the best way to load graphics.
Other methods of loading graphics into your program include
[load\_map](load_map "wikilink")() and
[load\_png](load_png "wikilink")() which load individual graphic files.
Graphics loaded individually will be given [FileID](FileID "wikilink") 0
and a [GraphID](GraphID "wikilink") starting at 1000. This is because
mod\_map reserves room for the first FPG loaded (FPG files can contain
999 different graphics max.), sometimes referred to as the [system
file](system_file "wikilink") or [environment
file](environment_file "wikilink").

The first FPG file loaded using mod\_map returns and uses the
[FileID](FileID "wikilink") 0, which is reserved by mod\_map for use as
the [system file](system_file "wikilink"). All extra FPG files loaded
will have a different FileID, progressing from 1 upwards.

An FPG file holds all its contained graphs in memory simultaneously.
Having a lot of large graphs being read from a single FPG file at once
has been known to cause a slowdown.

Once an FPG file is no longer necessary to be held in the memory, its
memory space can be released by using the function
[unload\_fpg](unload_fpg "wikilink")(). It is not necessary to unload
files at the termination of a program, as Bennu always releases all used
memory at the end of program execution.

Notes
-----

The optional parameter **id** was introduced in version rc282 and allows
you to load resources in the background. It used with the
[Offset](Offset "wikilink") operator. See example below:

         load_fpg("archivo_gordo.fpg", &idFpg);
          while(idFpg==-2)
                say("Big File Loading ....");
                frame;
          end
          if(idFpg==-1)
              say("Something went wrong!!");
              exit(); // o return
          end

          say("Big file loaded ok!!");

          file=idFpg;

          graph = 7;

Example
-------

    Program example;
    Global
        int my_fpg;
    Begin
        my_fpg=load_fpg("test.fpg");   //Loads the FPG file into memory
        put_screen(my_fpg,1);          //Puts graphic with code 1 onto screen
        Repeat
            frame;
        Until(key(_esc))
        unload_fpg(my_fpg);
    End

Used in example: [put\_screen](put_screen "wikilink")(),
[unload\_fpg](unload_fpg "wikilink")()

<Category:functions> <Category:fpg> <Category:mod_map>
