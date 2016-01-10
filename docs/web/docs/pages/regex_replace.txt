Syntax
------

**STRING** regex\_replace ( &lt;**STRING** pattern&gt; , &lt;**STRING**
string&gt; , &lt;**STRING** replacement&gt; )

Description
-----------

Match a regular expresion to the given string. For each match,
substitute it with the given replacement. \\0 - \\9 escape sequences are
accepted in the replacement. Regular expressions are very powerfull, and
allow to do complex pattern searches in texts. You can read about the
wealth of posibilities
[here](http://en.wikipedia.org/wiki/Regular_expression).

Matches are stored into the predefined global array
[Regex\_reg](Regex_reg "wikilink").

Parameters
----------

  ------------------------ -----------------------------------------------------------------------------
  **STRING** pattern       - The desired search pattern (i.e. the word or pattern that should change).
  **STRING** string        - The string with the replacement pattern.
  **STRING** replacement   - The replacement string (this is the source string), see example
  ------------------------ -----------------------------------------------------------------------------

Returns
-------

**STRING** : the resulting replacement string.

Example
-------

    // import modules
    IMPORT "mod_say";
    IMPORT "mod_debug";
    IMPORT "mod_regex";


    GLOBAL


       string sourcetext="It's raining cat's and dogs."; // the orginal sentence
       string searchtext="cat";                          // the search string
       string replacetext="bird";                        // the replacement string
       
       string replace_result;
       
       int result;
       
       
    PROCESS main();

    BEGIN


       // first, look for "cat".
       result=regex(searchtext,sourcetext);
       say("");
       say(searchtext+" found at position: "+result);

       
       say("");
       say("orginal text: "+sourcetext);
     
       // replace "cat" with "bird".
       replace_result=regex_replace(searchtext,replacetext,sourcetext);
       say("");
       say("replace_result: "+replace_result);
       
       
    END

This program will print as result:

    cat found at position: 13

    orginal text: It's raining cat's and dogs.


    replace_result: It's raining bird's and dogs

In this example one word was replaced, but it's possible to do more
advanced matching patterns, similair to what most text editors do.

Used in example: [regex](regex "wikilink")(), [say](say "wikilink")()
See also: [regular expresion
examples](http://en.wikipedia.org/wiki/Regular_expression#Examples)

<Category:functions> <Category:mod_regex>
