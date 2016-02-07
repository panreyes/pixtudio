Definition
----------

**INT** load\_wav ( &lt;**STRING** filename&gt;, \[ &lt;**POINTER**
id&gt;\] )

Loads a [sound effect](sound_effect "wikilink") in the WAV format for
later use with [play\_wav](play_wav "wikilink")().

Parameters
----------

  --------------------- ------------------------------------------------------------
  **STRING** filename   - The WAV file to be loaded, including a possible path.
  **POINTER** id        - Optional parameter, for loading a wav in the background.
  --------------------- ------------------------------------------------------------

Returns
-------

**INT** : [WaveID](WaveID "wikilink")

  -------- -------------------------------------------------
  -2       - Waiting for the file to be loaded, see notes.
  -1       - There was an error loading the file.
  &gt;=0   - The waveID of the newly created sound.
  -------- -------------------------------------------------

*the following applies for versions prior rc282:*

**INT** : [WaveID](WaveID "wikilink")

  ------- ---------------------------------------
  -1      - Error: sound inactive; opening file
  0       - Could not load wave file.
  &gt;0   - The [WaveID](WaveID "wikilink").
  ------- ---------------------------------------

Notes
-----

The optional parameter **id** was introduced in version rc282 and allows
you to load resources in the background. It used with the
[Offset](Offset "wikilink") operator. See example below:

          load_wav("archivo_gordo.wav", &idwav);
          while(idwav==-2)
                say("Big File Loading ....");
                frame;
          end
          if(idwav==-1)
              say("Something went wrong!!");
              exit(); // o return
          end

          say("Big file loaded ok!!");

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

Used in example: [play\_wav](play_wav "wikilink")()

<Category:functions> <Category:sound> <Category:mod_sound>
