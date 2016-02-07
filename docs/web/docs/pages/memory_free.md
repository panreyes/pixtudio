Syntax
------

**INT** memory\_free ( )

Description
-----------

Returns the free memory total in bytes.

Also called [mem\_available](mem_available "wikilink")().

Returns
-------

**INT** : Free memory total in bytes.

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
