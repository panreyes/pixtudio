<category:reserved> <category:language> [category:control flow
statements](category:control_flow_statements "wikilink")

Syntax
------

**call** <label> ;

Description
-----------

The [call](call "wikilink") command jumps to the given
[label](label "wikilink") inside a [function](function "wikilink") or
[process](process "wikilink") until it comes across a
[return](return "wikilink") statement. When this happens, it jumps back
to call statement and resumes after it.

Example
-------

    import "mod_say"

    Process Main()
    Begin

        say(my_function(1));

    End

    Function my_function(int value)
    Private
        int ret;
    Begin

        Jmp real_begin;

    jumping:
        ret = 300;
        return;

    real_begin:
        ret = 100;
        if(value == 1)
            Call jumping;
        end
        ret += 200;
        return ret;

    End

Used in example: [process](process "wikilink"),
[function](function "wikilink"), [jmp](jmp "wikilink"),
[call](call "wikilink"), [return](return "wikilink")

The output of this example is `500`, when `value` is 1. This example
show 500 because the input value is a one and it causes that goes to the
jumping label inserting a 300 and adding a 200 after.