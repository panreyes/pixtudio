Definition
----------

**STRING**

**String**s are a sort of character array, combining characters to form
text. Because the length of a `string` is dynamic, adding them is done
easily. Single and double quotes can be used to create strings.

Example
-------

```
    Program strings;
    Private
        String name;
        String surname;
    Begin
        name = "Yo";
        surname = "Momma";

        say(name + " " + surname + " has entered.");
        say('User logged on: "' + name + " " + surname + '"');

        Repeat
            frame;
        Until(key(_ESC))

    End
```

Used in example: [say](#say)(), [key](#key)()

Notes
-----

There are some things to be aware of with strings of the "string" data
type:

* Do not manually allocate data structures with strings in them (more specifically, don't use [alloc](#alloc)()/[calloc](#calloc)()/[realloc](#realloc)() and [free](free "wikilink")() on them).
* Do not use [memmove](#memmove)() or [memcopy](#memcopy)() on string variables or [structures](#struct)/[arrays](#array) containing them.
* PixTudio strings are integer identifiers, so using [sizeof](#sizeof) with them is pointless, as it will always return the size of an int. This is because bennu creates it's own internal database for strings, and therefore it is simply an identifier.
* Internally, the string data itself is a character array delimited with a NULL character, just like an [ANSI / C](http://en.wikipedia.org/wiki/Null-terminated_string) string.
* The memory for these strings is managed by bennu, thus manual memory operations on them can cause harm on bennu's internal string managment.
* All [local](#local)/[private](#private)/[public](#public) strings are automatically released (freed) when [processes](#process)/[functions](#function) die or exit.

However, if you want to do some manual memory managment on strings you
can:

* Create a simple character array yourself.

If you want to create a string list:

* You can create a linked list of processes using their [Father](#father) and [Son](#son) fields to create the links.
* Use textfiles.
* Create on big string in combination with an array that contains information about substrings.
* Create an array of character arrays.
