<category:reserved> <category:language> [category:basic
statement](category:basic_statement "wikilink")

[**Up to Basic Statements**](Basic_statements "wikilink")

------------------------------------------------------------------------

Syntax
------

**Private**

:   \[ <private variables> \]

\[**End**\]

Description
-----------

Private is a reserved word used to initiate the declaration of [private
variables](private_variable "wikilink"). Terminating the declaration
block with an [End](End "wikilink") is not necessary, but is possible.
[Parameters](Parameters "wikilink") of a [function](function "wikilink")
or [process](process "wikilink") will be considered a private variable
with the initiated value of the passed [argument](argument "wikilink").

Example
-------

    Process My_Process();
    Public
    Private // Declare private variables here
    Begin
    End