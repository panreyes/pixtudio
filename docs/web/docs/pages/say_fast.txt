Definition
----------

**INT** say\_fast ( &lt;**STRING** message&gt; )

Prints *message* to stdout (console). This function is the same as the
[Say](Say "wikilink")() function, but with the difference that the
debugging information isn't flushed (buffered) into the standard output.
As you can see in the [bennu source code
mod\_say.c](http://bennugd.svn.sourceforge.net/viewvc/bennugd/modules/mod_say/mod_say.c?revision=276&view=markup),
the difference is only 1 instruction, so it's slightly faster.

-   Similar to `System.out.println(message)` in Java.
-   Similar to `printf("%s\n",message)` in C

Parameters
----------

  -------------------- ------------------------------------------
  **STRING** message   - The message to print on to the console
  -------------------- ------------------------------------------

Returns
-------

**INT** - [true](true "wikilink")

Example
-------

    // import modules
    IMPORT "mod_say";
    IMPORT "mod_debug";


    GLOBAL

    int count;

    PROCESS main();
      
    BEGIN

       say("hello world.");
       say("");
       say("");
       FOR (count=0; count<5000; count+=1)
          say_fast("count: "+count);
       END
    END

This will result in the output on console:

    Hello World!

<Category:functions> <Category:debug> <Category:mod_say>
