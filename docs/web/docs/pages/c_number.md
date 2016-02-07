<category:variables> <category:predefined> [category:local
variables](category:local_variables "wikilink") <category:libscroll>
<category:librender>

[**Up to Local Variables**](Local_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

The cnumber is variable that is used when there's more then one
[scroll](scroll "wikilink") or [Mode7](Mode7 "wikilink") window active,
i.e. in a splitscreen configuration with two or more scroll or mode7
windows.

The cnumber indicates in wich window(s) the process is visible. It is
only necessary for processes that are intended to visible in a scroll or
mode7 window. The default value is 0, wich means that the process is
visible in all scroll or mode7 windows. Up to 10 scroll or mode7 windows
can be defined, wich are numbered from 0 to 9, wich are enumerated by
the predefined constants [C\_0](C_0 "wikilink"), [C\_1](C_1 "wikilink"),
[C\_2](C_2 "wikilink"), [C\_3](C_3 "wikilink"), [C\_4](C_4 "wikilink"),
[C\_5](C_5 "wikilink"), [C\_6](C_6 "wikilink"), [C\_7](C_7 "wikilink"),
[C\_8](C_8 "wikilink") and [C\_9](C_9 "wikilink").

The cnumbers can be added, and the sum of these indicate the visibility.
If there, are for instance 4 scroll windows active, (numbered 0, 1, 2,
and 3) and a specific process should only be visible in windows 0 and 2,
then you should use:

    cnumber = C_0 + C2; // this is 1+4

It is possible to change the value of the cnumber in runtime, wich can
be handy in certain situations.

Look for more information about scrolls and mode7 in the articles of the
[Start\_scroll](Start_scroll "wikilink")() and
[Start\_mode7](Start_mode7 "wikilink")() functions.
