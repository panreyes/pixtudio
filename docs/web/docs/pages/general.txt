Guide: Porting to your chosen system
------------------------------------

This is a general guide for getting your Bennu game onto your chosen
system.

''' *If you have missed the front page of this Wiki please see*
*[Bennu\_Wiki](http://wiki.bennugd.org/index.php?title=Bennu_Wiki) or
click on the BennuWiki logo on the top left of this page.* '''

At the time of writing this stable ports and porting processes exist for
these OS or platforms:

:   Windows
:   Linux
:   Caanoo (a later GP2X type handheld)
:   GP2X Wiz
:   Dingux (Dingoo OS for handheld)

The rest are generally unsupported by BennuGD community but still quite
possible:

:   Playstation 2
:   HTML5/Chrome Native Client
:   Dreamcast
:   Haiku OS
:   FreeBSD
:   MacOS X (Intel 32 bits)
:   BennuGD PPA for Ubuntu 32 bits
:   Nintendo Wii
:   PSP
:   Pandora
:   Xbox
:   Motorola linux phone (RU)

Another exciting development is - BennuGD is being ported to:

:   Android

Expect this to be added to the "unsupported" section list very soon.

**Essential: Check out [Downloads](http://bennugd.org/node/2) page for
BennuGD.**

**You can read about current developments on any ports at bennugd.org
main page in the frontpage [News](http://bennugd.org) feed.**

Starting Out
------------

If you have some experience with BennuGD you will have used bgdc (the
compiler) and bgdi (the interpreter).

Once you have downloaded the Bennu port for your chosen target platform
you will find it includes bgdc.xxx and bgdi.xxx. The compiler is the
part that talks to the the machine, making your bennu code into a .dcb
that is usable when executed with the interpreter. Also depending on
which port, you will also find the set of standard libraries for the
specific machine, or not. With bennu-monolithic ports you may find the
libraries are not present as seperate files.

'' **bennugd-monolithic** - Many of recent ports are part of the
bennugd-monolithic project, which enables certain machines to run Bennu
successfully, including **Wii, PSP iOS and Android.** See josebita's
[bennugd-monotlithic](http://code.google.com/p/bennugd-monolithic/)
Google Code pages for information about this.''

So if you haven't done so, see the
[Downloads](http://bennugd.org/node/2) page of bennugd.org and retrieve
the relevant port for your system - (checking that you are downloading
the latest version!)

Notes on Setting Up
-------------------

Porting is quite a task sometimes. You may find you need to edit your
source code, depending on requirements of the target system and the
current state of the port you are using. This can be related to sound or
display requirements for example. Sometimes you can find your game may
not run fast enough and needs optimisation - the target system can be
slower than the computer you originally wrote the game for. However this
should be only attempted after testing your game! So read on!

Also some preparation work is desired in your game source for the
peripherals (controls) of the console or platform, so a good idea is to
ascertain what controls you will be using early on. There is a section
on this next in the guide!

The other part of porting is getting **the machine you want to run your
Bennu game on to actually compile the game itself.** This can be an easy
process or rather tough. But you will find certain tools written by
developers who have paved the way before you will make this infinitely
easier.

Most of all DON'T GIVE UP. You may find once your game compiles
successfully with bgdc and you have a .dcb ready, there may be runtime
errors when running and playing your game (with bgdi).

Once you have filesystem specifics set up for your chosen platform, the
thing to remember is the standard commandline process which must be
performed on the machine you intend to run your game on:

`bgdc.xxx [params] bennugame.prg`

Which naturaly takes your code and builds a dcb of your program.

`bgdi.xxx bennugame.dcb`

This will run your program.

Note: Most testing scenarios will not require you to use parameters in
the compilation of your game/program.

However, one common parameter used is -a which automatically packages
your commonly used resources - for example FPGs, WAVs into the dcb. This
is optional for you of course, but can be very beneficial. When
distributing your game or homebrew, people will not see your resource
files and can help protect them from further use.

For further information on compile parameters you can ask bgdc itself:

`bgdc.xxx -help`

Which prints a list of parameters and a description of their uses.
'''Disclaimer: *Be careful with these! They can sometimes crash your
console or any equipment used!* '''

For any platform specific questions I will direct you to the bennugd.org
community boards for each supported platform.
[Here](http://forum.bennugd.org/index.php?board=80.0) you can post
questions or search for answers. (This is for more advanced or searching
questions about each particular console/machine).
