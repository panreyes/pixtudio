Definition
----------

**INT** fade\_music\_in ( &lt;**INT** songID&gt; , &lt;**INT**
num\_loops&gt; , &lt;**INT** ms&gt; )

Fades the music in, stepping up the volume from silence to the main song
volume, i.e. set by the
[Set\_song\_volume](Set_song_volume "wikilink")() function.

Parameters
----------

  -------------------- ------------------------------------------------------------------------------------------
  **INT** songID       - The identification code of the song, returned by [load\_song](load_song "wikilink")().
  **INT** num\_loops   - The number of loops, a value of -1 will be an infinite loop.
  **INT** ms           - Microseconds of fading (the duration).
  -------------------- ------------------------------------------------------------------------------------------

Returns
-------

**INT** : Error.

  ---- --------------------------
  -1   - Error: sound inactive.
  ---- --------------------------

See also
--------

[Fade\_music\_off](Fade_music_off "wikilink")().

<Category:functions> <Category:sound> <Category:mod_sound>
