[**Up to Network.DLL**](Networkdll "wikilink")

------------------------------------------------------------------------

General
-------

  ---------------------- --------------------------------------------------------------------------
  | NET\_MAX\_MSG\_LEN   - Maximum number of bytes per message. (doesn't really apply, ignore it)
  | NET\_FPS             - The frame percentage of the NET Loop. (default is frame;)
  ---------------------- --------------------------------------------------------------------------

Connection Status codes
-----------------------

  ------------------------------ ------ ----------------------------------------
  | NET\_STATUS\_DISCONNECTING   - -4   - The connection is being disconnected
  | NET\_STATUS\_DISCONNECTED    - -2   - The connection is disconnected.
  | NET\_STATUS\_INACTIVE        - 0    - (The connection is) inactive.
  | NET\_STATUS\_ACTIVE          - 1    - (The connection is) active.
  | NET\_STATUS\_ESTABLISHED     - 2    - The connection is established.
  | NET\_STATUS\_ESTABLISHING    - 4    - The connection is being established.
  ------------------------------ ------ ----------------------------------------

Console Reports modes
---------------------

  ---------------------------- ----------------------------- -----------------------------
  | NET\_CONSOLEREPORTS\_NO    - [false](false "wikilink")   - Console reports disabled.
  | NET\_CONSOLEREPORTS\_YES   - [true](true "wikilink")     - Console reports enabled.
  ---------------------------- ----------------------------- -----------------------------

Errorcodes
----------

[NET\_Errorcodes](NET_Errorcodes "wikilink")

<Category:defines> <Category:networkdll> <Category:dll>
