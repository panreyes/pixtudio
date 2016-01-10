Syntax
------

**INT** joy\_numhats ( \[ &lt;**INT** JoyID&gt; \] )

Description
-----------

Returns the number of [hats](joystick#hat "wikilink") on the specified
[joystick](joystick "wikilink"). If no joystick is specified, the number
of hats on the currently [selected
joystick](selected_joystick "wikilink") will be returned.

The JoyID is optional, if it is not present, the function uses the
selected joystick. You can change the selected joystick with
joy\_select().

Parameters
----------

  ------------------- -------------------------------------------------------------------------
  \[**INT** JoyID\]   - The [JoyID](JoyID "wikilink") of the [joystick](joystick "wikilink").
  ------------------- -------------------------------------------------------------------------

Returns
-------

**INT** : The number of [hats](joystick#Hat "wikilink").

<Category:functions> <Category:Joystick> <Category:Mod_joy>
