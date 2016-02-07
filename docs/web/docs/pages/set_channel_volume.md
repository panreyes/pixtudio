Definition
----------

**INT** set\_channel\_volume ( &lt;**INT** channel&gt; , &lt;**INT**
volume&gt; )

Change the reproduction volume of the wave [sound
channel](sound_channel "wikilink"). With this function, it is possible
to set the channels to different volumes.

Parameters
----------

  ----------------- --------------------------------------------------
  **INT** channel   - The [sound channel](sound_channel "wikilink").
  **INT** volume    - New volume. (0..128).
  ----------------- --------------------------------------------------

Returns
-------

**INT** : Error.

  ---- --------------------------
  -1   - Error: sound inactive.
  0    - No error.
  ---- --------------------------

Notes
-----

This function changes the reproduction volume of the sound channel. The
volume level can be set between 0 (silence) and 128 (original 100%
volume of the track. The default volume is 128.

<Category:functions> <Category:sound> <Category:mod_sound>
