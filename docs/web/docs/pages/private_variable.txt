<category:variablecategories> <category:general>

Definition
----------

A private variable is a [variable](variable "wikilink") that is specific
to a [process](process "wikilink") or [function](function "wikilink").
Unlike a [public variable](public_variable "wikilink"), it can only be
accessed from the process or function it was declared for.

To start the declaration of private variables, use
[Private](Private "wikilink").

Example
-------

    Function int SomeFunction()
    Private
        int i,j; // declare private ints i and j
        String strtemp; // declare private string strtemp
    Begin
        // ...
        return 0;
    End

Used in example: [Function](Function "wikilink"),
[Private](Private "wikilink"), [Begin](Begin "wikilink"),
[End](End "wikilink")

The private variables i and j could be variables used for counting and
the string probably would have some use as well.
