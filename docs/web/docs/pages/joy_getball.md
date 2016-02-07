Syntax
------

**INT** joy\_getball ( \[ &lt;**INT** JoyID&gt; \] , &lt;**POINTER**
dx&gt; , &lt;**POINTER** dy&gt;)

Description
-----------

Returns the state of the specfied ball on the current selected joystick.

The JoyID is optional, if it is not present, the function uses the
selected joystick. You can change the selected joystick with
[joy\_select](joy_select "wikilink")().

Parameters
----------

  ------------------- -------------------------------------------------------------------------
  \[**INT** JoyID\]   - The [JoyID](JoyID "wikilink") of the [joystick](joystick "wikilink").
  **POINTER** dx      - A pointer to the variable X of the ball.
  **POINTER** dy      - A pointer to the variable Y of the ball.
  ------------------- -------------------------------------------------------------------------

Returns
-------

**INT** : The state of the specfied ball on the current selected
joystick.

Example
-------

<Category:functions> <Category:Joystick> <Category:Mod_joy>
