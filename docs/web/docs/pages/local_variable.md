<category:general>

Definition
----------

A local variable is a [variable](variable "wikilink") that is specific
to a [process](process "wikilink") in the same way as a [public
variable](public_variable "wikilink"): they are both accessible from
other places in the code than the
[process](process "wikilink")/[function](function "wikilink") itself.
However, unlike a public variable, when a local variable is declared,
*all* following processes will have that local.

There's also a number of [predefined](predefined "wikilink") [local
variables](local_variables "wikilink").

To start the declaration of local variables, use
[Local](Local "wikilink").

Example
-------

    Local
        // insert local variables that you can use here
    End

    Process Main()
    Begin
        // main code
    End

Used in example: [Process](Process "wikilink"),
[Local](Local "wikilink"), [Begin](Begin "wikilink"),
[End](End "wikilink")

<Category:variablecategories>
