Syntax
------

**INT** memseti ( &lt;**VOID POINTER** data&gt; , &lt;**INT** value&gt;
, &lt;**INT** ints&gt; )

Description
-----------

Sets all [ints](int "wikilink") in the specified memory block to the
specified value.

Also called [mem\_seti](mem_seti "wikilink")().

Parameters
----------

  ----------------------- -------------------------------------------
  **VOID POINTER** data   - Pointer to the block of ints in memory.
  **INT** value           - Value to set all ints to.
  **INT** ints            - Number of ints to change the value of.
  ----------------------- -------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Example
-------

See [alloc](alloc "wikilink")().

Also useful in conjunction with [map\_buffer](map_buffer "wikilink")()
with 32bit [maps](map "wikilink"). (*Example needed.*)

<Category:functions> <Category:memory> <Category:mod_mem>
