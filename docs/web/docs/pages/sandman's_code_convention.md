Fenix/Bennu Code Convention by Sandman (work in progress)

Indenting and Blank Lines
-------------------------

Indenting is done with four spaces or a tab of four spaces wide. The
[Program](Program "wikilink")-, [Process](Process "wikilink")-,
[Function](Function "wikilink")-, [Global](Global "wikilink")-,
[Local](Local "wikilink")-, [Public](Public "wikilink")-,
[Private](Private "wikilink")- and [Begin](Begin "wikilink")-statements
are always completely to the left, with no indentation at all. The
exception to this is inside the [Declare](Declare "wikilink") block, in
which case [Public](Public "wikilink") and [Private](Private "wikilink")
are indented once. Declaration of variables are indented once.
Precompiler-statements are generally to the left as well, but for small
blocks they can be indented. The code between Begin and
[End](End "wikilink") statements are indented once at first.

The use of blank lines doesn't matter, but its use may improve
readability, so try to keep it in mind.

See the example for a visual representation.

Names
-----

Separating sections of a name is done by use of the underscore ("\_")
character. An easy example is the [function](function "wikilink")
[NET\_Init](NET_Init "wikilink"). "NET" is a different section than
"Init", because the first denotes the origin of the function and the
second denotes what the function does. Another example is
[NET\_ERROR\_CONNECTING](NET_ERROR_CONNECTING "wikilink"): "NET" denotes
the origin, "ERROR" denotes a more precise origin (an error) and
"CONNECTING" denotes what the constant means (error while connecting).

Separating some words with an underscore ("\_") is not needed, but can
simply be put together, making the first character of the second word a
capital. For example [NET\_SendVar](NET_SendVar "wikilink"). Here we see
the section "NET" and the section "SendVar", which is further cut down
to "Send" and "Var". First sections denoting the origin are typed in
capitals, while the other sections only begin with a capital.

Both Fenix and Bennu have the convention to mostly use an underscore
("\_") in names, so this is allowed too. It's more a matter of taste
than practicality: `int numberOfProcessesAlive;` versus
`int number_of_processes_alive`.

### Constants

Constants are written in all uppercase.

Like: [C\_SCREEN](C_SCREEN "wikilink"),
[NET\_ERROR\_CONNECTING](NET_ERROR_CONNECTING "wikilink"),
[B\_ALPHA](B_ALPHA "wikilink")

### Variables

Variables are written in mostly lowercase, whether they are private,
public, local or global. When defining a [struct](struct "wikilink"),
the name of the struct start with a capital and is accessed with a
capital as well. For example "Mouse.left". "Mouse" is a struct, so it's
typed with a capital and "left" is a normal variable, so it's in
lowercase.

The [datatype](datatype "wikilink") of the variables are *always* noted
when declaring them, even when they're integers.

Like: [ctype](ctype "wikilink"), [graph\_mode](graph_mode "wikilink"),
[Scroll](Scroll "wikilink"), numberOfProcessesAlive

### Types

Types are written in both cases, but mostly in lowercase. A type starts
with an underscore ("\_") or with a capital.

Like: [Network.dll](Network.dll "wikilink") has the type "\_IPaddress",
\_point, Point

### Defines

Defines are, like constants, written in all uppercase. On top of this,
the following way of defining can be used, to prevent multiple includes
of the same file. Note the "\_\_".

    #ifndef __MYFILENAME_MYFILEEXTENSION
    #define __MYFILENAME_MYFILEEXTENSION
    // Place the file's code here.
    #endif

This is done in [Network.dll](Network.dll "wikilink"):

    #ifndef __NETWORK_BH
    #define __NETWORK_BH
    // Network.fh code
    #endif

### Functions and Processes

Functions are written in both cases. Defining a function or process goes
like so:

    keyInput( int keycode, int pointer status)

The opening parenthesis ("(") comes directly after the function name,
followed by a space (" ") and the [datatype](datatype "wikilink") of the
first parameter, before a space and the name of the first parameter.
Then a comma (",") and the whole thing starts again, ending with a
closing parenthesis (")").

Processes start with a capital, both in the declaration and when
calling.

Calling functions and processes
-------------------------------

Calling a function or process isn't bound to any rules, because in many
cases, the clarity of the code is different, even though the code is
written the same. So just best suit the layout of the code to the
environment. In general though, a good look is created by the use of a
space (" ") before every [argument](argument "wikilink").

Control-flow keywords
---------------------

Control-flow keywords can be typed in two ways. The difference denotes
the importance of the statement. The important control-flow statements
are typed with the first character a capital, while the less important
ones are only lowercase.

Example
-------

    import "mod_key"
    import "mod_wm"
    import "mod_proc"

    Const
        KEY_TARGET = _A;
    End

    Global
        int keyPressed;
    End

    Process KeyInput( int keycode, int pointer status)
    Begin
        Loop
            if(key(keycode))
                *status = TRUE;
            else
                *status = FALSE;
            end
            frame;
        End
    End

    Process Main()
    Private
        KeyInput keyInput;
    Begin
        keyInput = KeyInput(KEY_TARGET, &keyPressed);
        Repeat
            if(keyPressed)
                say("Key pressed!");
            end
            frame;
        Until(exit_status)
    OnExit
        signal(keyInput, S_KILL);
    End