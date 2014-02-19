import "mod_say";
import "mod_sound";
import "mod_mouse";

Process main()
Private
	int song=0, fd=0;
	string fname="game.mp3";
Begin
	say("Going to play "+fname+", hope you like it :)");
	say("Press (A) in you Wiimote to quit.");
	song = load_song(fname);
	say("Loaded");
	play_song(song, 0);
	say("Playback started");
//	say("Playing sound @ "+SOUND_FREQ+"Hz");
	while(is_playing_song() && ! mouse.left)
		FRAME;
	end;
	say("Done looping");
	stop_song();
	say("Stopped");
	unload_song(song);
	say("Completely done");
	say("Quitting...");
End;
