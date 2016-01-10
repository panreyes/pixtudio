[**Up to LCD.DLL Functions**](Functioncategory:Lcddll "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** LCD\_GetNumButtons ( &lt;**INT** device&gt; )

Returns the number of soft buttons of the LCDscreen of the specified
device.

Parameters
----------

  ---------------- -------------------------
  **INT** device   - Number of the device.
  ---------------- -------------------------

Returns
-------

**INT** : The number of soft buttons of the LCDscreen.

  --------------------------- ------- ------------------------------------------------
  LCD\_ERROR\_INVALIDDEVICE   - -20   - Invalid device.
  &gt;=0                              - The number of soft buttons of the LCDscreen.
  --------------------------- ------- ------------------------------------------------

<Category:functions> <Category:lcddll> <Category:dll>
