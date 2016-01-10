Syntax
------

**INT** memset ( &lt;**VOID POINTER** data&gt; , &lt;**BYTE** value&gt;
, &lt;**INT** bytes&gt; )

Description
-----------

Sets all bytes in the specified memory block to the specified value.

Also called [mem\_set](mem_set "wikilink")().

Parameters
----------

  ----------------------- -------------------------------------------
  **VOID POINTER** data   - Pointer to the block of bytes in memory
  **BYTE** value          - Value to set all bytes to.
  **INT** bytes           - Number of bytes to change the value of.
  ----------------------- -------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Example
-------

See [alloc](alloc "wikilink")().

Also useful in conjunction with [map\_buffer](map_buffer "wikilink")()
with 8bit [maps](map "wikilink"). (*Example can be found in the
map\_buffer article.*)

<Category:functions> <Category:memory> <Category:mod_mem>
