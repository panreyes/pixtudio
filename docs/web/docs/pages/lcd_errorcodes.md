[**Up to LCD.DLL**](Lcddll "wikilink")

------------------------------------------------------------------------

Here is a list of all the errorcodes regarding
[LCD.DLL](LCD_DLL "wikilink").

Catching errorcodes is very easy: just check if the return value is
negative, then it is an error.

    result = LCD_Xxx();
    if(result<0)
        say("LCD Errorcode: " + result);
    else
        // success
    end

  ----------------------------------- ----------- ------------------------------------------------
  *Constant*                          - *Value*   - *Description*
  LCD\_ERROR\_NONE                    - 0         - No error.
  LCD\_ERROR\_RPCSSERVERUNAVAILABLE   - -10       - The RPC Server is unavailable.
  LCD\_ERROR\_RPCXWRONGPIPEVERSION    - -11       - RPC X: wrong pipe version
  LCD\_ERROR\_OLDWINVERSION           - -12       - Old Windows Version (must be 2000 or higher)
  LCD\_ERROR\_NOSYSTEMRESOURCES       - -13       - No system resources available.
  LCD\_ERROR\_SERVICEINACTIVE         - -14       - The service is inactive.
  LCD\_ERROR\_NOTINITIALIZED          - -15       - LCD.DLL is not initialized.
  LCD\_ERROR\_ALREADYINITIALIZED      - -16       - LCD.DLL was already initialized.
  LCD\_ERROR\_INVALIDCONNECTION       - -17       - Invalid connection.
  LCD\_ERROR\_TOOMANYCONNECTIONS      - -18       - Too many connections.
  LCD\_ERROR\_NOACTIVECONNECTIONS     - -19       - There are no active connections.
  LCD\_ERROR\_INVALIDDEVICE           - -20       - Invalid device.
  LCD\_ERROR\_DEVICENOTCONNECTED      - -21       - Device not connected.
  LCD\_ERROR\_INVALIDPARAMETER        - -22       - Invalid parameter.
  LCD\_ERROR\_FILENOTFOUND            - -23       - File not found.
  LCD\_ERROR\_ALREADYEXISTS           - -24       - File or connection already exists.
  LCD\_ERROR\_NOMOREITEMS             - -25       - No more devices to enumerate.
  LCD\_ERROR\_INVALIDBUTTON           - -26       - Invalid button.
  LCD\_ERROR\_UNKNOWN                 - -27       - Unknown error.
  ----------------------------------- ----------- ------------------------------------------------

<Category:errorcodes> <Category:lcddll> <Category:dll>