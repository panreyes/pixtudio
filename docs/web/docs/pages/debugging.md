Debugging a [Bennu](Bennu "wikilink") program can be tricky. So here are
a few tips to get you on your way.

Debug mode
----------

To run a game in debug mode, you have to import the debug
module("mod\_debug") and to compile the .prg with the -g option (e.g.
`bgdc.exe -g name.prg`). Then when you run the game, it is in debug
mode. In this there's a number of shortcuts, with a variety in
usefulness.

### Shortcuts

  ------- ----------------------------------------------------------------------------------------------------------
  ALT-C   - Show/hide the [Bennu console](Bennu_console "wikilink").
  ALT-F   - Go into fullscreen mode.
  ALT-G   - Make a screenshot and save it as `shotXXXX` where `XXXX` is the lowest possible number.
  ALT-P   - Show/hide the [Bennu profiler](Bennu_profiler "wikilink")
  ALT-R   - Resets the profile history of the Bennu Profiler.
  ALT-S   - Activate/Deactivate the Bennu Profiler.
  ALT-W   - Go into window mode.
  ALT-X   - Exit.
  ALT-Z   - Switch the [MODE\_16BITS](MODE_16BITS "wikilink") flag of [graph\_mode](graph_mode "wikilink") on/off.
  ------- ----------------------------------------------------------------------------------------------------------

Bennu Console
-------------

The [Bennu console](Bennu_console "wikilink") is a pretty handy
debugging tool. You can view all active [processes](process "wikilink"),
view values of any variable, perform one instruction, perform one frame,
manage breakpoints on processes, manage processes, etc. A sure go for
debugging.

Bennu Profiler
--------------

The [Bennu profiler](Bennu_profiler "wikilink") is somewhat handy,
mostly for tracing where a program is the most power hungry.

<Category:general> <Category:debugging>
