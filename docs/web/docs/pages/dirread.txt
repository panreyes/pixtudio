Definition
----------

**STRING** dirread ( &lt;**INT** handle&gt; )

Given a path with wildcards ('\*' or '?' characters), returns the first
file that matches and, in every next call, all matching files found
until no more files exists. It then returns NIL. Presumebly it's
somewhat similair to [glob](glob "wikilink"). Also you can read multiple
directories with different search criteria. This is usefull for
filemanagers and dialogboxes, when you only want to list files of a
specific type.

Parameters
----------

  ---------------- -------------------------------------------------------------------
  **INT** handle   - The id of the folder opened with [Diropen](Diropen "wikilink").
  ---------------- -------------------------------------------------------------------

Returns
-------

'''STRING ''' : The filename that matches with the wildcard search
pattern.

Example
-------

    IMPORT "mod_dir";
    IMPORT "mod_say";
    IMPORT "mod_debug";
    IMPORT "mod_key";


    GLOBAL

    int dir_id[9];

    string dir_result[9];

    string directory1="c:\windows\*.exe";
    string directory2="c:\windows\*.dll";
    string directory3="c:\windows\*.txt";

    PROCESS main();


    BEGIN

       dir_id[0]=diropen(directory1);
       dir_id[1]=diropen(directory2);
       dir_id[2]=diropen(directory3);
     
       
       /* print all exe files */
       say("");
       say("dirread test");
       say("");
       say("");
       say("the directory is: "+directory1);
       say("");
       say("reading directory.....");
       say("");  
       REPEAT
       
          IF (key(_esc))
             say("<aborted>");
             BREAK;
          END
          // read the dir
          dir_result[0]=dirread(dir_id[0]);     
          say(dir_result[0]);
              
       FRAME;
       UNTIL (dir_result[0]=="")
       
       
       
       /* print all dll files */
       say("");
       say("dirread test");
       say("");
       say("");
       say("the directory is: "+directory2);
       say("");
       say("reading directory.....");
       say("");
       REPEAT
       
          IF (key(_esc))
             say("<aborted>");
             BREAK;
          END
          // read the dir
          dir_result[1]=dirread(dir_id[1]);     
          say(dir_result[1]);
              
       FRAME;
       UNTIL (dir_result[1]=="")
       
       
       
       /* print all txt files */
       say("");
       say("dirread test");
       say("");
       say("");
       say("the directory is: "+directory3);
       say("");
       say("reading directory.....");
       say("");
       REPEAT
       
          IF (key(_esc))
             say("<aborted>");
             BREAK;
          END
          // read the dir
          dir_result[2]=dirread(dir_id[2]);     
          say(dir_result[2]);
              
       FRAME;
       UNTIL (dir_result[2]=="")
       
       
       say("closing the directory");
       dirclose(dir_id[0]);
       dirclose(dir_id[1]);
       dirclose(dir_id[2]);
      
         
    END

Used in example: [say](say "wikilink")(),
[Diropen](Diropen "wikilink")(), [Dirclose](Dirclose "wikilink")().

<Category:functions> <Category:files> <Category:mod_dir>
