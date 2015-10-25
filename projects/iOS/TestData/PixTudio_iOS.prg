import "mod_video"
import "mod_say"
import "mod_mouse"
import "mod_proc"
import "mod_file"
import "mod_say"
import "mod_map"
import "mod_text"

Process main()
Private
    int font;
    int fd;
    string line;

Begin
    fd = fopen("text.txt", O_READ);
    while(! feof(fd))
        line = fgets(fd);
        say(line);
    end;
    fclose(fd);

    say("Done");

    font = fnt_load("font.fnt");
    say(font);
    write(font, 0, 0, 0, "PixTudio in iOS!");

	while(! mouse.left)
		FRAME;
	end;

    fnt_unload(font);

	exit();
End