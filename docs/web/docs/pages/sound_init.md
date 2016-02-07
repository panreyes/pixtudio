Definition
----------

**INT** sound\_init ( )

Manually Initializes the audio system. This is normally not needed, but
may be necessary on some systems with SDL mixer issues. *(verification
needed)*

Parameters
----------

This function has no parameters.

Returns
-------

**INT** : Status/error.

  ---- ------------------------------------------------------------
  0    - The audio device is opened.
  -1   - There's an error, failed to initialize the audio system.
  ---- ------------------------------------------------------------

See also
--------

[Sound\_close](Sound_close "wikilink")()

<Category:functions> <Category:sound> <Category:mod_sound>
