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

    say(pbyte);

    // Set numbers
    for(i=0; i<elements; i++)
        bytearray[i] = i;
    end

    // Copy bytes to bytearray
    memcopy(pbyte, &bytearray[0], elements);

    // Show numbers
    for(i=0; i<elements; i++)
        say("byte["+i+"] = " + pbyte[i]);
    end

OnExit

    // Free the used memory
    free(pbyte);

End