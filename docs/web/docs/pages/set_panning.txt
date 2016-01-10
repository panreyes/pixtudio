Definition
----------

**INT** set\_panning ( &lt;**INT** channel&gt; , &lt;**INT** left&gt; ,
&lt;**INT** right&gt; )

Sets the stereo panning of a [sound channel](sound_channel "wikilink"),
i.e. set the volumes of the left and right speakers individually.

Parameters
----------

  ----------------- ---------------------------------------------------------------------------
  **INT** channel   - The [sound channel](sound_channel "wikilink") to change the panning of.
  **INT** left      - The volume of the left speaker (0-255).
  **INT** right     - The volume of the right speaker (0-255).
  ----------------- ---------------------------------------------------------------------------

Returns
-------

**INT** : Status.

  ---- --------------------------
  0    - Ok.
  -1   - Error: sound inactive.
  ---- --------------------------

<Category:functions> <Category:sound> <Category:mod_sound>
