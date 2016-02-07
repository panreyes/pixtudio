Syntax
------

**INT** joy\_numaxes ( \[ &lt;**INT** JoyID&gt; \] )

Description
-----------

Returns the number of [axes](joystick#axis "wikilink") on the specified
[joystick](joystick "wikilink"). If no joystick is specified, the number
of axes on the currently [selected
joystick](selected_joystick "wikilink") will be returned.

The JoyID is optional, if it is not present, the function uses the
selected joystick. You can change the selected joystick with
[joy\_select](joy_select "wikilink")().

Also called [joy\_axes](joy_axes "wikilink")().

Parameters
----------

  ------------------- -------------------------------------------------------------------------
  \[**INT** JoyID\]   - The [JoyID](JoyID "wikilink") of the [joystick](joystick "wikilink").
  ------------------- -------------------------------------------------------------------------

Returns
-------

**INT** : The number of [axes](joystick#Axis "wikilink").

<Category:functions> <Category:Joystick> <Category:Mod_joy>
