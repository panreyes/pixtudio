Syntax
------

**Declare** [ **Function** | **Process** ] [ {returntype} ] {name}
**(** [ {parameters} ] **)**

```
Private
   {private variables}
End
Public
    {public variables}
End
```

Description
-----------

`Declare` is a reserved word used to declare a
[process](process "wikilink") or [function](function "wikilink") before
its actual code. This can be useful if the function or process needs to
be known before it is actually defined, like when the function returns
something other than an [int](int "wikilink") or when the
[publics](publics "wikilink") of the process need to be accessed before
the definition. By default, the returntype of a process or function is
an [int](int "wikilink").

When using this statement, a few things can be defined about the
process/function:

-   If it's a process or function
-   Its returntype
-   The parameters of the process or function
-   The public variables of the process or function
-   The private variables of the process or function

The first three are defined when using the statement Declare, while the
last two are defined within the Declare block.

Example
-------

```
    Declare Process example_process()
        Public // Declare public variables for the process example_process
            int public_int;
            string public_string;
        End
    /*  The Process definition handles this section
        Private // Declare private variables for the process example_process
            int private_int;
        End
    */
    End

    Declare Function string example_function( int param_int)
        Private // Declare private variables for the process example_process
            int private_int;
        End
    End

    Process example_process();
    /* The Declare handles this section.
    Public
        int public_int;
        string public_string;
    */
    Private
        int private_int;
    Begin
        Loop
            frame;
        End
    End

    Function string example_function( int param_int)
    Begin
        return "";
    End
```
