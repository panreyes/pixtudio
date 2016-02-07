<category:reserved> <category:language> [category:basic
statement](category:basic_statement "wikilink")

[**Up to Basic Statements**](Basic_statements "wikilink")

------------------------------------------------------------------------

Syntax
------

**Begin**\
:\[ <main code> \]\
\[ **OnExit**\
:\[ <exit code>\]\
\] **End**

Description
-----------

Begin is a reserved word to indicate the start of the code part of a
[program](program "wikilink"), [process](process "wikilink") or
[function](function "wikilink"). The end is indicated by
[End](End "wikilink"). The [OnExit](OnExit "wikilink") statement can be
used in between.

Example
-------

    Process Main
    Begin // Start the main code part of the main process
        proc1(); // create new instance of proc1
    End

    Process proc1()
    Begin // Start the main code part of the process
    End

    Function int func1()
    Begin // Start the main code part of the function
        return 0;
    End

Used in example: [end](end "wikilink"), [process](process "wikilink"),
[function](function "wikilink")
