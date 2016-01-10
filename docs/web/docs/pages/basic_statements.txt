<category:general>

Below are explained the basic statements of
[Program](Program "wikilink") and [Process](Process "wikilink") and
where to declare all the types of [variables](variables "wikilink"). For
prototyping see [Declare](Declare "wikilink").

A list of basic statements:

-   [Program](Program "wikilink")
-   [Process](Process "wikilink")
-   [Function](Function "wikilink")
-   [Declare](Declare "wikilink")
-   [Begin](Begin "wikilink")
-   [OnExit](OnExit "wikilink")
-   [End](End "wikilink")
-   [Private](Private "wikilink")
-   [Public](Public "wikilink")
-   [Local](Local "wikilink")
-   [Global](Global "wikilink")
-   [Const](Const "wikilink")

Basic statements
----------------

    Program example;
    Global // Start a global variables part of the program
    End

    Const // Start a constants part of the program
    End

    Local // Start a global variables part of the program
    End

    Private // Start a private variables part of the main process
    End

    Begin // Start the main code part of the main process
        proc1(); // create new instance of proc1
        Loop
            frame;
        End
    OnExit // Start the exit code part of the main process
    End

    Global // Start a global variables part of the program
    End

    Const // Start a constants part of the program
    End

    Local // Start a global variables part of the program
    End

    Process proc1()

    Public // Start the public variables part of the process
    Private // Start the private variables part of the process

    Begin // Start the main code part of the process
        Loop
            frame;
        End
    OnExit // Start the exit code part of the process

    End

    Function int func1()
    Public // Start the public variables part of the function
    Private // Start the private variables part of the function
    Begin // Start the main code part of the function
        return 0;
    OnExit // Start the exit code part of the function
    End

Used in example: [basic statements](basic_statements "wikilink"),
[loop](loop "wikilink"), [return](return "wikilink"),
[frame](frame "wikilink")

Global, constant, local and private parts of the program can be
scattered through the code, between processes and functions. Sometimes
the End can be left out, but it's good practice to keep it in. When a
variable or constant is declared, it's only viewable or editable for
statements *beneath* the declaration. For more info on that, see
[prototyping](prototyping "wikilink").

Note that when [Declare](Declare "wikilink") is used, the [Public
variables](Public_variable "wikilink") have to be declared in the
Declare block and not in the process block.
