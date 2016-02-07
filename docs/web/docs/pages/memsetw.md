Syntax
------

**INT** memsetw ( &lt;**VOID POINTER** data&gt; , &lt;**WORD** value&gt;
, &lt;**INT** words&gt; )

Description
-----------

Sets all words in the specified memory block to the specified value.

Also called [mem\_setw](mem_setw "wikilink")().

Parameters
----------

  ----------------------- --------------------------------------------
  **VOID POINTER** data   - Pointer to the block of words in memory.
  **WORD** value          - Value to set all words to.
  **INT** words           - Number of words to change the value of.
  ----------------------- --------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Example
-------

See [alloc](alloc "wikilink")().

Also useful in conjunction with [map\_buffer](map_buffer "wikilink")()
with 16bit [maps](map "wikilink"). (*Example needed.*)

<Category:functions> <Category:memory> <Category:mod_mem>
