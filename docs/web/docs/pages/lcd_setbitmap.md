[**Up to LCD.DLL Functions**](Functioncategory:Lcddll "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** LCD\_SetBitmap ( &lt;**INT** device&gt; , &lt;**INT**
priority&gt; , &lt;**BYTE POINTER** map&gt; )

Sets the bitmap of the device to a certain map with a certain priority.

Parameters
----------

  ---------------------- ----------------------------------------------------------------
  **INT** device         - Number of the device.
  **INT** priority       - The priority of the bitmap (see [notes](#Notes "wikilink")).
  **BYTE POINTER** map   - Pointer to a 160x43 byte array.
  ---------------------- ----------------------------------------------------------------

Returns
-------

**INT** : [LCD.DLL Errorcodes](LCD_ERRORCODES "wikilink")

  -------------------------------- ------- ----------------------------
  LCD\_ERROR\_NONE                 - 0     - No error.
  LCD\_ERROR\_SERVICEINACTIVE      - -14   - The service is inactive.
  LCD\_ERROR\_DEVICENOTCONNECTED   - -21   - Device not connected.
  LCD\_ERROR\_INVALIDPARAMETER     - -22   - Invalid parameter.
  -------------------------------- ------- ----------------------------

Notes
-----

-   Multiple priorities can be used:

  ------------------------------- ------------------------------------------------------------------------------------------------------
  LCD\_PRIORITY\_IDLE\_NO\_SHOW   - Lowest priority, disable displaying. Use this priority when you don’t have anything to show.
  LCD\_PRIORITY\_BACKGROUND       - Priority used for low priority items.
  LCD\_PRIORITY\_NORMAL           - Normal priority, to be used by most applications most of the time.
  LCD\_PRIORITY\_ALERT            - Highest priority. To be used only for critical screens, such as "your CPU temperature is too high"
  ------------------------------- ------------------------------------------------------------------------------------------------------

-   One can use [map\_buffer](map_buffer "wikilink")() to obtain a byte
    pointer to a map. Make sure this map is of size 160x43 and it has a
    color depth of 8.

<Category:functions> <Category:lcddll> <Category:dll>
