Description
-----------

A parameter is the [variable](#variable) and its
[value](#value) inside the definition of a
[function](#function) or [process](#process) that is
received from the [calling](#function_call) environment. The
value passed on when calling the function or process is called an
[argument](#argument).

If a parameter is named like a [local
variable](#local_variable), the value passed to it will be assigned to
that local variable for a process. This means that passed
arguments will modify the local variable. This is commonly used for
[x](#x), [y](#y) and [graph](#graph) local variables, but can also be
used for [alpha](#alpha), [angle](#angle) and others.

Notes
-----

There currently is a limit of 15 parameters that can be used per
function or process.

Example
-------
```pixtudio
    Process Main()
    Private
        int argument = 3;
    Begin
        my_proc( argument );
    End
```

```pixtudio
    Process my_proc( int parameter )
    Begin
        //statements
    End
``` 

See also
--------

-   [Argument](#Argument)

