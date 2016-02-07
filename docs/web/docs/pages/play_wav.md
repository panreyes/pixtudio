Definition
----------

**INT** play\_wav ( &lt;**INT** waveID&gt; , &lt;**INT** repeats&gt; ,
\[&lt;**INT** channel&gt;\] )

Plays a [sound effect](sound_effect "wikilink") previously loaded with
[load\_wav](load_wav "wikilink")().

Parameters
----------

  --------------------- ---------------------------------------------------------------------------------------------------------------------------------------
  **INT** waveID        - The [WaveID](WaveID "wikilink") of the sound effect to be played.
  **INT** repeats       - Number of times to *repeat* the sound effect. Use -1 for an infinite loop.
  \[**INT** channel\]   - The [sound channel](sound_channel "wikilink") the [sound effect](sound_effect "wikilink") is to be played on (-1 for any, default).
  --------------------- ---------------------------------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : The [sound channel](sound_channel "wikilink") the [sound
effect](sound_effect "wikilink") is now playing on.

  -------- ----------------------------------------------------------------------------------------------------------------
  -1       - Error: sound inactive; invalid [waveID](waveID "wikilink")
  &gt;=0   - The [sound channel](sound_channel "wikilink") the [sound effect](sound_effect "wikilink") is now playing on.
  -------- ----------------------------------------------------------------------------------------------------------------

Example
-------

    Program
    Private
        int wave;
    Begin
        wave = load_wav("my_wav.wav");
        play_wav(wave,0);
        Loop
            frame;
        End
    End

Used in example: [load\_wav](load_wav "wikilink")()

<Category:functions> <Category:sound> <Category:mod_sound>
