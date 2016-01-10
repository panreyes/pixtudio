Syntax
------

**INT** joy\_gethat ( \[ &lt;**INT** JoyID&gt; \] , &lt;**INT** hat&gt;
)

Description
-----------

Returns the current position of the digital POV hat of the controller
pad selected.

The return values are:

  --------------------- ----------- ------------------------------------
  *Constant*            - *Value*   - *Description*
  JOY\_HAT\_CENTERED    - 0         - The hat is centered.
  JOY\_HAT\_UP          - 1         - The hat is moved up.
  JOY\_HAT\_RIGHT       - 2         - The hat is moved right.
  JOY\_HAT\_DOWN        - 4         - The hat is moved down.
  JOY\_HAT\_LEFT        - 8         - The hat is moved left.
  JOY\_HAT\_RIGHTUP     - 3         - The hat is moved right and up.
  JOY\_HAT\_RIGHTDOWN   - 6         - The hat is moved right and down.
  JOY\_HAT\_LEFTUP      - 9         - The hat is moved left and up.
  JOY\_HAT\_LEFTDOWN    - 12        - The hat is moved left and down.
  --------------------- ----------- ------------------------------------

You may notice that some are combinations of others. For example
JOY\_HAT\_RIGHTUP == (JOY\_HAT\_RIGHT | JOY\_HAT\_UP ). This is because
the returned value has [bit flags](bit_flag "wikilink") indicating four
directions: up, down, left, right. These can be combined to make
diagonal directions.

A value of -1 is returned when there is no hat or
[joystick](joystick "wikilink") detected.

The JoyID is optional, if it is not present, the function uses the
selected joystick. You can change the selected joystick with
[joy\_select](joy_select "wikilink")().

Parameters
----------

  ------------------- -------------------------------------------------------------------------
  \[**INT** JoyID\]   - The [JoyID](JoyID "wikilink") of the [joystick](joystick "wikilink").
  **INT** hat         - The number of the hat, starting at `0`
  ------------------- -------------------------------------------------------------------------

Returns
-------

**INT** : The position of the POV hat.

Example
-------

<Category:functions> <Category:Joystick> <Category:Mod_joy>
