Definition
----------

**INT** rand\_seed ( &lt;**INT** seed&gt; )

Seeds the random generator, used in [rand](rand "wikilink")().

This is useful for synchronizing the random generator on multiple
machines, as when the same *seed* is used, calls to
[rand](rand "wikilink")() with the same limits will return values in the
same order on all the machines.

To reset the seeding to its original state, meaning the state before any
call to [rand](rand "wikilink")() or
[rand\_seed](rand_seed "wikilink")(), set *seed* to `1`.

Parameters
----------

  -------------- ------------------------------------------------------------------------------------
  **INT** seed   - The seed for the random generator used in [rand](rand "wikilink")(); 1 to reset.
  -------------- ------------------------------------------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Example
-------

    import "mod_rand"
    import "mod_say"
    import "mod_time"

    Process Main()
    Begin
        say("First number: " + (rand(0,1000)%100));
        rand_seed(time());
        say("Random number: " + (rand(0,1000)%100));
        rand_seed(1);
        say("Again the first number: " + (rand(0,1000)%100));
    End

Used in example: [say](say "wikilink")(), [rand](rand "wikilink")(),
[rand\_seed](rand_seed "wikilink")()

<Category:functions> <Category:math> <Category:mod_rand>
