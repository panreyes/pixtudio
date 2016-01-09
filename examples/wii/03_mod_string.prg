import "mod_say";
import "mod_string";

// Test for the asc() function
// http://wiki.bennugd.org/index.php?title=Asc
Function test_asc(string teststr)
Begin
  say("The ASCII value for '"+teststr[0]+"' is "+asc(teststr));
End;

// Test for the atof() function
// http://wiki.bennugd.org/index.php?title=Atof
Function test_atof(string teststr)
Begin
  say(teststr+" becomes "+atof(teststr)+" (this should show you the same "+
      "thing twice)");
End;

// Test for the atoi() function
// http://wiki.bennugd.org/index.php?title=Atoi
Function test_atoi(string teststr)
Begin
  say(teststr+" becomes "+atoi(teststr)+" (this should show you the same "+
      "thing twice)");
End;

// Test for the chr() function
// http://wiki.bennugd.org/index.php?title=Chr
Function test_chr(byte ascii)
Begin
  say("ASCII character "+ascii+" is really a '"+chr(ascii)+"'");
End;

// Test for the find() function
// http://wiki.bennugd.org/index.php?title=Find
Function test_find()
Private
  int pos=0;

Begin
  pos = find("Hello, World!", "World");
  if(pos != -1)
    say("Found at pos: "+pos);
  else
    say("String couldn't be found");
  end;
End;

// Test for the find() function
// http://wiki.bennugd.org/index.php?title=Find
Function test_find2()
Private
  int pos=0;

Begin
  pos = find("Hello, World!", "World", 0);
  if(pos != -1)
    say("Found at pos: "+pos);
  else
    say("String couldn't be found");
  end;
End;

// Test for the ftoa() function
// http://wiki.bennugd.org/index.php?title=Ftoa
Function test_ftoa(float testfloat)
Begin
  say(testfloat+" becomes "+ftoa(testfloat)+" (this should show you the same "+
      "thing twice)");
End;

// Test for the itoa() function
// http://wiki.bennugd.org/index.php?title=Itoa
Function test_itoa(int testint)
Begin
  say(testint+" becomes "+atoi(testint)+" (this should show you the same "+
      "thing twice)");
End;

// Test for the lcase() function
// http://wiki.bennugd.org/index.php?title=Lcase
Function test_lcase(string teststr)
Begin
  say(lcase(teststr));
End;

// Test for the len() function
// http://wiki.bennugd.org/index.php?title=Len
Function test_len(string teststr)
Begin
  say("String '"+teststr+"' is "+len(teststr)+" characters long");
End;

// Test for the lpad() function
// http://wiki.bennugd.org/index.php?title=Lpad
Function test_lpad(string teststr, int length)
Begin
  say("'"+lpad(teststr, length)+"'");
End;

// Test for the rpad() function
// http://wiki.bennugd.org/index.php?title=Rpad
Function test_rpad(string teststr, int length)
Begin
  say("'"+rpad(teststr, length)+"'");
End;

// Test for the strcasecmp() function
// http://wiki.bennugd.org/index.php?title=Rpad
Function test_strcasecmp(string str1, string str2)
Private
  int retval=0;
Begin
  retval = strcasecmp(str1, str2);
  switch(retval)
    case 0:
      say("Strings match, if case sensitivity is not considered.");
    end;
    default:
      say("Strings don't match.");
    end;
  end;
End;

// Test for the strrev() function
// http://wiki.bennugd.org/index.php?title=Strrev
Function test_strrev(string teststr)
Begin
  say(strrev(teststr));
End;

// Test for the substr() function
// http://wiki.bennugd.org/index.php?title=Substr
Function test_substr(string teststr)
Begin
  say(substr(teststr, 2, 10));
End;

// Test for the trim() function
// http://wiki.bennugd.org/index.php?title=Trim
Function test_trim(string teststr)
Begin
  say("'"+trim(teststr)+"'");
End;

// Test for the ucase() function
// http://wiki.bennugd.org/index.php?title=Ucase
Function test_ucase(string teststr)
Begin
  say(ucase(teststr));
End;

Process main()
Private
	string teststr="Hello, World!", testfloat="3.1415", testint="30";
Begin
  test_asc(teststr);
  test_atof(testfloat);
  test_atoi(testint);
  test_chr(asc(teststr));
  test_find();
  test_find2();
  test_ftoa(atof(testfloat));
  test_itoa(atoi(testint));
  test_lcase(teststr);
	test_len(teststr);
	test_lpad(teststr, testint);
	test_rpad(teststr, testint);
	test_strcasecmp(teststr, lcase(teststr));
	test_strrev(teststr);
	test_substr(teststr);
	test_trim(lpad(teststr, len(teststr)+testint));
	test_ucase(teststr);
End;
