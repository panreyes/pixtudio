import "mod_say"
import "mod_video"
import "mod_map"
import "mod_key"
import "mod_text"

Process main()
Begin
    set_mode(800, 600);
    x = 400; y = 300;
    graph = jpg_load("jpg/sunset_on_mars.jpg");
    write(0, 400, 0, 1, "Press esc to quit");
    while(!key(_esc))
        frame;
    end
End
