Syntax
------

```
include "{filename}"
```

Description
-----------

When the compiler reaches an `include` statement, it
continues compilation at the included file and when it's 
done resumes compiling from the statement right after the `include`.
In other words, these files contain code that gets inserted 
at the place of inclusion.

This is very handy for breaking up your code into pieces. The handling
of video in one include file, audio in another, game logic in another,
etc. This makes code more maintainable and understandable; moreover it
makes code reusable. The video handling include file you made for one
game can be used for another game (if it was coded in a generic fashion)
without spitting through the whole sourcecode of the first game.

Also headers can be used to import [modules](#modules) and possibly
give a little more functionality to that module.

Example
-------

**main.prg**
```
    // The code in "bar.inc" will be inserted here:
    include "bar.inc"

    import "mod_say"

    Process Main()
    Private
        int barcode;
    Begin
        barcode = bar();
        say(barcode);
    End  
```

**bar.inc**
```
    import "mod_rand"

    Function int bar()
    Begin
        return rand(0,10);
    End
```

Used in example: [include](#include),
[import](#import), [write_int](#write_int)(),
[key](#key)()
