import "mod_joy";
import "mod_video";
import "mod_say";

Process main()
Private
    int pointer modes;
    int nmodes=0, i=0;

Begin
    //if(mode_is_ok(640, 480, 16, MODE_WINDOW))
      set_mode(640, 480, 16, MODE_WINDOW);
    //end;
    while(!joy_getbutton(0, 0))
        FRAME;
    end;
End;
