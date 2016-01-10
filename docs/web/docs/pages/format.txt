Definition
----------

**STRING** format ( &lt;**INT** number&gt; )

**STRING** format ( &lt;**FLOAT** number&gt; )

**STRING** format ( &lt;**FLOAT** number&gt;, &lt;**INT** number&gt;)

Formats nummerical data for use in a [string](string "wikilink"). There
are three variants of this function, the first one only formats
integers, the second one a floating point number, and the third one uses
a fixed number of decimals, as given with the second parameter.

Parameters
----------

  ------------- -------------------------
  **INT** str   - The number to format.
  ------------- -------------------------

  --------------- ---------------------------------
  **FLOAT** str   - The decimal number to format.
  --------------- ---------------------------------

Returns
-------

**STRING** : The string with the fomatted number.

Example
-------

    // import modules
    IMPORT "mod_say";
    IMPORT "mod_debug";
    IMPORT "mod_string";


    GLOBAL

    int count=400000;
    float count2=2.50000;
    float count3=456.0000;

    PROCESS main();
      
    BEGIN

       say("format test.");
       say("");
       say("");
       say(format(count));
       say(format(count2));
       say(format(count3));
       
       say(format(count2,0));
       say(format(count2,1));
       say(format(count2,2));
       say(format(count2,3));
       
       say(format(count3,0));
       say(format(count3,1));
       say(format(count3,2));
       say(format(count3,3));
    END

The program outputs this list:

    400,000
    2.500000
    456.000000
    3
    2.5
    2.50
    2.500
    456
    456.0
    456.00
    456.000

Notes
-----

The format function seems to like US number formats, even on a european
machine.

<Category:functions> <Category:strings> <Category:mod_string>
