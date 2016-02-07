Definition
----------

An argument is the [value](#value) passed on when calling a
[function](#function) or [process](#process). The
[variable](#variable) and its value inside the definition of a
[function](#function) or [process](#process) is
called a [parameter](#parameter).

Example
-------

```pixtudio
    Function int my_proc( int parameter )
    Begin
        //statements
        return 0;
    End
```

```pixtudio
    Process Main()
    Private
        int argument = 3;
    Begin
        my_proc( argument );
        my_proc( 4);
    End
```

See also
--------

-   [Parameter](#parameter)
