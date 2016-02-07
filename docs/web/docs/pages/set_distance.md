Definition
----------

**INT** set\_distance ( &lt;**INT** channel&gt; , &lt;**INT**
distance&gt; )

Set the "distance" of a [sound channel](sound_channel "wikilink"). the
distance specifies the location of the sound in relation to the
listener. If you want also want to have control over the angle, see
[Set\_position](Set_position "wikilink")().

Parameters
----------

  ------------------ ----------------------------------------------------------------------------
  **INT** channel    - The [sound channel](sound_channel "wikilink") to change the position of.
  **INT** distance   - The distance (0-255).
  ------------------ ----------------------------------------------------------------------------

Returns
-------

**INT** : Status.

  ---- --------------------------
  0    - Ok.
  -1   - Error: sound inactive.
  ---- --------------------------

Notes
-----

*Distance value's*

  ----- -------------------------------------------
  0     - The sound is near (or at it's loudest).
  255   - The sound is far away (very quite).
  ----- -------------------------------------------

<Category:functions> <Category:sound> <Category:mod_sound>
