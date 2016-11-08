Syntax
------

```
Global
    {global variables}
End
```

Description
-----------

`Global` is a reserved word used to initiate the declaration of [global
variables](#global_variables). Terminating the
declaration block with an [End](#end) is needed when the
`Global` is not used in conjunction with the main code of the
[Program](#program).

For a list of predefined global variables, see [this
page](#global_variables).

Example
-------

```
    Global // Declare global variables here
    End

    Process Main()
    Begin
    End

    Global // Declare global variables here
    End
```