Definition
----------

**STRING**

**String**s are a sort of character array, combining characters to form
text. Because the length of a **string** is dynamic, adding them is done
easily. Single and double quotes can be used to create strings.

Example
-------

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

Used in example: [say](say "wikilink")(), [key](key "wikilink")()

Notes
-----

There are some things to be aware of with strings of the "string" data
type:

- Don't manually allocate data structures with strings in them (more
specifically, don't use
[alloc](alloc "wikilink")()/[calloc](calloc "wikilink")()/[realloc](realloc "wikilink")()
and [free](free "wikilink")() on them).

- Do not use [memmove](memmove "wikilink")() or
[memcopy](memcopy "wikilink")() on string variables or
[structures](struct "wikilink")/[arrays](array "wikilink") containing
them.

- Bennu strings are integer identifiers, so using sizeof with them is
pointless, as it will always return the size of an int. This is because
bennu creates it's own internal database for strings, and therefore it
is simply an identifier.

- Internally, the string data itself is a character array delimited with
a NULL character, just like an [ANSI /
C](http://en.wikipedia.org/wiki/Null-terminated_string) string.

- The memory for these strings is managed by bennu, thus manual memory
operations on them can cause harm on bennu's internal string managment.

- All
[local](local "wikilink")/[private](private "wikilink")/[public](public "wikilink")
strings are automatically released (free) when
[processes](process "wikilink")/[functions](function "wikilink") die or
exit.

However, if you want to do some manual memory managment on strings you
can:

- Create a simple character array yourself.

If you want to create a string list:

- You can create a linked list of processes using their
[Father](Father "wikilink") and [Son](Son "wikilink") fields to create
the links.

- Use textfiles.

- Create on big string in combination with an array that contains
information about substrings.

- Create an array of character arrays.

<Category:language> <Category:datatypes>
