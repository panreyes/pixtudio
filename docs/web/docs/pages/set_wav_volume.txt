Syntax
------

**INT** set\_wav\_volume ( &lt;**INT** waveID&gt; , &lt;**INT**
volume&gt; )

Description
-----------

Change the reproduction volume of the wav track.

With this function, it is possible to set the volume of the sound
effects, etc.

Parameters
----------

  ---------------- ----------------------------------------------------------------------------------
  **INT** waveID   - [waveID](waveID "wikilink") as returned by [load\_wav](load_wav "wikilink")().
  **INT** volume   - New volume. (0..128)
  ---------------- ----------------------------------------------------------------------------------

Returns
-------

(assumed) **INT** : Error.

  ---- --------------------------
  -1   - Error: sound inactive.
  0    - No error.
  ---- --------------------------

Notes
-----

This function changes the reproduction volume of the wav track. The
volume level can be set between 0 (silence) and 128 (original 100%
volume of the track. The default volume is 128.

Example
-------

    global
        int my_wav;
        int v;
    end

    process main()
    begin

        set_mode(640,480,16);
        
        my_wav = load_wav("beat.wav");
        
        write(0,320,30,4,"Use the keyboard to control the music playback.");
        write(0,320,50,4,"Key [ENTER] starts the wav.");
        write(0,320,60,4,"Key [0] through key [9] changes the song volume.");
        
        write(0,320,180,5,"Volume: ");
        write_int(0,320,180,3,&v);
        
        v = 128;

        repeat
            if(key(_ENTER))
                play_wav(my_wav,50);
                while(key(_ENTER))
                    frame;
                end
            end
            
                  
            if(key(_0)) v =   0; end
            if(key(_1)) v =  14; end
            if(key(_2)) v =  28; end
            if(key(_3)) v =  43; end
            if(key(_4)) v =  57; end
            if(key(_5)) v =  71; end
            if(key(_6)) v =  85; end
            if(key(_7)) v = 100; end
            if(key(_8)) v = 114; end
            if(key(_9)) v = 128; end
            
            set_wav_volume(v);

            frame;
        until(key(_ESC))
        
    end

Used in example: [key](key "wikilink")(),
[set\_mode](set_mode "wikilink")(), [load\_wav](load_wav "wikilink")(),
[write](write "wikilink")(), [write\_int](write_int "wikilink")(),
[play\_wav](play_wav "wikilink")().

*This example uses media: [beat.wav](Media:beat.wav "wikilink")*

<Category:functions> <Category:sound> <Category:mod_sound>
