import "mod_dir";
import "mod_say";

Private
    i;
    string temp;
Begin
    i=diropen("c:\*.*");
    loop
        temp=dirread(i);
        if(temp=="") break; end
        say(temp);
        frame;
    end
    dirclose(i);
End