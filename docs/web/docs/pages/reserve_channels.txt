Definition
----------

**INT** reserve\_channels ( &lt;**INT** num\_channels&gt; )

This functions reserves the indicated number of [sound
channels](sound_channel "wikilink") from the default sound mixing setup.
This is usefull if you want to create groups of sound channels, so that
you can devide them for different tasks. When you indicate a 0, all
reservations are removed. The channels are reserved starting from
channel 0 to num\_channels -1. Normally SDL\_mixer starts without any
channels reserved.

Parameters
----------

  ----------------------- --------------------------------------
  **INT** num\_channels   - The number of channels to reserve.
  ----------------------- --------------------------------------

Returns
-------

**INT** : Status.

  ------- ------------------------------------
  &gt;0   - The number of reserved channels.
  -1      - Error: sound inactive.
  ------- ------------------------------------

<Category:functions> <Category:sound> <Category:mod_sound>
