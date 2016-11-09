import "mod_steam"
import "mod_text"
import "mod_video"
import "mod_key"
import "mod_map"

Process main()
Private
	int font;
	string steam_name;
Begin
	steam_init(480);
	font = ttf_load("ttf/DejaVuSans.ttf");
	ttf_set_size(font, 30);
	set_mode(800, 600);
	steam_name = steam_username();
	write(font, 400, 280, 4, "Your steam username is: "+steam_name);
	write(font, 400, 320, 4, "Press esc to quit");
	while(!key(_esc))
		Frame;
	End

	steam_close();
End