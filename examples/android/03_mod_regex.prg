import "mod_say"
import "mod_regex"

Process Main()
Private
	string str = "A,B,C,D,E";
	string a[9];
	int n;
	int i;
Begin

	// Split
	n = split(",",str,&a,10);

	// Display result
	say("Number of pieces: " + n);
	for(i=0; i<n; i++)
		say("[" + i + "] = " + a[i]);
	end

End

