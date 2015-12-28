import "mod_file"
import "mod_say"

Process main()
Private
int correct=0;
Begin
    if(dirname("/tmp/file.txt") == "/tmp")
        correct++;
    end
    if(basename("/tmp/file.txt") == "file.txt")
        correct++;
    end
    if(dirname("/") == "/")
        correct++;
    end
    if(basename("/") == "/")
        correct++;
    end

    if(correct == 4)
        say("Working as expected");
    else
        say("Test failed");
    end
End;