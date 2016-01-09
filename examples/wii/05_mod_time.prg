#ifndef NOWII
import "mod_say";
import "mod_time";
#endif 

Process main()
Private
	int now=0;
Begin
	now = time();
	say("It's "+now+". std. UNIX time");
	say("That's around "+ftime("%d-%m-%Y %H:%M:%S", now));
	say("Gonna die now.");
	say("I've been running for "+get_timer()+"ms");
End;
