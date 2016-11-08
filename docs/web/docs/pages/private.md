Syntax
------

```
Private
    {private variables}
End
```

Description
-----------

`Private` is a reserved word used to initiate the declaration of [private
variables](#private_variable). Terminating the declaration
block with an [End](#end) is not necessary, but is possible.
[Parameters](#parameters) of a [function](#function)
or [process](#process) will be considered a private variable
with the initiated value of the passed [argument](#argument).

Example
-------

```
    Process My_Process();
    Public
    Private // Declare private variables here
    Begin
    End
```