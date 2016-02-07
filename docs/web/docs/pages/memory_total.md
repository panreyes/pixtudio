Definition
----------

**INT** memory\_total ( )

Returns the memory total in bytes.

Also called [mem\_total](mem_total "wikilink")().

Returns
-------

**INT** : Memory total in bytes.

Example
-------

    import "mod_mem"
    import "mod_say"

    Process Main()
    Begin

        say("Total memory: " + memory_total());
        say("Free memory:  " + memory_free() );

    End

Used in example: [say](say "wikilink")(),
[memory\_total](memory_total "wikilink")(),
[memory\_free](memory_free "wikilink")()

<Category:functions> <Category:memory> <Category:mod_mem>
