[**Up to Network.DLL**](Networkdll "wikilink")

------------------------------------------------------------------------

Here is a list of all the errorcodes regarding
[Network.DLL](Network_DLL "wikilink").

Catching errorcodes is very easy: just check if the return value is
negative, then it is an error.

    result = NET_Xxx();
    if(result<0)
        say("NET Error: " + NET_GetError(result));
    else
        // success
    end

  ------------------------------- ----------------------------------------------------
  *Constant*                      - *Description*
  NET\_ERROR\_NONE                - No error.
  NET\_ERROR\_INITIALIZATION      - Error during initialization.
  NET\_ERROR\_NOTINITIALIZED      - Network.DLL not initialized. Depecrated.
  NET\_ERROR\_INVALIDADDRESS      - Invalid IP address. Deprecated.
  NET\_ERROR\_RESOLVINGHOST       - Could not resolve host.
  NET\_ERROR\_ALLOCSOCKETSET      - Could not allocate socketset. Deprecated.
  NET\_ERROR\_INVALIDSOCKETSET    - The socketset is invalid.
  NET\_ERROR\_SOCKETSETINACTIVE   - The socketset is inactive.
  NET\_ERROR\_ADDINGSOCKET        - Could not add socket to socketset.
  NET\_ERROR\_INVALIDSOCKETSET    - The socketset is invalid.
  NET\_ERROR\_DELETINGSOCKET      - Could not delete the socket.
  NET\_ERROR\_CONNECTING          - Could not connect.
  NET\_ERROR\_INVALIDCONN         - The connection is invalid.
  NET\_ERROR\_CONNINACTIVE        - The connection is inactive.
  NET\_ERROR\_LISTENINGONCONN     - Could not listen on connection.
  NET\_ERROR\_TOOMANYCONNS        - There are too many connections
  NET\_ERROR\_TOOFEWCONNS         - Too small number of maximum connections
  NET\_ERROR\_INVALIDTYPE         - The type specified is invalid.
  NET\_ERROR\_ALREADYINIT         - Network.DLL already initialized.
  NET\_ERROR\_MESSAGETOOLONG      - The message is too long.
  NET\_ERROR\_MESSAGETOOSHORT     - The message is too short.
  NET\_ERROR\_OUTGOINGSTACKFULL   - Outgoing Message stack is full.
  NET\_ERROR\_INCOMINGSTACKFULL   - Incoming Message stack is full.
  NET\_ERROR\_SENDING             - Could not send message.
  NET\_ERROR\_RECEIVING           - Could not receive message.
  NET\_ERROR\_DISCONNECTING       - Could not close connection.
  NET\_ERROR\_DISCONNECTED        - Connection was closed.
  NET\_ERROR\_TOOMANYLISTENERS    - Too many listenports specified.
  NET\_ERROR\_INVALIDPORTNUMBER   - The portnumber is invalid (&lt;0 or &gt;65535).
  NET\_ERROR\_SIZEMISMATCH        - Integral size mismatch.
  NET\_ERROR\_RESOLVINGIP         - Could not resolve IP.
  NET\_ERROR\_NONEXTERNALCONN     - Non-external connection. Deprecated.
  NET\_ERROR\_NONEWMESSAGE        - The incomingbuffer is empty.
  NET\_ERROR\_UNFINISHEDMESSAGE   - The message in the incomingbuffer is incomplete.
  NET\_ERROR\_NULLPOINTER         - NULL pointer exception.
  NET\_ERROR\_NONEXISTINGGRAPH    - The graph does not exist.
  NET\_ERROR\_NONEXISTINGFILE     - The file does not exist.
  NET\_ERROR\_CREATINGGRAPH       - Could not create graph.
  NET\_ERROR\_OPENINGFILE         - Could not open file.
  ------------------------------- ----------------------------------------------------

<Category:errorcodes> <Category:networkdll> <Category:dll>
