import "mod_video";
import "mod_map";
import "mod_joy"
import "mod_mouse";
import "mod_say";
import "mod_screen";
import "image";

Process main()
Begin
	set_mode(640, 480, 16, MODE_FULLSCREEN);
	graph = load_image("logo.png");

	while(! mouse.left)
	  x = mouse.x;
	  y = mouse.y;
	  FRAME;
	End;

	unload_map(0, graph);
End;
