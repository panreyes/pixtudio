Definition
----------

**INT** quicksort ( &lt;**VOID POINTER** array&gt; , &lt;**INT**
elementsize&gt; , &lt;**INT** elements&gt; , &lt;**INT** dataoffset&gt;
, &lt;**BYTE** datasize&gt; , &lt;**BYTE** datatype&gt; )

Sorts an [array](array "wikilink") by the Quicksort ordering algorithm.

This function is very handy for user defined [types](type "wikilink")
for elements in which a sort-[variable](variable "wikilink") is present.
For simple arrays or arrays in which the first variable is the
sort-variable, [sort](sort "wikilink")() can be used. For arrays in
which the sort-variable is a String, [ksort](ksort "wikilink")() can be
used.

Parameters
----------

  ------------------------ ---------------------------------------------------------------------------------------------------------------------------------------------
  **VOID POINTER** array   - [Pointer](Pointer "wikilink") to the first element of the [array](array "wikilink") to be sorted.
  **INT** elementsize      - The size of an element in the array in bytes.
  **INT** elements         - The number of elements in the array.
  **INT** dataoffset       - The number of [bytes](byte "wikilink") the sort-[variable](variable "wikilink") in each element is relative to the start of that element.
  **BYTE** datasize        - The size of the sort-variable in bytes.
  **BYTE** datatype        - The datatype of the sort-variable. (0:[integer](int "wikilink"), 1:[float](float "wikilink"))
  ------------------------ ---------------------------------------------------------------------------------------------------------------------------------------------

Returns
-------

**INT**: [true](true "wikilink")

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
