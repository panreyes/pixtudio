[**Up to LCD.DLL Functions**](Functioncategory:Lcddll "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** LCD\_GetWidth ( &lt;**INT** device&gt; )

Returns the width in pixels of the LCDscreen of the specified device.

Parameters
----------

  ---------------- -------------------------
  **INT** device   - Number of the device.
  ---------------- -------------------------

Returns
-------

**INT** : The width of the LCDscreen in pixels.

  --------------------------- ------- -----------------------------------------
  LCD\_ERROR\_INVALIDDEVICE   - -20   - Invalid device.
  &gt;=0                              - The width of the LCDscreen in pixels.
  --------------------------- ------- -----------------------------------------

<Category:functions> <Category:lcddll> <Category:dll>
