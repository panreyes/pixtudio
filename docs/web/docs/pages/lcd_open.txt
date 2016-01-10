[**Up to LCD.DLL Functions**](Functioncategory:Lcddll "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** LCD\_Open ( &lt;**INT** device&gt; , &lt;**INT POINTER**
buttons&gt; )

Opens a connection to an LCDscreen.

Parameters
----------

  ------------------------- ------------------------------------------------
  **INT** device            - Number of the device.
  **INT POINTER** buttons   - Pointer to the buttonstatus holding integer.
  ------------------------- ------------------------------------------------

Returns
-------

**INT** : [LCD.DLL Errorcodes](LCD_ERRORCODES "wikilink")

  ------------------------------ ------- ----------------------------
  LCD\_ERROR\_NONE               - 0     - No error.
  LCD\_ERROR\_SERVICEINACTIVE    - -14   - The service is inactive.
  LCD\_ERROR\_INVALIDPARAMETER   - -22   - Invalid parameter.
  ------------------------------ ------- ----------------------------

<Category:functions> <Category:lcddll> <Category:dll>
