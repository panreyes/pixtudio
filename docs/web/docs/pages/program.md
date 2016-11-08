Syntax
------

```
Program {programname};
```

Description
-----------

`Program` is a reserved word used to begin your program. It's not needed
to start a program with it.

It should be noted that this is for backwards compatibility only,
because it doesn't actually do anything.

Example
-------

```
    Program example; // Name this program "example", which doesn't really matter

    Process Main() // This process is started when the program is started
    Begin
    End
```

When the [End](#end) of the main code is reached, the program
exits, if there are no [processes](#process) alive anymore,
which is logical, as PixTudio quits when there are no processes
running and Main is a process as well. 
This process is just like any other process with the addition it gets called when the program starts. This means
that you can also [call](#function_call) the process using
`main()`.
