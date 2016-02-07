Syntax
------

**Debug** **;**

Description
-----------

Debug is a reserved word used to tell [Bennu](Bennu "wikilink") to go
into debug mode, only if the [DCB](DCB "wikilink") was compiled with
debug information ([compiler](bgdc "wikilink") option `-g`). If the
module [mod\_debug](mod_debug "wikilink") was imported as well, the
console is immediately invoked and one can begin tracing from the debug
statement.

[Here](Debugging "wikilink")'s a handy page about debugging a Bennu
program.

Example
-------

    Function int debug_warning(string warning)
    Begin
        say("Warning: " + warning);
        debug;
        return 0;
    End

Used in example: [say](say "wikilink")(), [debug](debug "wikilink")

<Category:reserved> <Category:language> [Category:Basic
statement](Category:Basic_statement "wikilink")