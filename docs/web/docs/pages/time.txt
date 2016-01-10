Syntax
------

**INT** time ( )

Description
-----------

Returns the current time, in seconds from January 1st, 1970.

This function is mostly useful for the [function](function "wikilink")
[ftime](ftime "wikilink")(), to display time and date in a particular
format. It is also useful in [rand\_seed](rand_seed "wikilink")(), to
have 'more randomness'.

Returns
-------

**INT** : The current time, in seconds from January 1st, 1970.

Example
-------

    import "mod_time"
    import "mod_timer"
    import "mod_text"
    import "mod_key"

    Process Main();
    Private
        String timestring; // The string holding the formatted time
    Begin

        write_string(0,0,0,0,&timestring); // Display the timestring
        timer = 100; // Make it so it updates the timestring immediately

        Repeat
            if(timer>100) // Update the timestring every 1 second
                timer = 0;
                timestring = ftime("%d-%m-%Y %H:%M:%S",time());
            end
            frame;
        Until(key(_esc))

    End

Used in example: [write\_string](write_string "wikilink")(),
[ftime](ftime "wikilink")(), [key](key "wikilink")(),
[timer](timer "wikilink")

<Category:functions> <Category:time> <Category:mod_time>
