Definition
----------

**INT** is\_playing\_song ( )

Checks to see if Bennu is playing a song file, started with
[play\_song](play_song "wikilink")().

Returns
-------

**INT** : Whether Bennu is playing a song at the moment of calling.

  --------------------------- --------------------------------
  [true](true "wikilink")     - Bennu is playing a song.
  [false](false "wikilink")   - Bennu is not playing a song.
  --------------------------- --------------------------------

Example
-------

    program music_example;
    global
        my_song;
        playing;
        paused;
        faded_in;
        v;
    begin
        set_mode(640,480,16);
        
        my_song=load_song("beat.ogg");
        
        write(0,320,30,4,"Use the keyboard to control the music playback.");
        write(0,320,50,4,"Key [ENTER] starts / stops the song.");
        write(0,320,60,4,"Key [SPACE] pauses / resumes the song.");
        write(0,320,70,4,"Key [0] through key [9] changes the song volume.");
        write(0,320,80,4,"Key [F] fades the song in or out.");
        
        write(0,320,120,5,"Playing: ");
        write_int(0,320,120,3,&playing);
        
        write(0,320,140,5,"Paused: ");
        write_int(0,320,140,3,&paused);
        
        write(0,320,160,5,"Faded in: ");
        write_int(0,320,160,3,&faded_in);
        
        write(0,320,180,5,"Volume: ");
        write_int(0,320,180,3,&v);
        
        v=128;
        faded_in=true;


        repeat
            if(key(_enter))
                if(is_playing_song())
                    stop_song();
                    playing=false;
                else
                    play_song(my_song,1);
                    playing=true;
                end
                while(key(_enter))frame;end
            end
            
            if(key(_space))
                if(paused)
                    paused=false;
                    resume_song();
                else
                    paused=true;
                    pause_song();
                end
                while(key(_space))frame;end
            end
            
            if(key(_f))
                if(faded_in)
                    faded_in=false;
                    fade_music_off(100);
                else
                    faded_in=true;
                    fade_music_in(my_song,1,100);
                end
                while(key(_f))frame;end
            end
            
            if(key(_0))v=0;end
            if(key(_1))v=14;end
            if(key(_2))v=28;end
            if(key(_3))v=43;end
            if(key(_4))v=57;end
            if(key(_5))v=71;end
            if(key(_6))v=85;end
            if(key(_7))v=100;end
            if(key(_8))v=114;end
            if(key(_9))v=128;end
            
            set_song_volume(v);

        frame;
        until(key(_esc))
        
        exit();
    end

Used in example: [key](key "wikilink")(),
[set\_mode](set_mode "wikilink")(),
[load\_song](load_song "wikilink")(), [write](write "wikilink")(),
[write\_int](write_int "wikilink")(),
[pause\_song](pause_song "wikilink")(),
[play\_song](play_song "wikilink")(),
[stop\_song](stop_song "wikilink")(),
[resume\_song](resume_song "wikilink")(),
[fade\_music\_in](fade_music_in "wikilink")(),
[fade\_music\_off](fade_music_off "wikilink")(),
[set\_song\_volume](set_song_volume "wikilink")().

<Category:functions> <Category:sound> <Category:mod_sound>
