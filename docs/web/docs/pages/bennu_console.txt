The Bennu console is a handy debugging tool. Many commands can be
entered in it, like [process](process "wikilink") manipulation or
[variable](variable "wikilink") manipulation. The current state of
[Globals](Globals "wikilink"), [Constants](Constants "wikilink"),
[Locals](Locals "wikilink"), [Publics](Publics "wikilink"),
[Privates](Privates "wikilink") can also be monitored. One can add text
to it in the programcode by using the function [say](say "wikilink")().

To use the debugger, you need import the debug module
([mod\_debug](mod_debug "wikilink")) in your source code, run in debug
mode by compiling your program in bgdc.exe with the argument "-g", and
when you are running your application with the interpreter(bgdi.exe) you
can activate it in-program with ALT+C.

Commands
--------

### Process Info

##### INSTANCES

List all running [processes](process "wikilink") in a tree view. It
shows what processes a processes called.

##### GLOBALS

List all [global variables](global_variable "wikilink") with their
current values. Both predefined and user defined variables are listed.

##### LOCALS <processName|processID>

List all [local variables](local_variable "wikilink") of the specified
process. The process can be specified by either its name or its
[processID](processID "wikilink"). Both predefined and user defined
variables are listed.

##### PRIVATES <processName|processID>

List all [local variables](local_variable "wikilink") of the specified
process. The process can be specified by either its name or its
[processID](processID "wikilink").

##### PUBLICS <processName|processID>

List all [local variables](local_variable "wikilink") of the specified
process. The process can be specified by either its name or its
[processID](processID "wikilink").

### Debugging Commands

##### TRACE

Execute the next instruction.

##### BREAK

List all set breakpoints.

##### BREAK <processName|processID>

Add a breakpoint on the execution of the specified process. The process
can be specified by either its name or its
[processID](processID "wikilink").

##### DELETE

Delete a breakpoint on the execution of the specified process. The
process can be specified by either its name or its
[processID](processID "wikilink").

##### CONTINUE

Continue the execution (close the console).

##### DOFRAME

Execute the next frame.

### Misc

##### SHOW <expression>

Evaluate and show the specified expression.

##### STRINGS

List all strings in memory and how many times they are used.

##### VARS

List all internal variables.

##### FILES

Displays the amount of files currently opened.

##### QUIT

Kill the program and exit.

### Process Management

See [signals](signals "wikilink") for further explanation about the
following signaling commands.

##### RUN <processName> \[<argument>\]

Start a process with optional arguments.

##### KILL <processName|processID>

Kill the specified process. The process can be specified by either its
name or its [processID](processID "wikilink").

##### WAKEUP <processName|processID>

Wake up the specified process. The process can be specified by either
its name or its [processID](processID "wikilink").

##### SLEEP <processName|processID>

Put the specified process to sleep. The process can be specified by
either its name or its [processID](processID "wikilink").

##### FREEZE <processName|processID>

Freeze the specified process. The process can be specified by either its
name or its [processID](processID "wikilink").

##### KILLALL <processName|processID>

If a processname is specified, kill all processes with that name; if a
processID is specified, only kill that process.

##### WAKEUPALL <processName|processID>

If a processname is specified, wake up all processes with that name; if
a processID is specified, only wake up that process.

##### SLEEPALL <processName|processID>

If a processname is specified, put all processes with that name to
sleep; if a processID is specified, only put that process to sleep.

##### FREEZEALL <processName|processID>

If a processname is specified, freeze all processes with that name; if a
processID is specified, only freeze that process.

### Expressions

You can evaluate free expressions and see/alter the values of variables.
=====<variable> \[= <value>\]===== Return or alter a global variable.
=====<processName|processID>.<variable> \[= <value>\]===== If a
processID is specified, the value of the local, private or public
variable of that process is returned or altered. If a processName is
specified, the process with that name and the lowest ID is assumed.

Example
-------

    Process Main()
    Begin
        Repeat
            frame;
        Until(key(_ESC))
    End

<Category:general> <Category:debugging>
