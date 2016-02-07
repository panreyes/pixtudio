<category:reserved> <category:language> [category:basic
statement](category:basic_statement "wikilink")

[**Up to Basic Statements**](Basic_statements "wikilink")

------------------------------------------------------------------------

Syntax
------

**Const**

:   \[ <constants> \]

**End**

Description
-----------

Const is a reserved word used to initiate the declaration of
[constants](constants "wikilink"). Terminating the declaration block
with an [End](End "wikilink") is needed when the Const statement is not
used in conjunction with the main code of the
[Program](Program "wikilink").

When declaring constants inside this construct, it's now allowed to
explicitly name the type of the constant, i.e. you only have to assign
the constant the value you want (see [the
example](#example "wikilink")).

For a list of predefined constants, see [this
page](constants "wikilink").

Example
-------

    Const // Declare constants here
        myInt = 4;
        myString = "hello";
    End

    Process Main()
    Begin
    End

    Const // Declare constants here
    End