<category:variables> <category:predefined> [category:global
variables](category:global_variables "wikilink") <category:internal>

[**Up to Global Variables**](Global_variables "wikilink") [**Up to
Internal**](internal "wikilink")

------------------------------------------------------------------------

Definition
----------

**STRING\[32\]** argv

**Argv** is a [global variable](global_variable "wikilink"), holding the
arguments with which [BGDI](BGDI "wikilink") was called, including the
bytecode file.

  ------------- ---------------------------------------------------
  argv\[0\]     - The bytecode file (possibly without extension).
  argv\[1\]     - First argument.
  argv\[2\]     - Second argument.
  argv\[*n*\]   - *n*th argument.
  ------------- ---------------------------------------------------

If an argument was not given, the corresponding string will be `""`
(empty string). The number of arguments passed can be found with
[argc](argc "wikilink"). This means that `argv[argc-1]` is the last
argument.

Example
-------

    import "mod_say"

    Process Main()
    Private
        int i;
    Begin

        say("Bytecode file: " + argv[0]);

        i = 1;
        while(i<argc)
            say("Argument " + i + ": " + argv[i]);
            i++;
        end

    End

Running this on Windows XP:

    > bgdi argv mies noot "mies noot" "'mies noot'" "\"mies noot\"" 'mies noot'
    Bytecode file: argv
    Number of arguments: 8
    Argument 1: mies
    Argument 2: noot
    Argument 3: mies noot
    Argument 4: 'mies noot'
    Argument 5: "mies noot"
    Argument 6: 'mies
    Argument 7: noot'

Running this on Linux:

    $ bgdi argv mies noot "mies noot" "'mies noot'" "\"mies noot\"" 'mies noot'
    Bytecode file: argv
    Number of arguments: 7
    Argument 1: mies
    Argument 2: noot
    Argument 3: mies noot
    Argument 4: 'mies noot'
    Argument 5: "mies noot"
    Argument 6: mies noot

Here you can see some interesting things:

  ---------------- ------------------------------------------------------------------------------------
  *text*           produces an argument *word* for each word (words are separated by spaces)
  "*text*"         produces the argument *text*
  "'*text*'"       produces the argument *'text'*.
  "\\"*text*\\""   produces the argument *"text"*
  *'text'*         doesn't combine multiple words into one argument on Windows, but it does on Linux.
  ---------------- ------------------------------------------------------------------------------------

The passing of arguments is totally unrelated to
[Bennu](Bennu "wikilink") and is OS dependent. Usually the doubleqoutes
(" ") work, but as you can see, the single quotes (' ') don't always
work to combine multiple words into one argument.
