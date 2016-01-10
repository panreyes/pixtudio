Definition
----------

**INT** memcmp ( &lt;**VOID POINTER** ptr1&gt; , &lt;**VOID POINTER**
ptr2&gt; , &lt;**INT** number&gt; )

Compares the first *number* bytes of the block of memory pointed by
*ptr1* to the first *number* bytes pointed by *ptr2*, returning zero if
they all match or a value different from zero representing which is
greater if they do not.

Also called [mem\_cmp](mem_cmp "wikilink")().

Parameters
----------

  ----------------------- --------------------------------------
  **VOID POINTER** ptr1   - Pointer to a block of memory
  **VOID POINTER** ptr2   - Pointer to a block of memory.
  **INT** number          - The number of bytes to be checked.
  ----------------------- --------------------------------------

Returns
-------

**INT** : Difference

  ------- ---------------------------------------------------------------------------------
  0       - The blocks of memory are identical.
  &gt;0   - The first differing byte in both memory blocks has a greater value in *ptr1*.
  &lt;0   - The first differing byte in both memory blocks has a greater value in *ptr2*.
  ------- ---------------------------------------------------------------------------------

A byte ranges from 0 to 255, meaning 189 is a greater value than 105.

Example
-------

    Program example;
    Const
        elements = 10;
    End
    Private
        byte pointer pbyte1;
        byte pointer pbyte2;
        int result;
    End
    Begin

        // Allocate memory
        pbyte1 = alloc(elements);
        pbyte2 = alloc(elements);

        // Make the blocks the same and compare
        memset(pbyte1,3,elements);
        memset(pbyte2,3,elements);
        result = memcmp(pbyte1,pbyte2,elements); // You can also compare the first 5 bytes,
                                                 // or the first elements/2 bytes, it
                                                 // depends on what you want.
        say("Memcmp 1: " + result);

        // Make the first block have a greater value and compare
        pbyte1[0] = 4;
        result = memcmp(pbyte1,pbyte2,elements);
        say("Memcmp 2: " + result);

        // Make the blocks the same and compare
        pbyte2[0] = 4;
        result = memcmp(pbyte1,pbyte2,elements);
        say("Memcmp 3: " + result);

        // Make the first block have a greater value and compare
        pbyte2[1] = 5;
        result = memcmp(pbyte1,pbyte2,elements);
        say("Memcmp 4: " + result);

        Repeat
            frame;
        Until(key(_esc))

        // Free the used memory
        free(pbyte1);
        free(pbyte2);

    End

Used in example: [alloc](alloc "wikilink")(),
[memset](memset "wikilink")(), [memcmp](memcmp "wikilink")(),
[say](say "wikilink")(), [free](free "wikilink")(),
[pointer](pointer "wikilink")

<Category:functions> <Category:memory> <Category:mod_mem>
