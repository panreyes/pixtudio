<category:variables> <category:predefined> [category:local
variables](category:local_variables "wikilink") <category:internal>

[**Up to Local Variables**](Local_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** father

**Father** is a predefined [local variable](local_variable "wikilink").
**Father** holds the [ProcessID](ProcessID "wikilink") of the
[process](process "wikilink")/[function](function "wikilink") that
called the current
[process](process "wikilink")/[function](function "wikilink"). There are
several other local variables which refer to the ProcessID of a related
process:

-   [Son](Son "wikilink")
-   [Bigbro](Bigbro "wikilink")
-   [Smallbro](Smallbro "wikilink")

Example
-------

    Program example;
    Begin
        first_process();
        Loop
            frame;
        End
    End

    Process first_process()  // Declaration of the first process
    Begin
        second_process();  // Call the second process
        Loop
            frame; // This loop makes "first_process()" a process rather than a function
        End
    End

    Process second_process()  //declaration of another process
    Begin
        x = father.x; // These two lines use the father variable to move this process
        y = father.y; // to the position of first_process, as the father variable here
                      // holds the ProcessID of "first_process()"
        Loop
            frame;  
        End
    End

Used in example: [process](process "wikilink"),
[function](function "wikilink"), [processID](processID "wikilink")
