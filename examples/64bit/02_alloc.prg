import "mod_mem"
import "mod_say"

Process Main()
Private
    byte* pbyte;
    word* pword;
    int* pint;
    int elements = 10;
    int i;
Begin

    // Allocate memory
    pbyte = alloc(elements);
    pword = alloc(elements*sizeof(*pword)); // note the sizeof() here, this is possible!
    pint  = alloc(elements*sizeof(int));

    // Reset memory to 0's
    memset (pbyte,0,elements);
    memsetw(pword,0,elements); // same as  memset(pword,0,elements*sizeof(word));
                               // because value-parameter is 0.
    memseti(pint ,0,elements); // same as  memset(pint,0,elements*sizeof(int));
                               // because value-parameter is 0.

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

OnExit

    // Free the used memory
    free(pbyte);
    free(pword);
    free(pint);

End