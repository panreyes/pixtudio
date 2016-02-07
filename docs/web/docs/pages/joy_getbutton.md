Syntax
------

**INT** joy\_getbutton ( \[ &lt;**INT** joy&gt;\], &lt;**INT**
button&gt; )

Description
-----------

Returns the selected joystick state for the given button.

The JoyID is optional, if it is not present, the function uses the
selected joystick. You can change the selected joystick with
joy\_select().

The previous name [get\_joy\_button](get_joy_button "wikilink")() is
deprecated.

Parameters
----------

  ------------------- ---------------------------------------------------------------------------
  \[**INT** JoyID\]   - The [JoyID](JoyID "wikilink") of the [joystick](joystick "wikilink").
  **INT** button      - The [button](button "wikilink") on the [joystick](joystick "wikilink").
  ------------------- ---------------------------------------------------------------------------

Returns
-------

**INT** : state for the given button.

<Category:functions> <Category:Joystick> <Category:Mod_joy>
