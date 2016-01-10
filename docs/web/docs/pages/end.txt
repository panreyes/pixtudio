<category:reserved> <category:language> [category:basic
statement](category:basic_statement "wikilink")

[**Up to Basic Statements**](Basic_statements "wikilink")

------------------------------------------------------------------------

Syntax
------

**End**

Description
-----------

End is a reserved word used to terminate loads of stuff, such as
[if-statements](if "wikilink"), [loops](loops "wikilink"),
[begin-statements](begin "wikilink"), etc...

Example
-------


    Process Main()
    Begin
        If(something)
           If(something_else)
               Loop
                   frame;
               End //ends the loop
           End //ends the second if-statement
        End //ends the first if-statement
    End //ends the program block (begin keyword)

Used in example: [process](process "wikilink"), [if](if "wikilink"),
[loop](loop "wikilink"), [end](end "wikilink")
