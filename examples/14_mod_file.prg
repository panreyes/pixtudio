import "mod_file"
import "mod_say"

Process main()
Private
int correct=0;
Begin
    if(OS_ID == OS_WIN32)
        if(dirname("C:\Windows\temp\file.txt") == "C:\Windows\temp\")
            correct++;
        end
        if(basename("C:\Windows\temp\file.txt") == "file.txt")
            correct++;
        end
        if(dirname("C:\") == "C:\")
            correct++;
        else
            say("dirname: " + dirname("C:\"));
        end
        if(basename("D:\") == "D:\")
            correct++;
        else
            say("basename: " + basename("D:\"));
        end
    else
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
    end

    if(correct == 4)
        say("Dirname & basename working as expected");
    else
        say("Dirname & basename test failed");
    end
End;
