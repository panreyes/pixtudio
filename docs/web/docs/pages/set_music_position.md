Definition
----------

**INT** set\_music\_position ( &lt;**FLOAT** position&gt; )

Set the position of the currently playing music, loaded with
[Load\_song](Load_song "wikilink")() and played with
[Play\_song](Play_song "wikilink")() It only works with the formats
supported by those functions. *It does not apply to wave files.*

Parameters
----------

  -------------------- -------------------------------------------------------------
  **FLOAT** position   - Jumps to position seconds from the beginning of the song.
  -------------------- -------------------------------------------------------------

Returns
-------

**INT** : Status.

  ---------- ------------------------------
  position   - The position in the music.
  -1         - Error: sound inactive.
  ---------- ------------------------------

<Category:functions> <Category:sound> <Category:mod_sound>
