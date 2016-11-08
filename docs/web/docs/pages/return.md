Definition
----------

```
Return {value};
```

Return is a reserved word used to return a value in a function. The
returned value must be of the datatype specified as the returndatatype
(see [Function](#function)). By default, the returntype of a
process or function is an [int](#int). When this statement is
reached, the function in which it resides will stop execution and return
the specified value. If a value was not specified, the
[ProcessID](#processid) will be returned.

Example
-------

```
    Function string example_function()
    Private
        string s;
    Begin
        s = "Some string";
        return s;
    End
```

Used in example: [Function](#function),
[Private](#private), [Begin](#begin),
[End](#end), [Return](#return),
[String](#string)
