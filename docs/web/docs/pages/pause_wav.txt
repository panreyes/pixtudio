Definition
----------

**INT** pause\_wav (**INT** &lt; channel &gt; )

Pauses the currently playing wave channel.

Notes
-----

The sound channel pauses immediately, but can be resumed later by
calling [resume\_wav](resume_wav "wikilink")(). For a nicer effect, you
may want to fade the music out before pausing. See
[set\_channel\_volume](set_channel_volume "wikilink")().

Parameters
----------

  ----------------- ------------------------------------------------------
  **INT** channel   - The WAV [sound channel](sound_channel "wikilink").
  ----------------- ------------------------------------------------------

Returns
-------

**INT** : Error.

  ---- ----------------------------------
  -1   - Error: sound channel inactive.
  0    - No error.
  ---- ----------------------------------

Example
-------

    // import modules
    IMPORT "mod_say";
    IMPORT "mod_debug";
    IMPORT "mod_proc";
    IMPORT "mod_key";
    IMPORT "mod_sound";

    GLOBAL
       int wav;
       int channel;
      
    PROCESS main();  
    BEGIN

      wav=load_wav("wav.wav");
      
      say("Test pause_wav...");
      say("ENTER = Pause Sound...");
      say("Press ESC to quit...");
      
      channel=play_wav(wav,-1);
      
      REPEAT
      
        IF(key(_enter))
          pause_wav(channel);
          FRAME(2500);
          resume_wav(channel);
        END
        
        FRAME;
      UNTIL(key(_esc))
    END

Used in example: [key](key "wikilink")(), [say](say "wikilink")(),
[resume\_wav](resume_wav "wikilink")(),
[play\_wav](play_wav "wikilink")(), [load\_wav](load_wav "wikilink")().

<Category:functions> <Category:sound> <Category:mod_sound>
