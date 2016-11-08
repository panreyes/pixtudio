Syntax
------

**Debug** **;**

Description
-----------

`Debug` is a reserved word used to tell [PixTudio](#PixTudio) to go
into debug mode, only if the [DCB](#DCB) was compiled with
debug information ([compiler](#pxtb) option `-g`). If the
module [mod_debug](#mod_debug) was imported as well, the
console is immediately invoked and one can begin tracing from the debug
statement.

[Here](#debugging)'s a handy page about debugging a Bennu
program.

Example
-------

```
    Function int debug_warning(string warning)
    Begin
        say("Warning: " + warning);
        debug;
        return 0;
    End
```

Used in example: [say](#say)(), [debug](#debug)
