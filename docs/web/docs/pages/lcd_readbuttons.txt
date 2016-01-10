[**Up to LCD.DLL Functions**](Functioncategory:Lcddll "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** LCD\_ReadButtons ( &lt;**INT** device&gt; )

Updates the integer holding the buttonstatus.

Parameters
----------

  ---------------- -------------------------
  **INT** device   - Number of the device.
  ---------------- -------------------------

Returns
-------

**INT** : [LCD.DLL Errorcodes](LCD_ERRORCODES "wikilink")

  -------------------------------- ------- ----------------------------
  LCD\_ERROR\_NONE                 - 0     - No error.
  LCD\_ERROR\_SERVICEINACTIVE      - -14   - The service is inactive.
  LCD\_ERROR\_DEVICENOTCONNECTED   - -21   - Device not connected.
  LCD\_ERROR\_INVALIDPARAMETER     - -22   - Invalid parameter.
  -------------------------------- ------- ----------------------------

<Category:functions> <Category:lcddll> <Category:dll>
