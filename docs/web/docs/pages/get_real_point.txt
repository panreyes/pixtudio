Definition
----------

**INT** get\_real\_point( &lt;**INT** controlpoint&gt; , &lt;**INT
POINTER** x&gt; , &lt;**INT POINTER** y&gt; )

Finds the actual position on the screen of the calling
[process](process "wikilink"), given its [graphic](graphic "wikilink")
and the specified *[controlpoint](controlpoint "wikilink")* on this
graphic. All process-related variables are taken into account, like
[x](x "wikilink"), [y](y "wikilink"), [angle](angle "wikilink"), even
[ctype](ctype "wikilink"). These coordinates are then assigned to the
variables pointed to by *x* and *y*.

Parameters
----------

  ---------------------- ---------------------------------------------------------------------------------------------------------------
  **INT** controlpoint   - The [controlpoint](controlpoint "wikilink") on the process' graphic of which the actual position is wanted.
  **INT POINTER** x      - A pointer to an integer to which the X-coordinate will be assigned.
  **INT POINTER** y      - A pointer to an integer to which the Y-coordinate will be assigned.
  ---------------------- ---------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : Successrate

  --------------------------- --------------------------------------------
  [false](false "wikilink")   - Error: no graphic; invalid controlpoint;
  [true](true "wikilink")     - Success.
  --------------------------- --------------------------------------------

<Category:functions> <Category:processinteraction> <Category:mod_grproc>
