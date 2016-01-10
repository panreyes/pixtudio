Setting up
----------

### Source

Before we start coding, download the latest Fenix Source
[here](Latest_Fenix_version "wikilink") and the file
[fenixdll.def](Media:Fenixdll.def "wikilink"). Put the source somewhere
appropriate, like **Fenix\\Fenix 0.92a Source\\**. Search for all \*.c
and \*.h in that folder and put it into a new folder like **Fenix\\Fenix
0.92a Includes\\**, together with fenixdll.def.

### MVC++

So we got MVC++ eh, let's do this then.

-   **Tools -&gt; Options -&gt; TAB: Directories**. Show directories
    for: Include files. Add the directory you created earlier,
    **Fenix\\Fenix 0.92a Includes**, to the list. Yes the
    **includes** folder.

<!-- -->

-   **File -&gt; New** will bring up the **New** dialog box. Select
    **Win32 Dynamic-Link Library** and name your project. Click OK. A
    new dialog box pops up! Select **An empty DLL project.** and
    click Finish. Click OK. I myself like to have the list on the left
    to display the files; to do this select FileView under it.

<!-- -->

-   **File -&gt; New** again, select **C++ Source File** and name
    your file. Click OK.

<!-- -->

-   **Project -&gt; Add To Project -&gt; Files...** and add fenixdll.def
    to your project.

### Code::Blocks

Ah, so you're a cool kid on the block. Let's get cracking.

-   **File -&gt; New -&gt; Project**. Select Empty project. Specify a
    name and project folder. Keep GNU GCC Compiler and just hit Finish.

<!-- -->

-   **File -&gt; New -&gt; Empty file**. Select yes. Name the file
    anything you want, but for the sake of this tutorial, have it the
    extension **.c**; you can go rogue later.

<!-- -->

-   **Project -&gt; Properties...**. Select TAB **Build targets**. For
    each target you want to use (on the left), select **Dynamic
    library** at the Type (on the right). You don't need to create an
    import library.

<!-- -->

-   **Project -&gt; Build options...**. Select the top item in the list
    on the left. Go to TAB **Linker settings** and add the following
    line to the right textfield: `-def fenixdll.def`. Now go to TAB
    **Search directories** -&gt; TAB **Compiler** and add the directory
    you created earlier, the **Fenix\\Fenix 0.92a Includes**.

<!-- -->

-   Copy **fenixdll.def** to your project folder.

Coding a DLL
------------

