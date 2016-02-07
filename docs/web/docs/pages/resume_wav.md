Definition
----------

**INT** resume\_wav (**INT** &lt; channel &gt; )

Resumes the currently paused wave channel, that was paused by
[Pause\_wav](Pause_wav "wikilink")().

Parameters
----------

  ----------------- ------------------------------------------------------
  **INT** channel   - The WAV [sound channel](sound_channel "wikilink").
  ----------------- ------------------------------------------------------

Returns
-------

**INT** : Error.

  ---- --------------------------
  -1   - Error: sound inactive.
  0    - No error.
  ---- --------------------------

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
[pause\_wav](pause_wav "wikilink")(),
[play\_wav](play_wav "wikilink")(), [load\_wav](load_wav "wikilink")().

<Category:functions> <Category:sound> <Category:mod_sound>
