<category:reserved> <category:language> [category:control flow
statements](category:control_flow_statements "wikilink")

Definition
----------

**Return** \[<value>\];

Return is a reserved word used to return a value in a function. The
returned value must be of the datatype specified as the returndatatype
(see [Function](Function "wikilink")). By default, the returntype of a
process or function is an [int](int "wikilink"). When this statement is
reached, the function in which it resides will stop execution and return
the specified value. If a value was not specified, the
[ProcessID](ProcessID "wikilink") will be returned.

Example
-------

    Function string example_function()
    Private
        string s;
    Begin
        s = "Some string";
        return s;
    End

Used in example: [Function](Function "wikilink"),
[Private](Private "wikilink"), [Begin](Begin "wikilink"),
[End](End "wikilink"), [Return](Return "wikilink"),
[String](String "wikilink")
