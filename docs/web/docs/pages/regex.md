Syntax
------

**INT** regex ( &lt;**STRING** pattern&gt; , &lt;**STRING** string&gt; )

Description
-----------

Match a regular expresion to the given string. Regular expressions are
very powerfull, and allow to do complex pattern searches in texts. You
can read about the wealth of posibilities
[here](http://en.wikipedia.org/wiki/Regular_expression). Please note
that regular expresion synthax is quite cryptic and difficult in
general. Some things can be achieved in easier way with string functions
like [Find](Find "wikilink")(), [Len](Len "wikilink")(),
[Substr](Substr "wikilink")() and [glob](glob "wikilink")(). It is
unknown to wich extend bennu supports certain expressions.

Matches are stored into the predefined global array
[Regex\_reg](Regex_reg "wikilink").

Parameters
----------

  -------------------- -------------------------------
  **STRING** pattern   - The desired search pattern.
  **STRING** string    - The string to search in.
  -------------------- -------------------------------

Returns
-------

**INT** : status/match position

  ------- ----------------------------------------------------------
  &gt;0   - The character position where the match has been found.
  -1      - There is no match found.
  ------- ----------------------------------------------------------

Example
-------

    // import modules
    IMPORT "mod_say";
    IMPORT "mod_debug";
    IMPORT "mod_regex";


    GLOBAL


       string sourcetext="It's raining cat's and dogs";
       string searchtext="cat"; // the search pattern
       
       int status;
       
    PROCESS main();

    BEGIN


       // print the joined string
       say("");
       
       // looking for the position of the word "cat"
       status=regex(searchtext,sourcetext);
       
       say("match found at: "+status);
       say("");

       // the last character of a line. 
       status=regex("$","99 bottles of beer on the wall.");
       
       say(status+" is the last character position in 99 bottles of beer on the wall.");
       say("");
    END

This program will print as result:

    match found at: 13

    31 is the last character position in 99 bottles of beer on the wall.

Used in example: [say](say "wikilink")() See also: [regular expresion
examples](http://en.wikipedia.org/wiki/Regular_expression#Examples)

<Category:functions> <Category:mod_regex>