Now you have a setup for making a DLL for Fenix, but if you use
libraries, you'll have to set them up yourself. Fenix uses SDL by
default, so you will need to [set this
up](http://lazyfoo.net/SDL_tutorials/lesson01/index.php) too. If the
compiler complains it cannot find `SDL*.h`, go to where the file is
included and change the inclusion of `SDL*.h` to `SDL/SDL*.h`. It also
uses [zlib](http://www.zlib.net/).

The most basic code will be something like this:

    #include <fxdll.h>

    static int DLL_MYFUNC(INSTANCE * my, int * params)
    {
        return 0;
    }

    FENIX_MainDLL RegisterFunctions (COMMON_PARAMS)
    {
        FENIX_DLLImport

        FENIX_export ( "DLL_MYFUNC" , "" , TYPE_DWORD , DLL_MYFUNC ) ;

    }

If this doesn't compile then something went wrong during setup. Let's
assume it compiles, so I can explain the code.

### RegisterFunctions

This is where you tell Fenix which functions to make available for use
in Fenix. To do this, add a line like this:

FENIX\_export ( &lt;**CHAR \*** functionname&gt; , &lt;**CHAR \***
parameters&gt; , &lt;**BASETYPE** returntype&gt; , &lt;**VOID \***
function&gt; ) ;

-   **CHAR \*** functionname: This is how the function will be called
    in Fenix.

<!-- -->

-   **CHAR \*** parameters: The list of parameters, possible characters
    are:

  --- -----------------
  I   - TYPE\_DWORD
  B   - TYPE\_BYTE
  W   - TYPE\_WORD
  S   - TYPE\_STRING
  P   - TYPE\_POINTER
  F   - TYPE\_FLOAT
  --- -----------------

-   **BASETYPE** returntype: The datatype of the returnvalue. Possible
    are:

  ----------------- ------
  TYPE\_UNDEFINED   - 0
  TYPE\_INT         - 1
  TYPE\_DWORD       - 2
  TYPE\_SHORT       - 3
  TYPE\_WORD        - 4
  TYPE\_SBYTE       - 5
  TYPE\_BYTE        - 6
  TYPE\_CHAR        - 8
  TYPE\_FLOAT       - 9
  TYPE\_STRING      - 16
  TYPE\_ARRAY       - 17
  TYPE\_STRUCT      - 18
  TYPE\_POINTER     - 19
  ----------------- ------

-   **VOID \*** function: This is the function you wish Fenix to call
    when the function is called. This is the name of the function,
    without "" and can differ from the functionname used in Fenix.

### Functions

Like stated, the most basic function is of the form:

    static int DLL_MYFUNC(INSTANCE * my, int * params)
    {
        return 0;
    }

The first parameter is like a [processID](processID "wikilink"): it is
the [process](process "wikilink") calling this function. The second
parameter is a list of parameters. For some parameters you may wish to
typecast them via a 'pointer tyoecast' and put them into a proper
variable before using them, for example:

    float my_float = *(float*)&params[0];

The return type of this function is always **static int** and you should
always return an int. Of course you can return other datatypes, but it
needs to be 'pointer typecasted' to an int, like:

    return *(int*)&my_float;

### Example

    #include <fxdll.h>
    #include <math.h>

    static int dll_log(INSTANCE * my, int * params)
    {
        // Store the result in a variable first, for the pointer typecasting
        float f = logf(*(float*)&params[0]);
        return *(int*)&f;
    }

    FENIX_MainDLL RegisterFunctions (COMMON_PARAMS)
    {
        FENIX_DLLImport

        // float log( float f)
        FENIX_export ( "log" , "F" , TYPE_FLOAT , dll_log) ;

    }

Tips & Tricks
-------------

There are a few tips and tricks, but most of them come from experience.
Some from a lot of experience.

-   It is possible to use the same functionname multiple times, even
    with different properties. The only condition is that the number of
    parameters needs to be different:

<!-- -->

    FENIX_export ( "DLL_MYFUNC" , "I"  , TYPE_DWORD , DLL_MYFUNC ) ;
    FENIX_export ( "DLL_MYFUNC" , "II" , TYPE_DWORD , DLL_MYFUNC2 ) ;

-   Some functions are handy to use, for example gr\_con\_printf(). Look
    in the sourcecode of for example
    [Network.dll](Network.dll "wikilink") to see how it works. Keep in
    mind that flooding the console isn't very nice, so leave the option
    open for the user of the DLL to turn it off.

<!-- -->

-   Calling a [Fenix](Fenix "wikilink")
    [function](function "wikilink")/[process](process "wikilink") from a
    DLL can be handy sometimes, especially when used as a
    callback function. Initiating a process of a variable processtype in
    Fenix is also possible:

<!-- -->

    static int CALL(INSTANCE * my, int * params)
    {
        INSTANCE * proc = instance_new (procdef_get(params[0]), first_instance);
        return instance_go (proc);
    }

With this method the parameters of the called process won't be
initialized. Definition: `ProcessID call( <ProcessTypeID> )`\
Example: `proc_id = call(type MyProcName);`

Some handy functions
--------------------

<big>**void** gr\_con\_printf (**const char\*** fmt, ...)</big>

:   Outputs the message pointed to by *fmt* in the Fenix console.

<big>**int** string\_new (**const char\*** ptr)</big>

:   Creates a new string for Fenix, a copy of the string pointed to by
    *ptr* (so you can free the passed string). Returns the stringID of
    the created string.

<big>**void** string\_use (**int** stringID)</big>

:   Increase the usage counter of a string. Use this when you store the
    identifier of the string somewhere. So in practice this should
    always be called after string\_new().

<big>**const char\*** string\_get (**int** stringID)</big>

:   Returns the contents of a string. This pointer is only valid as long
    as no other string function is called (so duplicate the string
    if needed).

Be sure to discard the string once you don't need it anymore with
string\_discard () or that memory won't be freed until bennugd exits.

<big>**void** string\_discard (**int** stringID)</big>

:   Decrease the usage counter of a string. Use this when you retrieve
    the identifier of the string and discard it.

For the rest, see [fxdll.h](Media:Fxdll.h "wikilink") in the Fenix
source. If you'd like more documentation about a function or something
else, let [me](User:Sandman "wikilink") know (IRC/discussion page).

------------------------------------------------------------------------

--[Sandman](User:Sandman "wikilink") 19:10, 28 July 2008 (CEST)
