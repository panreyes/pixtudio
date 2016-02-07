[**Up to LCD.DLL Functions**](Functioncategory:Lcddll "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** LCD\_ReadButton ( &lt;**INT** device&gt; , &lt;**INT**
button&gt; )

Returns whether a button is being pressed on a device.

This also updates the button integer specified at
[LCD\_Open](LCD_Open "wikilink")().

Parameters
----------

  ---------------- -------------------------
  **INT** device   - Number of the device.
  **INT** button   - Number of the button.
  ---------------- -------------------------

Returns
-------

**INT** : [LCD.DLL Errorcodes](LCD_ERRORCODES "wikilink")

  ------------------------------ ------- ------------------------------------
  [TRUE](TRUE "wikilink")        - 1     - The button is being pressed.
  [FALSE](FALSE "wikilink")      - 0     - The button is not being pressed.
  LCD\_ERROR\_SERVICEINACTIVE    - -14   - The service is inactive.
  LCD\_ERROR\_INVALIDPARAMETER   - -22   - Invalid parameter.
  ------------------------------ ------- ------------------------------------

<Category:functions> <Category:lcddll> <Category:dll>
