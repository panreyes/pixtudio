// import modules
IMPORT "mod_say";
IMPORT "mod_debug";
IMPORT "mod_regex";


PROCESS regex_test()
PRIVATE
   string sourcetext="It's raining cat's and dogs";
   string searchtext="cat"; // the search pattern

   int status;
BEGIN
   // print the joined string
   // looking for the position of the word "cat"
   status=regex(searchtext,sourcetext);

   say("match found at: "+status);
   say("");

   // the last character of a line.
   status=regex("$","99 bottles of beer on the wall.");

   say(status+" is the last character position in 99 bottles of beer on the wall.");
   say("");
END


PROCESS split_test()
PRIVATE
   string str = "A,B,C,D,E";
   string a[3];
   int n;
   int i;
BEGIN
   say("Splitting '"+ str + "' with ','");
   // Split
   n = split(",",str,&a,10);

   // Display result
   say("Number of pieces: " + n);
   for(i=0; i<3; i++)
      say("[" + i + "] = " + a[i]);
   end
END


PROCESS main()
BEGIN
   say("REGEX() test:");
   say("=============");
   regex_test();
   say("SPLIT() test:");
   say("=============");
   split_test();
END
