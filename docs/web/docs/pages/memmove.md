Definition
----------

**INT** memmove ( &lt;**VOID POINTER** destination&gt; , &lt;**VOID
POINTER** origin&gt; , &lt;**INT** size&gt; )

Copies a certain number of [bytes](byte "wikilink") from one point in
[memory](memory "wikilink") to another.

Difference between [memmove](memmove "wikilink")() and
[memcopy](memcopy "wikilink")() is that the first one can be used if the
destination section and origin section overlap. With
[memcopy](memcopy "wikilink")(), this can go wrong, though some systems
make [memcopy](memcopy "wikilink")() safe too.

Also called [mem\_move](mem_move "wikilink")().

Parameters
----------

  ------------------------------ -------------------------------------------------
  **VOID POINTER** destination   - Pointer to the first byte of the destination.
  **VOID POINTER** origin        - Pointer to the first byte of the origin.
  **INT** size                   - The size of the to be copied memory in bytes.
  ------------------------------ -------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Example
-------

    import "mod_mem"
    import "mod_say"

    Const
        elements = 5;
    End

    Process Main()
    Private
        byte bytearray[elements-1];
        byte* pbyte;
        int i;
    End
    Begin

        // Allocate memory
        pbyte = alloc(elements);

        // Set numbers
        for(i=0; i<elements; i++)
            bytearray[i] = i;
        end

        // Copy bytes to bytearray
        memmove(pbyte,&bytearray[0],elements);

        // Show numbers
        for(i=0; i<elements; i++)
            say("byte["+i+"] = " + pbyte[i]);
        end

    OnExit

        // Free the used memory
        free(pbyte);

    End

Used in example: [alloc](alloc "wikilink")(),
[memmove](memmove "wikilink")(), [say](say "wikilink")(),
[free](free "wikilink")(), [array](array "wikilink"),
[pointer](pointer "wikilink")

<Category:functions> <Category:memory> <Category:mod_mem>
