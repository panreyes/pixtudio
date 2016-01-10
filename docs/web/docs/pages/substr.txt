Syntax
------

**INT** substr ( &lt;**STRING** str&gt; , &lt;**INT** startposition&gt;
, \[&lt;**INT** characters&gt;\] )

Description
-----------

Returns a subsection of a certain string.

Parameters
----------

  ------------------------ -------------------------------------------------------------------------------------------------------------------
  **STRING** str           - The string of which a subsection will be returned.
  **INT** startposition    - The position of the first character to be in the subsection.
  \[**INT** characters\]   - The number of characters the subsection will hold. Negative values are special; see [Notes](#Notes "wikilink").
  ------------------------ -------------------------------------------------------------------------------------------------------------------

Returns
-------

**STRING** : The subsection.

Notes
-----

If the number of characters is a negative value, the following applies:
the start of the subsection will be *startposition*; the end of the
subsection will be the length of the string minus the absolute value of
*characters*.

Example
-------

    Private                             
        String str = "This is my string.";
    Begin

        // No specified number of characters
        say( substr(str,2)     + "<" ); // "is is my string."
        say( substr(str,-7)    + "<" ); // "string."

        // Specified number of characters
        say( substr(str,5,2)   + "<" ); // "is"

        // Number of characters greater than length of string
        say( substr(str,2,50)  + "<" ); // "is my string."
        say( substr(str,-7,50) + "<" ); // "string."

        // Negative number of characters
        say( substr(str,5,-5)  + "<" ); // "is my st"

        // Special case
        say( substr(str,0,0)   + "<" ); // "", but pre 0.92: "This is my string."

        Repeat
            frame;
        Until(key(_ESC))

    End

Used in example: [say](say "wikilink")(), [key](key "wikilink")()

<Category:functions> <Category:strings> <Category:mod_string>
