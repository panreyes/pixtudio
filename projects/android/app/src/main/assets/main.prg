import "mod_video"
import "mod_say"
import "mod_mouse"
import "mod_proc"
import "mod_file"
import "mod_say"

Process main()
Private
    int fd;
    string line;

Begin
    fd = fopen("text.txt", O_READ);
    while(! feof(fd))
        line = fgets(fd);
        say(line);
    end;

    say("Done");

	while(! mouse.left)
		FRAME;
	end;

    fclose(fd);
	exit();
End
