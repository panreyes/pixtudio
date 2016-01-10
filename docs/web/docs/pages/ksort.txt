Definition
----------

**INT** ksort ( &lt;**VARSPACE** array&gt; , &lt;**VARSPACE**
sort-variable&gt; , \[&lt;**INT** datacount&gt;\] )

Sorts a certain [array](array "wikilink") according to a sort-variable
within the elements and by sorting a certain number of elements. By
default the whole array is sorted.

If the array elements contain only one variable each or the first one is
the sort-variable, [sort](sort "wikilink")() can be used. For more
advanced sorting, look at [quicksort](quicksort "wikilink")().

Parameters
----------

  ---------------------------- ----------------------------------------------------------------
  **VARSPACE** array           - The [array](array "wikilink") to be sorted.
  **VARSPACE** sort-variable   - The variable within each element to be used for the sorting.
  \[**INT** datacount\]        - Number of elements to sort.
  ---------------------------- ----------------------------------------------------------------

Returns
-------

**INT**: Successrate

  --------------------------- -----------------------------------------------------------------------
  [true](true "wikilink")     - Sorting succeeded.
  [false](false "wikilink")   - Sorting failed, probably the type of sort-variable isn't supported.
  --------------------------- -----------------------------------------------------------------------

Example
-------

    Program sorting;

    Type _player
        String name;
        int score;
    End

    Const
        maxplayers = 5;
    Global
        _player player[maxplayers-1];
    Begin

        // Insert some values
        player[0].name = "That one bad looking dude";
        player[1].name = "Ah pretty lame guy";
        player[2].name = "Some cool dude";
        player[3].name = "OMG ZOMG guy";
        player[4].name = "This person is ok";

        player[0].score = 70;
        player[1].score = 30;
        player[2].score = 80;
        player[3].score = 90;
        player[4].score = 50;


        // Show array
        say("-------------------- unsorted");
        for(x=0; x<maxplayers; x++)
            say(player[x].name + " - " + player[x].score);
        end

    /* Sort by name ( quicksort() can't be used to sort Strings,
       as a String in Fenix is a pointer to the actual String,
       so it would sort the pointer addresses */

        // sort()
        sort(player); // sorts by name because name is the first variable in each element

        // Show array
        say("-------------------- name - sort()");
        for(x=0; x<maxplayers; x++)
            say(player[x].name + " - " + player[x].score);
        end

        // ksort()
        ksort(player,player[0].name,maxplayers);

        // Show array
        say("-------------------- name - ksort()");
        for(x=0; x<maxplayers; x++)
            say(player[x].name + " - " + player[x].score);
        end

    /* Sort by score (sort() cannot be used here, because score is not the first variable) */

        // ksort()
        ksort(player,player[0].score,maxplayers);

        // Show array
        say("-------------------- score - ksort()");
        for(x=0; x<maxplayers; x++)
            say(player[x].name + " - " + player[x].score);
        end

        // quicksort()
        quicksort(&player[0],sizeof(_player),maxplayers,sizeof(String),sizeof(int),0);

        // Show array
        say("-------------------- score - quicksort()");
        for(x=0; x<maxplayers; x++)
            say(player[x].name + " - " + player[x].score);
        end

        // Wait until ESC is pressed
        Repeat
             frame;
        Until(key(_esc))

    End

Used in example: [say](say "wikilink")(), [sort](sort "wikilink")(),
[ksort](ksort "wikilink")(), [quicksort](quicksort "wikilink")(),
[type](type "wikilink"), [array](array "wikilink"),
[pointer](pointer "wikilink")

<Category:functions> <Category:sorting> <Category:mod_sort>
