import "mod_say"
import "mod_map"
import "mod_rand"

Local
byte var;
End;

Process robot(var)
Begin
    say("VAR: "+var);
End;

Process main()
Begin
    robot(rand(0, 10));
    robot(rand(0, 10));
    robot(rand(0, 10));
    robot(rand(0, 10));
End;
