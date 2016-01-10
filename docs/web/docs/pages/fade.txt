Definition
----------

**INT** fade ( &lt;**INT** red&gt; , &lt;**INT** green&gt; , &lt;**INT**
blue&gt; , &lt;**INT** speed&gt; )

Fades the screen from the current setting to the specified setting
(*red*,*green*,*blue*) at the specified speed.

Parameters
----------

  --------------- -----------------------------------------------------
  **INT** red     - Amount of red shown from 0 to 200. 100 is normal.
  **INT** green   - Amount of red shown from 0 to 200. 100 is normal.
  **INT** blue    - Amount of red shown from 0 to 200. 100 is normal.
  **INT** speed   - The speed of the fade from 1 to 64.
  --------------- -----------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Notes
-----

Standard RGB combinations:

  --------------- -----------------
  *(R,G,B)*       - *Description*
  (0,0,0)         - Black out.
  (100,100,100)   - Normal.
  (200,200,200)   - White out.
  --------------- -----------------

The number of frames the fading will take can be calculated like this:

:   frames = roundup( 64 / speed )
:   speed = roundup( 64 / frames )

So:

  --------- --------------------
  *Speed*   - *Description*
  &lt;0     - Takes 1 frame.
  0         - Pointless.
  1         - Takes 64 frames.
  2         - Takes 32 frames.
  3         - Takes 22 frames.
  &gt;=64   - Takes 1 frame.
  --------- --------------------

See also [fade\_on](fade_on "wikilink")() and
[fade\_off](fade_off "wikilink")().

<Category:functions> <Category:palettes> <Category:mod_map>
