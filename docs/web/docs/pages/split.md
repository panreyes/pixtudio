Syntax
------

**INT** split ( &lt;**STRING** delimiter&gt; , &lt;**STRING** str&gt; ,
&lt;**STRING POINTER** array&gt; , &lt;**INT** max\_number&gt; )

Description
-----------

Splits a [string](string "wikilink") in several strings using a [regular
expression](regular_expression "wikilink") as delimiter.

The first piece will go to *array*\[0\], the second to *array*\[1\], and
so forth, until either there are no more pieces left or *max\_number*
pieces are returned into the array. The number of pieces returned this
way is returned by the function.

Parameters
----------

  -------------------------- ---------------------------------------------------------------------
  **STRING** delimiter       - The regular expression used as delimiter to split.
  **STRING** str             - The input string to split into multiple string.
  **STRING POINTER** array   - Pointer to the string array where the pieces will be returned to.
  **INT** max\_number        - The maximum number of strings to return.
  -------------------------- ---------------------------------------------------------------------

Returns
-------

**INT** : The number of pieces returned into the array.

Example
-------

    import "mod_say"
    import "mod_regex"

    Process Main()
    Private
        string str = "A,B,C,D,E";
        string a[9];
        int n;
        int i;
    Begin

        // Split
        n = split(",",str,&a,10);

        // Display result
        say("Number of pieces: " + n);
        for(i=0; i<n; i++)
            say("[" + i + "] = " + a[i]);
        end

    End

Used in example: [split](split "wikilink")(), [say](say "wikilink")()

<Category:functions> <Category:mod_regex>
