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
