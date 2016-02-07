<category:variables> <category:predefined> [category:local
variables](category:local_variables "wikilink") <category:librender>

[**Up to Local Variables**](Local_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** flags = 0

Flags is a predefined [local variable](local_variable "wikilink") which
is used to manipulate how the [graphic](graphic "wikilink") of a
[process](process "wikilink"), assigned to its local variable
[graph](graph "wikilink"), is displayed.

To alter the effect, change the value of this local variable by
assigning it [blit flags](blit_flags "wikilink"). Like most [bit
flags](bit_flags "wikilink"), constants can be added together to combine
effects. A horizontally mirrored translucent graphic would need flags
B\_TRANSLUCENT (4) and B\_HMIRROR (1), so flags =
B\_TRANSLUCENT|B\_HMIRROR (5) will do the trick.

Example
-------

To make the graphic of a process spin:

    Program mirror
    Begin
        mirror_graphic();
        Loop
            frame;
        End
    End
    Process mirror_graphic()
    Begin
        graph = new_map(50,50,8);
        map_clear(0,graph,rgb(0,255,255));
        x = 100;     //Position the graphic 100 pixels
        y = 100;     //from the top and left of the screen
        Loop
            if (key(_l))
                flags = B_HMIRROR; //if you press the L key, your graphic is horizontally mirrored
            else
                flags = 0;
            end       
            frame;
        End
    End

The process will mirror its graphic when the key L is held down.
