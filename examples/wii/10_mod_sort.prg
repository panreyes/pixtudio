/* MOD_SORT example from:
   http://wiki.bennugd.org/index.php?title=Sort#Example */

import "mod_sort";
import "mod_key";
import "mod_say";

Type _player
    String name;
    int score;
End

Const
    maxplayers = 5;
End;


Process main()
Private
    _player player[maxplayers-1];
    int i=0;
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
    for(i=0; i<maxplayers; i++)
        say(player[i].name + " - " + player[i].score);
    end

/* Sort by name ( quicksort() can't be used to sort Strings,
   as a String in Bennu is a pointer to the actual String,
   so it would sort the pointer addresses */

    // sort()
    sort(player); // sorts by name because name is the first variable in each element

    // Show array
    say("-------------------- name - sort()");
    for(i=0; i<maxplayers; i++)
        say(player[i].name + " - " + player[i].score);
    end

    // ksort()
    ksort(player,player[0].name,maxplayers);

    // Show array
    say("-------------------- name - ksort()");
    for(i=0; i<maxplayers; i++)
        say(player[i].name + " - " + player[i].score);
    end

/* Sort by score (sort() cannot be used here, because score is not the first variable) */

    // ksort()
    ksort(player,player[0].score,maxplayers);

    // Show array
    say("-------------------- score - ksort()");
    for(i=0; i<maxplayers; i++)
        say(player[i].name + " - " + player[i].score);
    end

    // quicksort()
    quicksort(&player[0],sizeof(_player),maxplayers,sizeof(String),sizeof(int),0);

    // Show array
    say("-------------------- score - quicksort()");
    for(i=0; i<maxplayers; i++)
        say(player[i].name + " - " + player[i].score);
    end
End
