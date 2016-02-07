Definition
----------

A ProcessTypeID is a unique identification code, for a
[processType](processType "wikilink"). A ProcessTypeID is smaller than
65536 (2\^16).

Example
-------

Kill all SpaceShip()s (see [process](process "wikilink")):

    Begin
        signal(type SpaceShip,s_kill);
    End

[signal](signal "wikilink")() signals all
[processes](process "wikilink") of [processType](processType "wikilink")
SpaceShip the [signal](signals "wikilink") to [die](die "wikilink").
This is done by using the [constant](constant "wikilink")
[s\_kill](s_kill "wikilink") as the signal.

<Category:general>
