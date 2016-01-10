Definition
----------

**INT** find ( &lt;**STRING** str&gt; , &lt;**STRING** searchstring&gt;
, \[&lt;**INT** startposition&gt;\] )

Returns the position of the firstly found appearance of a *searchstring*
in *str* or -1 if not found. The starting position can be specified
optionally.

Parameters
----------

  --------------------------- -----------------------------------------------------------
  **STRING** str              - The string in which to search.
  **STRING** searchstring     - The string to search for.
  \[**INT** startposition\]   - The position at which to start searching. Default is 0.
  --------------------------- -----------------------------------------------------------

Returns
-------

**INT** : The position of the firstly found appearance of *searchstring*
in *str* or -1 if not found.

Example
-------

In this example there's a very long string in wich we're going to look
for 10 strings. Some of these are found (when the result is &gt; -1),
and others are deliberately bogus to show how you can detect if a string
is not found. What you'll see, is that when you specify a start position
greater then 0, and the word exists but your start position is behind
the actual position of the first character of the word you're looking
for, the function returns -1 (no match). If you specify 0 (the start of
the string), you'll be safe, because it will return the fist occurance
of the word or character when it exists in the string.

As you can see, the working of the find function works very similarly to
the find and search/replace function that you get in most text editors.


    #IFdef __VERSION__
    IMPORT "mod_video";
    IMPORT "mod_text";
    IMPORT "mod_say";
    IMPORT "mod_key";
    IMPORT "mod_string";
    IMPORT "mod_proc";
    IMPORT "mod_map";
    IMPORT "mod_draw";
    IMPORT "mod_debug";
    IMPORT "mod_sys";
    IMPORT "mod_wm";
    #ENDIF


    GLOBAL

    /* this is the big string in wich we're going to try the find() function on with a couple of tests. */
    string string_to_find_in = "hello, world! this is a very long string in wich the 'find' function must find another string. let's try a few things.";

    /* these are the strings we're going to test. */
    string search_string0 = "wich";
    string search_string1 = "wich";
    string search_string2 = ".";
    string search_string3 = "str";
    string search_string4 = "hello";
    string search_string5 = "find";
    string search_string6 = "i don't exist in the string";
    string search_string7 = "me neither";
    string search_string8 = "must";
    string search_string9 = "a";

    /* return values for the tests. a return value of "-1" means that the string could not be found. */
    int find_result0;
    int find_result1;
    int find_result2;
    int find_result3;
    int find_result4;
    int find_result5;
    int find_result6;
    int find_result7;
    int find_result8;
    int find_result9;

    /* we store the find positions here. */
    int find_pos0;
    int find_pos1;
    int find_pos2;
    int find_pos3;
    int find_pos4;
    int find_pos5;
    int find_pos6;
    int find_pos7;
    int find_pos8;
    int find_pos9;


    PRIVATE


    PROCESS main ();

    PRIVATE

    BEGIN

       /* experiment with these to try different results. */
       find_pos0 = 0;
       find_pos1 = 45;
       find_pos2 = 118;
       find_pos3 = 0;
       find_pos4 = 0;
       find_pos5 = 70;
       find_pos6 = 0;
       find_pos7 = 0;
       find_pos8 = 94;
       find_pos9 = 94;
     

       /* INT find ( <STRING str> , <STRING searchstring> , [<INT startposition>] ); */

       find_result0 = find (string_to_find_in, search_string0, find_pos0); /* search_string0 = "wich"; */
       
       find_result1 = find (string_to_find_in, search_string1, find_pos1); /* search_string1 = "wich"; */
       
       find_result2 = find (string_to_find_in, search_string2, find_pos2); /* search_string2 = "."; */
       
       find_result3 = find (string_to_find_in, search_string3, find_pos3); /* search_string3 = "str"; */
       
       find_result4 = find (string_to_find_in, search_string4, find_pos4); /* search_string4 = "hello"; */
      
       find_result5 = find (string_to_find_in, search_string5, find_pos5); /* search_string5 = "find"; */
       
       find_result6 = find (string_to_find_in, search_string6, find_pos6); /* search_string6 = "i don't exist in the string"; */
       
       find_result7 = find (string_to_find_in, search_string7, find_pos7); /* search_string7 = "me neither"; */
      
       find_result8 = find (string_to_find_in, search_string8, find_pos8); /* search_string8 = "must"; */
       
       find_result9 = find (string_to_find_in, search_string9, find_pos9); /* search_string9 = "a"; */
       
       
       
       /* 
                 "hello, world! this is a very long string in wich the 'find' function must find another string. let's try a few things.";            
                  |                                                                                                                    |
         char pos:0                                                                                                                    118
       */
       
       
       /* display the results in the console. */
       say("");
       say("looking for: '"+search_string0+"'");
       say ("search_string0 result: "+find_result0);
       IF (find_result0 == -1)
          say ("no match for: '"+search_string0+"' at the indicated position: "+find_pos0);
       ELSE
          say ("'"+search_string0+"'"+" found at position: "+find_result0);
       END
       
       say("");
       say("looking for: '"+search_string1+"'");
       say ("search_string1 result: "+find_result1);
       IF (find_result1 == -1)
          say ("no match for: '"+search_string1+"' at the indicated position: "+find_pos1);
       ELSE
          say ("'"+search_string1+"'"+" found at position: "+find_result1);
       END
       
       say("");
       say("looking for: '"+search_string2+"'");
       say ("search_string2 result: "+find_result2);
       IF (find_result2 == -1)
          say ("no match for: '"+search_string2+"' at the indicated position: "+find_pos2);
       ELSE
          say ("'"+search_string2+"'"+" found at position: "+find_result2);
       END
       
       say("");
       say("looking for: '"+search_string3+"'");
       say ("search_string3 result: "+find_result3);
       IF (find_result3 == -1)
          say ("no match for: '"+search_string3+"' at the indicated position: "+find_pos3);
       ELSE
          say ("'"+search_string3+"'"+" found at position: "+find_result3);
       END
       
       say("");
       say("looking for: '"+search_string4+"'");
       say ("search_string4 result: "+find_result4);
       IF (find_result4 == -1)
          say ("no match for: '"+search_string4+"' at the indicated position: "+find_pos4);
       ELSE
          say ("'"+search_string4+"'"+" found at position: "+find_result4);
       END
       
       say("");
       say("looking for: '"+search_string5+"'");
       say ("search_string5 result: "+find_result5);
       IF (find_result5 == -1)
          say ("no match for: '"+search_string5+"' at the indicated position: "+find_pos5);
       ELSE
          say ("'"+search_string5+"'"+" found at position: "+find_result5);
       END
       
       say("");
       say("looking for: '"+search_string6+"'");
       say ("search_string6 result: "+find_result6);
       IF (find_result6 == -1)
          say ("no match for: '"+search_string6+"' at the indicated position: "+find_pos6);
       ELSE
          say ("'"+search_string6+"'"+" found at position: "+find_result6);
       END
       
       say("");
       say("looking for: '"+search_string7+"'");
       say ("search_string7 result: "+find_result7);
       IF (find_result7 == -1)
          say ("no match for: '"+search_string7+"' at the indicated position: "+find_pos7);
       ELSE
          say ("'"+search_string7+"'"+" found at position: "+find_result7);
       END
       
       say("");
       say("looking for: '"+search_string8+"'");
       say ("search_string8 result: "+find_result8);
       IF (find_result8 == -1)
          say ("no match for: '"+search_string8+"' at the indicated position: "+find_pos8);
       ELSE
          say ("'"+search_string8+"'"+" found at position: "+find_result8);
       END
       
       say("");
       say("looking for: '"+search_string9+"'");
       say ("search_string9 result: "+find_result9);
       IF (find_result9 == -1)
          say ("no match for: '"+search_string9+"' at the indicated position: "+find_pos9);
       ELSE
          say ("'"+search_string9+"'"+" found at position: "+find_result9);
       END
          
    END

Notes
-----

A first character of a string is at position 0.

<Category:functions> <Category:strings> <Category:mod_string>
