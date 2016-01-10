Definition
----------

**INT** unload\_song ( &lt;**INT** SongID&gt; )

Frees the memory occupied by the song file, previously loaded with
[load\_song](load_song "wikilink")().

Parameters
----------

  ---------------- ----------------------------------------------------------
  **INT** SongID   - The [SongID](SongID "wikilink") of the song to unload.
  ---------------- ----------------------------------------------------------

Returns
-------

**INT** : Error.

  ---- ---------------------------------------------------------------
  -1   - Error: sound inactive; invalid [songID](songID "wikilink").
  0    - No error.
  ---- ---------------------------------------------------------------

Notes
-----

Instead of an **INT** a **POINTER** may also be used in the SongID
argument.

<Category:functions> <Category:sound> <Category:mod_sound>
