import "mod_file"
import "mod_say"
import "mod_proc"

Process main()
Private
    int fd=0;
    string line;

Begin
    fd = fopen("output.txt", O_WRITE);
    if(fd > 0)
        fputs(fd, "Uncompressed writing");
        fclose(fd);
    else
        say("Could not write to uncompressed file");
        exit(1);
    end

    fd = fopen("output.txt", O_READWRITE);
    if(fd > 0)
        line = fgets(fd);
        if(line != "Uncompressed writing")
            say("Could not read from uncrompressed file");
            exit(2);
        end
        fputs(fd, "Uncompressed writing, line 2");
        fclose(fd);
    else
        say("Could not write a second line to uncompressed file");
        exit(3);
    end

    fd = fopen("output.txt.gz", O_ZWRITE);
    if(fd > 0)
        fputs(fd, "Compressed writing");
        fclose(fd);
    else
        say("Could not write to compressed file");
        exit(4);
    end

    fd = fopen("output.txt.gz", O_ZREAD);
    if(fd > 0)
        line = fgets(fd);
        if(line != "Compressed writing")
            say("Could not read from crompressed file");
            exit(5);
        end
        fclose(fd);
    end

    return 0;
End
