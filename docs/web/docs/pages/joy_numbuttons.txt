Syntax
------

**INT** joy\_numbuttons ( \[ &lt;**INT** JoyID&gt; \] )

Description
-----------

Returns the number of [buttons](joystick#button "wikilink") on the
specified [joystick](joystick "wikilink"). If no joystick is specified,
the number of buttons on the currently [selected
joystick](selected_joystick "wikilink") will be returned.

The JoyID is optional, if it is not present, the function uses the
selected joystick. You can change the selected joystick with
joy\_select().

Also called [joy\_buttons](joy_buttons "wikilink")().

Parameters
----------

  ------------------- -------------------------------------------------------------------------
  \[**INT** JoyID\]   - The [JoyID](JoyID "wikilink") of the [joystick](joystick "wikilink").
  ------------------- -------------------------------------------------------------------------

Returns
-------

**INT** : The number of [buttons](joystick#Button "wikilink").

<Category:functions> <Category:Joystick> <Category:Mod_joy>
