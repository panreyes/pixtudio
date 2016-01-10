Syntax
------

**STRING** ftime ( &lt;**STRING** format&gt; , &lt;**INT** time&gt; )

Description
-----------

Puts a certain time in a certain format.

It returns the specified [string](string "wikilink"), with certain
keywords replaced with their corresponding values, according to the
specified time (see [Notes](#Notes "wikilink")). The current time is
fetched by use of the [function](function "wikilink")
[time](time "wikilink")().

Parameters
----------

  ------------------- -----------------------------------------------
  **STRING** format   - The format wanted.
  **INT** time        - The time to be put in the formatted string.
  ------------------- -----------------------------------------------

Returns
-------

**STRING** : The formatted string.

Notes
-----

A list of keywords:

  ----------- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  *Keyword*   - *Replaced by*
  %a          - the locale's abbreviated weekday name.
  %A          - the locale's full weekday name.
  %b          - the locale's abbreviated month name.
  %B          - the locale's full month name.
  %c          - the locale's appropriate date and time representation.
  %C          - the century number (the year divided by 100 and truncated to an integer) as a decimal number \[00-99\].
  %d          - the day of the month as a decimal number \[01,31\].
  %D          - the same as %m/%d/%y.
  %e          - the day of the month as a decimal number \[1,31\]; a single digit is preceded by a space.
  %h          - the same as %b.
  %H          - the hour (24-hour clock) as a decimal number \[00,23\].
  %I          - the hour (12-hour clock) as a decimal number \[01,12\].
  %j          - the day of the year as a decimal number \[001,366\].
  %m          - the month as a decimal number \[01,12\].
  %M          - the minute as a decimal number \[00,59\].
  %n          - a newline character.
  %p          - the locale's equivalent of either a.m. or p.m.
  %r          - the time in a.m. and p.m. notation; in the POSIX locale this is equivalent to %I:%M:%S %p.
  %R          - the time in 24 hour notation (%H:%M).
  %S          - the second as a decimal number \[00,61\].
  %t          - a tab character.
  %T          - the time (%H:%M:%S).
  %u          - the weekday as a decimal number \[1,7\], with 1 representing Monday.
  %U          - the week number of the year (Sunday as the first day of the week) as a decimal number \[00,53\].
  %V          - the week number of the year (Monday as the first day of the week) as a decimal number \[01,53\]. If the week containing 1 January has four or more days in the new year, then it is considered week 1. Otherwise, it is the last week of the previous year, and the next week is week 1.
  %w          - the weekday as a decimal number \[0,6\], with 0 representing Sunday.
  %W          - the week number of the year (Monday as the first day of the week) as a decimal number \[00,53\]. All days in a new year preceding the first Monday are considered to be in week 0.
  %x          - the locale's appropriate date representation.
  %X          - the locale's appropriate time representation.
  %y          - the year without century as a decimal number \[00,99\].
  %Y          - the year with century as a decimal number.
  %Z          - the timezone name or abbreviation, or by no bytes if no timezone information exists.
  %%          - %.
  ----------- --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Example
-------

    import "mod_timer"
    import "mod_time"
    import "mod_text"
    import "mod_key"

    Process Main()
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
[time](time "wikilink")(), [key](key "wikilink")(),
[timer](timer "wikilink")

<Category:functions> <Category:time> <Category:mod_time>
