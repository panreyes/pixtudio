<category:variables> <category:predefined> [category:global
variables](category:global_variables "wikilink") [category:regular
expression](category:regular_expression "wikilink") <category:mod_regex>

[**Up to Global Variables**](Global_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**STRING\[15\]** regex\_reg

**Regex\_reg** is a [global variable](global_variable "wikilink"),
holding 16 strings. It holds matches when the functions
[Regex](Regex "wikilink")() and
[Regex\_replace](Regex_replace "wikilink")() are used.

Examples
--------

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
       
       say("regex_reg[0]="+regex_reg[0]);
       say("regex_reg[1]="+regex_reg[1]);
       say("regex_reg[2]="+regex_reg[2]);
       say("regex_reg[3]="+regex_reg[3]);
       
       say("regex_reg[4]="+regex_reg[4]);
       say("regex_reg[5]="+regex_reg[5]);
       say("regex_reg[6]="+regex_reg[6]);
       say("regex_reg[7]="+regex_reg[7]);
       
       say("regex_reg[8]="+regex_reg[8]);
       say("regex_reg[9]="+regex_reg[9]);
       say("regex_reg[10]="+regex_reg[10]);
       say("regex_reg[11]="+regex_reg[11]);
       
       say("regex_reg[12]="+regex_reg[12]);
       say("regex_reg[13]="+regex_reg[13]);
       say("regex_reg[14]="+regex_reg[14]);
       say("regex_reg[16]="+regex_reg[15]);
    END
