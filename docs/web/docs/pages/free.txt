Definition
----------

**INT** free ( &lt;**VOID POINTER** data&gt; )

Frees a block of memory.

The pointer used must be a pointer to a previously allocated block of
memory, else the behavior of free() is undefined.

Also called [mem\_free](mem_free "wikilink")().

Parameters
----------

  ----------------------- -----------------------------------------------
  **VOID POINTER** data   - Pointer to the block of memory to be freed.
  ----------------------- -----------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Example
-------

    Program example;
    Private
        byte pointer pbyte;
        word pointer pword;
        int  pointer pint;
        int elements = 10;
        int i;
    Begin

        // Allocate memory
        pbyte = alloc(elements);
        pword = alloc(elements*sizeof(word));
        pint  = alloc(elements*sizeof(int));

        // Reset memory to 0's
        memset (pbyte,0,elements);
        memsetw(pword,0,elements); // same as  memset(pword,0,elements*sizeof(word));
                                   // because value-parameter is 0.
        memset (pint ,0,elements*sizeof(int)); // There isn't a "memseti()", so we need to
                                               // set the individual bytes to 0. To change
                                               // ints to nonzero values, memset() can't be
                                               // used easily

        // Write numbers to bytes and ints
        for(i=0; i<elements; i++)
            pbyte[i]  = 133; // pbyte[i] is the same as *(pbyte+i)
            *(pint+i) = 4555; // pint[i] is the same as *(pint+i)
        end

        // Write numbers to words
        memsetw(pword,345,elements);

        // Show numbers
        for(i=0; i<elements; i++)
            say("byte["+i+"] = " + *(pbyte+i));
            say("word["+i+"] = " + pword[i]);
            say("int ["+i+"] = " + pint[i]);
        end

        Repeat
            frame;
        Until(key(_esc))

        // Free the used memory
        free(pbyte);
        free(pword);
        free(pint);

    End

Used in example: [alloc](alloc "wikilink")(),
[memset](memset "wikilink")(), [memsetw](memsetw "wikilink")(),
[sizeof](sizeof "wikilink")(), [say](say "wikilink")(),
[free](free "wikilink")(), [pointer](pointer "wikilink")

<Category:functions> <Category:memory> <Category:mod_mem>
