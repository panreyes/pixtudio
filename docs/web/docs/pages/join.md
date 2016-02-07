Syntax
------

**STRING** join ( &lt;**STRING** separator&gt; , &lt;**POINTER**
array&gt; , &lt;**INT** array\_size&gt; )

Description
-----------

Joins an array of strings, given a separator. Returns the resulting
string. The function is the opposite of [Split](Split "wikilink")(). It
is usefull for generating [comma seperated value
lists](http://en.wikipedia.org/wiki/Comma-separated_values), i.e. for
use in spreadsheets or text based file formats.

The function concatinates individual strings from an array, and adds a
separator between them, the first piece will be copied from
*array*\[0\], the second from *array*\[1\], and so forth, until either
there are no more pieces left or *max\_number* pieces are copied from
the array.

Parameters
----------

  ---------------------- --------------------------------------------------------------------------------------
  **STRING** separator   - The regular expression used as separator, i.e. comma's, spaces, semi columns, etc.
  **POINTER** array      - Pointer to the string array where the strings are stored that are to be joined.
  **INT** array\_size    - The length of the array.
  ---------------------- --------------------------------------------------------------------------------------

Returns
-------

**STRING** : The resulting (concatinated) string.

Example
-------

    // import modules
    IMPORT "mod_say";
    IMPORT "mod_debug";
    IMPORT "mod_regex";


    GLOBAL


       string separator=","; // the separator character
       string csv_list[9];   // array with 10 strings

    PROCESS main();

    BEGIN


       // fill the array with words, that will become an comma seperated list
       // this is could for instance be data for a some spreadsheet file
       csv_list[0]="A";
       csv_list[1]="300";
       csv_list[2]="100";
       csv_list[3]="B";
       csv_list[4]="255";
       csv_list[5]="30";
       csv_list[6]="C";
       csv_list[7]="1000";
       csv_list[8]="10";
       csv_list[9]="<END_DATA>";


       // print the joined string
       say("");
       say(join(separator,&csv_list, 10));
       say("");

    END

This program will print as result:

    A,300,100,B,255,30,C,1000,10,<END_DATA>

Used in example: [say](say "wikilink")() See also:
[split](split "wikilink")()

<Category:functions> <Category:mod_regex>
