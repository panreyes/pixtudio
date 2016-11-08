Syntax
------

```pixtudio-syntax
Function <returntype> <name> ( [ <parameters> ] )
[ Public
   [ <public variables> ]
End ]
[ Private
   [ <private variables> ]
End ]
Begin
   [ <function code> ]
[ OnExit
   [ <exit code> ]
]
End
```

Description
-----------

Function is a reserved word used to start the code of a function.

A function is a [subroutine](#subroutine) to which one or more
of the following apply:

-   it receives [parameters](#parameter)
-   it acts on the parameters
-   it processes data located elsewhere
-   it [returns](#return) a [value](#value)

The difference between a function and a [process](#process) is
that the calling process or function waits until the function is
completed. When a process or function calls a process, it doesn't wait.
This means that, even when the called function contains
[frame](#frame) statements, the calling function or process
still waits for the function to finish. This is shown in [this
tutorial](Tutorial:#Textinput).

Example
-------

```
    Function int addInts( int a , int b )
    Private // Declare private variables here
    Begin // Start the main functioncode
        return a+b;
    End // End the main functioncode
```

`addInts(3,6);` will return 9. One can see that the function does indeed:

-   receive parameters.
-   act on the parameters.
-   return a value.
