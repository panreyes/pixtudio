[**Up to Network.DLL**](Networkdll "wikilink")

------------------------------------------------------------------------

Struct NET
----------

  -------------------------------------- -------------------------------------------------------------------------------------------------------------------------------------------
  | **INT** Activity                     - [true](true "wikilink")/[false](false "wikilink"): whether there is an incoming message on a connection. READ ONLY
  | **INT POINTER** Incoming             - The change of state of each connection. READ ONLY
  | **INT POINTER** Status               - The status of each connection. READ ONLY
  | **WORD** MaxConnections              - Maximum number of connections specified when [NET\_Init](NET_Init "wikilink") was called. READ ONLY
  | **WORD** MaxListenPorts              - Maximum number of listenports specified when [NET\_Init](NET_Init "wikilink") was called. READ ONLY
  | **WORD** ActiveConnections           - Number of currently active Connections; this does not include ListenConnections. READ ONLY
  | **WORD** ActiveListenPorts           - Number of currently active ListenConnections. READ ONLY
  | **BYTE** ConsoleReports              - [true](true "wikilink")/*[false](false "wikilink")*: whether general messages should be displayed in the console. READ/WRITE
  | **BYTE** ReturnNETDLLCommands        - [true](true "wikilink")/*[false](false "wikilink")*: whether Network.DLL commands are visible to Fenix/Bennu. READ/WRITE **Deprecated**
  | **INT** totaltransferrate\_up        - The number of bytes sent this frame by all connections. READ ONLY
  | **INT** totaltransferrate\_down      - The number of bytes received this frame by all connections. READ ONLY
  | **INT** totaltransferred\_up         - The total number of bytes sent by all connections. READ ONLY
  | **INT** totaltransferred\_down       - The total number of bytes received by all connections. READ ONLY
  | **INT POINTER** transferrate\_up     - The number of bytes sent this frame by a connection. READ ONLY
  | **INT POINTER** transferrate\_down   - The number of bytes received this frame by a connection. READ ONLY
  | **INT POINTER** transferred\_up      - The total number of bytes sent by a connection. READ ONLY
  | **INT POINTER** transferred\_down    - The total number of bytes received by a connection. READ ONLY
  -------------------------------------- -------------------------------------------------------------------------------------------------------------------------------------------

### Pointers

To the **int pointers** in the NET struct applies the following:

-   they point to an array with number of elements equal to
    `NET.MaxConnections`;
-   each element contains data regarding one connection;
-   every connection has a NetID and this NetID corresponds with the
    position in the array (so for example for the NetID n:
    NET.Status\[n\] works).

### Incoming/Status

To the incoming array the following status codes apply:
NET\_STATUS\_DISCONNECTED, NET\_STATUS\_INACTIVE, NET\_STATUS\_ACTIVE,
NET\_STATUS\_CONNECTED.

To the status array the following status codes apply:
NET\_STATUS\_DISCONNECTING, NET\_STATUS\_DISCONNECTED,
NET\_STATUS\_INACTIVE, NET\_STATUS\_CONNECTED, NET\_STATUS\_CONNECTING.

The status array tells the current status of each connection, while the
incoming array tells the change of status of each connection. For
example, if a connection would disconnect, the element of the incoming
array of that connection would become NET\_STATUS\_DISCONNECT for one
cycle and then become NET\_STATUS\_INACTIVE.

For the incoming array:

-   NET\_STATUS\_DISCONNECTED lasts one cycle
-   NET\_STATUS\_INACTIVE lasts until a different status is valid
-   NET\_STATUS\_ACTIVE lasts one cycle
-   NET\_STATUS\_ESTABLISHED lasts one cycle

[Category:global variables](Category:global_variables "wikilink")
<Category:networkdll> <Category:dll>
