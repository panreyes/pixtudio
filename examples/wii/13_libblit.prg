#ifndef OS_WII
import "libblit";
import "mod_say";
#endif

Process main()
Begin
    say("Should display all 1's");
    say("======================");
	say(B_ABLEND==16);
	say(B_ALPHA==8);
	say(B_HMIRROR==1);
	say(B_NOCOLORKEY==128);
	say(B_SBLEND==32);
	say(B_TRANSLUCENT==4);
	say(B_VMIRROR==2);
End;
