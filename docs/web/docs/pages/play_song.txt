Definition
----------

**INT** play\_song ( &lt;**INT** songID&gt; , &lt;**INT** repeats&gt; )

Plays a song.

Parameters
----------

  ----------------- --------------------------------------------------------------------------------------------------------
  **INT** songID    - [SongID](SongID "wikilink") of the song loaded previously with [load\_song](load_song "wikilink")().
  **INT** repeats   - Number of times to repeat the song. Use -1 for an infinite loop.
  ----------------- --------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : Error.

  ---- ----------------------------------------------------------------------------
  -1   - Error: sound inactive; mixer error; invalid [songID](songID "wikilink").
  0    - No error.
  ---- ----------------------------------------------------------------------------

Errors
------

  ---------------- ------------------------------------------------
  Sound inactive   - The sound is inactive.
  Invalid songID   - The [songID](songID "wikilink") was invalid.
  Other            - Some Mixer error.
  ---------------- ------------------------------------------------

Example
-------

    Program example;
    Private
        int song;
    Begin
        song = load_song("my_song.ogg");
        play_song(song,0);
        Loop
            frame;
        End
    End

Used in example: [load\_song](load_song "wikilink")()

<Category:functions> <Category:sound> <Category:mod_sound>
