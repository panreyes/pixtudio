[**Up to LCD.DLL Functions**](Functioncategory:Lcddll "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** LCD\_Init( &lt;**STRING** connectionname&gt; )

Initializes [LCD.DLL](LCD.DLL "wikilink").

Parameters
----------

  --------------------------- ------------------------------------------------------------------------------------------------
  **STRING** connectionname   - The name of the connection. This will be displayed when browsing LCD connections on the LCD.
  --------------------------- ------------------------------------------------------------------------------------------------

Returns
-------

**INT** : [LCD.DLL Errorcodes](LCD_ERRORCODES "wikilink")

  ----------------------------------- ------- ------------------------------------------------
  LCD\_ERROR\_NONE                    - 0     - No error.
  LCD\_ERROR\_RPCSSERVERUNAVAILABLE   - -10   - The RPC Server is unavailable.
  LCD\_ERROR\_RPCXWRONGPIPEVERSION    - -11   - RPC X: wrong pipe version
  LCD\_ERROR\_OLDWINVERSION           - -12   - Old Windows Version (must be 2000 or higher)
  LCD\_ERROR\_NOSYSTEMRESOURCES       - -13   - No system resources available.
  LCD\_ERROR\_SERVICEINACTIVE         - -14   - The service is inactive.
  LCD\_ERROR\_ALREADYINITIALIZED      - -16   - LCD.DLL was already initialized.
  LCD\_ERROR\_INVALIDPARAMETER        - -22   - Invalid parameter.
  LCD\_ERROR\_FILENOTFOUND            - -23   - File not found.
  LCD\_ERROR\_ALREADYEXISTS           - -24   - File or connection already exists.
  ----------------------------------- ------- ------------------------------------------------

<Category:functions> <Category:lcddll> <Category:dll>
