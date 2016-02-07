<category:variables> <category:predefined> [category:local
variables](category:local_variables "wikilink") <category:internal>

[**Up to Local Variables**](Local_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** priority = 0

priority is a predefined [local variable](local_variable "wikilink"),
holding the priority of the [process](process "wikilink"); default is 0.

Using this priority, the order of process-execution can be influenced,
because processes with a higher priority are executed before processes
with a lower priority.

Example
-------

    import "mod_say"
    import "mod_proc"
    import "mod_timers"

    Process A()
    Begin
        priority = 0; // Default
        Loop
            say("[" + timer[0] + "] " + "A");
            frame(100000000); // This is very high because Bennu runs without limiter here
        End
    End

    Process main()
    Private
        int f=0;
    Begin
        priority = 1; // Set to higher priority than A
        A();
        Repeat
            f++;
            say("[" + timer[0] + "] " + "Main");
            frame(100000000); // This is very high because Bennu runs without limiter here
        Until(f==5)
    OnExit
        let_me_alone();
    End

Used in example: [say](say "wikilink")(),
[let\_me\_alone](let_me_alone "wikilink")(), [timer](timer "wikilink"),
[priority](priority "wikilink"), [frame](frame "wikilink")

Possible output:

    [0] A
    [0] Main
    [26] Main
    [26] A
    [50] Main
    [50] A
    [74] Main
    [74] A
    [98] Main
    [98] A

It can be seen here that regardless of priority, `A` is first executed,
because `A` is called by `Main`. As soon as `A` reaches its
[frame](frame "wikilink") statement, `Main` continues until its frame
statement and this concludes the first frame. The second frame it is
shown that the priority has effect: `Main` is executed before `A`.
