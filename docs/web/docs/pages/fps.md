<category:general> <category:variables> <category:predefined>
[category:global variables](category:global_variables "wikilink")
<category:librender>

[**Up to Global Variables**](Global_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** fps

The [global variable](global_variable "wikilink") [fps](fps "wikilink")
holds the current frames per second on which [Bennu](Bennu "wikilink")
is running. This means how many times a frame is executed every second
and how many times the screen is updated every second.

If a different FPS is needed, the target FPS can be altered by use of
[set\_fps](set_fps "wikilink")().

If a more accurate FPS is needed, use
[frame\_time](frame_time "wikilink") to calculate it.

If you need to view the FPS in-game, please use the code (in a loop):
write\_int(0,0,0,0,&fps);
