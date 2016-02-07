Definition
----------

**INT** set\_position ( &lt;**INT** channel&gt; , &lt;**INT** angle&gt;
, &lt;**INT** distance&gt; )

Sets the position of a [sound channel](sound_channel "wikilink"). With
this function you can "emulate" a simple 3d audio effect. If you only
want to control the distance, you can use
[Set\_distance](Set_distance "wikilink")().

Parameters
----------

  ------------------ ----------------------------------------------------------------------------
  **INT** channel    - The [sound channel](sound_channel "wikilink") to change the position of.
  **INT** angle      - The angle (0-360).
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

*Angle value's*

  ------------- -----------------------------------
  0 degrees     - Sound is directly in front.
  90 degrees    - Sound is directly to the right.
  180 degrees   - Sound is directly behind.
  270 degrees   - Sound is directly to the left.
  ------------- -----------------------------------

*Distance value's*

  ----- -------------------------------------------
  0     - The sound is near (or at it's loudest).
  255   - The sound is far away (very quite).
  ----- -------------------------------------------

<Category:functions> <Category:sound> <Category:mod_sound>
