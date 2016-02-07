<category:precompiler>

Definition
----------

**\#define** <what to define> \[<what it will be>\]

Defines *what to define* as *what it will be*. This means that after
this line, all *what to define*s will be "replaced" by *what it will
be*.

You can also create "functions" with this, even with parameters. The
call to this "function", including parameters, will be replaced by the
*what it will be* section, with the parameters replaced by the
arguments.

Example
-------

### Basic statements

In the following example, we'll show it is possible to define words as
"being" [basic statements](basic_statements "wikilink").

    #define StartThisShow Program
    #define GimmeSomeShit Process

    StartThisShow example;
    Begin
        proc();
    End

    GimmeSomeShit proc()
    Begin
    End

Used in example: [Program](Program "wikilink"),
[Process](Process "wikilink"), [Begin](Begin "wikilink"),
[End](End "wikilink")

### Error codes

Error codes are handy as well, like used in
[Network.DLL](Network.DLL "wikilink") and [LCD.DLL](LCD.DLL "wikilink"):

    #define NET_ERROR_INVALIDADDRESS -12

This will enable the use of *NET\_ERROR\_INVALIDADDRESS* as it it were
the value *-12*. This makes it much more clear for the programmer what
the errors are. Consider this:

    #define NET_STATUS_ESTABLISHED 2

The value *2* on itself means very little, but
*NET\_STATUS\_ESTABLISHED* immediately makes it clear what it means.

### Function

In the following we define a function
*kill(<int processID|processTypeID>,<string reason>)*.

    #define kill(a,b) if(exists(a)) signal(a,s_kill); say("Killed '" + a + "' for reason: " + b); end
    Program example;
    Private
        int i;
    Begin
        i = proc();
        kill(i,"It had to be killed!"); // The ';' is not needed per se, but is allowed.
        Repeat
            frame;
        Until(key(_ESC))
    End
    Process proc()
    Begin
        Loop
            frame;
        End
    End

Used in example: [Program](Program "wikilink"),
[Process](Process "wikilink"), [Begin](Begin "wikilink"),
[End](End "wikilink"), [If](If "wikilink"), [Repeat](Repeat "wikilink"),
[Until](Until "wikilink"), [frame](frame "wikilink"),
[signal](signal "wikilink")(), [say](say "wikilink")(),
[key](key "wikilink")()
