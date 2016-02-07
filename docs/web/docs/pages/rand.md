Definition
----------

**INT** rand ( &lt;**INT** lowerlimit&gt; , &lt;**INT** upperlimit&gt; )

Returns a random number, ranging from a certain lower limit to a certain
upper limit. The limits are within the range.

Make sure the difference between *lowerlimit* and *upperlimit* does not
exceed 32767 (2\^15-1). If that is needed, the function *rand2()* below
can be used.

Parameters
----------

  -------------------- -----------------------------------------
  **INT** lowerlimit   - The lower limit for the random value.
  **INT** upperlimit   - The upper limit for the random value.
  -------------------- -----------------------------------------

Returns
-------

**INT** : A random value: lowerlimit &lt;= result &lt;= upperlimit

Notes
-----

To synchronize rand() on different computers, the function
[rand\_seed](rand_seed "wikilink")() can be used.

Rand() is not a very good function on itself. To counter this, the
following *rand2()* can be used:

    #define RAND_MAX 32767
    #define DRAND_RANGE (1.0/((RAND_MAX + 1)*(RAND_MAX + 1)))
    #define irand(x) ((unsigned int) ((x) * drand ()))
    Function float drand ()
    Private
        float f;
    Begin
        Repeat
           f = (rand (0,RAND_MAX) * (RAND_MAX + 1.0)
              + rand (0,RAND_MAX)) * DRAND_RANGE;
        Until (f < 1); /* Round off */
        return f;
    End
    Function int rand2(int lowerlimit, int upperlimit)
    Begin
        return (lowerlimit+irand(upperlimit-lowerlimit+1));
    End

To understand this code, one can read [its
source](http://www.azillionmonkeys.com/qed/random.html).

<Category:functions> <Category:math> <Category:mod_rand>
