// import modules
IMPORT "mod_say";
IMPORT "mod_debug";
IMPORT "mod_regex";


PROCESS regex_test()
PRIVATE
   string sourcetext="It's raining cats, cots and dogs";
   string reg="(c[a-z]t)|(dog)"; // the search pattern

   int status;
   int i=0;
BEGIN
   // print the joined string
   // the last character of a line.
   status=regex("$","99 bottles of beer on the wall.");
   say(status+" is the last character position in '99 bottles of beer on the wall'.");
   // looking for the position of the word "cat"
   status=regex(reg, sourcetext);
   say("match for '"+reg+"' in '"+sourcetext+"' found at: "+status);

   say("");
   for(i=0; i<16;i++)
      say("regex_reg["+i+"]="+regex_reg[i]);
   end
   say("");
END


PROCESS split_test()
PRIVATE
   string str = "A,B,C,D,EFG";
   string a[9];
   int n;
   int i;
BEGIN
   say("Splitting '"+ str + "' with ','");
   // Split
   n = split(",", str, &a, 10);

   // Display result
   say("Number of pieces: " + n);
   for(i=0; i<10; i++)
      say("[" + i + "] = " + a[i]);
   end
END


PROCESS regex_replace_test()
PRIVATE
    string str = "A,B,C-D,E";
BEGIN
    say(regex_replace("(B)|(-)", str, "^"));
END


PROCESS main()
BEGIN
   say("REGEX() test:");
   say("=============");
   regex_test();
   say("SPLIT() test:");
   say("=============");
   split_test();
   say("REGEX_REPLACE() test:");
   say("=====================");
   regex_replace_test();
END
