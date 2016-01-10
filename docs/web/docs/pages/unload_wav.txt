Definition
----------

**INT** unload\_wav ( &lt;**INT** WaveID&gt; )

Frees the memory occupied by the wave file, previously loaded with
[load\_wav](load_wav "wikilink")().

Parameters
----------

  ---------------- -----------------------------------------------------------
  **INT** WaveID   - The [WaveID](WaveID "wikilink") of the sound to unload.
  ---------------- -----------------------------------------------------------

Returns
-------

**INT** : Error.

  ---- ---------------------------------------------------------------
  -1   - Error: sound inactive; invalid [waveID](waveID "wikilink").
  0    - No error.
  ---- ---------------------------------------------------------------

Notes
-----

Instead of an **INT** a **POINTER** may also be used in the WaveID
argument.

<Category:functions> <Category:sound> <Category:mod_sound>
