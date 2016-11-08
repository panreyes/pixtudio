Syntax
------

```
Local
    {local variables}
End
```

Description
-----------

Local is a reserved word used to initiate the declaration of [local
variables](#local_variables). Terminating the
declaration block with an [End](#end) is needed when the `Local`
is not used in conjunction with the main code of the
[Program](#program).

For a list of predefined local variables, see [this
page](#local_variables).

Example
-------

```
    Local // Declare local variables here
    End

    Process Main()
    Begin
    End

    Local // Declare local variables here
    End
```
