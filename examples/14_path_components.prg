import "mod_file"
import "mod_say"

Process main()
Private
int correct=0;
Begin
    if(dirname("/tmp/file.txt") == "/tmp")
        correct++;
    else
        say("FAIL: dirname('/tmp/file.txt'): " + dirname("/tmp/file.txt"));
    end
    if(basename("/tmp/file.txt") == "file.txt")
        correct++;
    else
        say("FAIL: basename('/tmp/file.txt'): " + basename("/tmp/file.txt"));
    end
    if(dirname("/") == "/")
        correct++;
    else
        say("FAIL: dirname('/'): " + dirname("/"));
    end
    if(basename("/") == "/")
        correct++;
    else
        say("FAIL: basename('/'): "+ basename("/"));
    end

    if(correct == 4)
        say("Working as expected");
    else
        say("Test failed");
    end
End;
