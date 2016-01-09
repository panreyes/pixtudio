import "mod_sys"

Process Main()
Private
    string arg;
Begin
    arg = "file.txt";
    exec(_P_NOWAIT,"cat", 1, &arg);
End
