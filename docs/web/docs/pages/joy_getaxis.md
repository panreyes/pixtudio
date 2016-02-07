Syntax
------

**INT** joy\_getaxis ( \[ &lt;**INT** joy&gt;\], &lt;**INT** axis&gt; )

Description
-----------

Returns the selected joystick state for the given axis.

The JoyID is optional, if it is not present, the function uses the
selected joystick. You can change the selected joystick with
joy\_select().

Also called [joy\_getposition](joy_getposition "wikilink")(). The
previous name [get\_joy\_position](get_joy_position "wikilink")() is
deprecated.

Parameters
----------

  ------------------- -------------------------------------------------------------------------
  \[**INT** JoyID\]   - The [JoyID](JoyID "wikilink") of the [joystick](joystick "wikilink").
  **INT** axis        - The [axis](axis "wikilink") of the [joystick](joystick "wikilink").
  ------------------- -------------------------------------------------------------------------

Returns
-------

**INT** : state for the given axis.

<Category:functions> <Category:Joystick> <Category:Mod_joy>
