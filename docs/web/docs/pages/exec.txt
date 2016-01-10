Definition
----------

**INT** exec ( &lt;**INT** mode&gt; , &lt;**STRING** executable&gt;,
&lt;**INT** number\_of\_arguments&gt; , &lt;**STRING POINTER**
arguments&gt; )

Executes the specified executable with the specified arguments in the
specified mode.

Parameters
----------

  ------------------------------- -------------------------------------------------------------------------------------------------------------
  **INT** mode                    - The mode to call the executable ([\_P\_WAIT](_P_WAIT "wikilink")/[\_P\_NOWAIT](_P_NOWAIT "wikilink")).
  **STRING** executable           - The executable to start.
  **INT** number\_of\_arguments   - The number of arguments given with *arguments*
  **STRING POINTER** arguments    - Pointer to an array of strings to be passed; *number\_of\_arguments* strings will be passed as arguments.
  ------------------------------- -------------------------------------------------------------------------------------------------------------

Returns
-------

**INT**

  -------------------- --------------------------------------------------------------------------------------------------------------------------------------
  -1                   - Error.
  mode==\_P\_WAIT:     - The exit status of the executable.
  mode==\_P\_NOWAIT:   - The process ID of the executable. This is **not** a [ProcessID](ProcessID "wikilink"), it is a process ID of the operating system.
  -------------------- --------------------------------------------------------------------------------------------------------------------------------------

Notes
-----

The mode parameter can be two things:

  ------------- -------------------------------------------
  \_P\_WAIT     - Wait for the executable to exit.
  \_P\_NOWAIT   - Do not wait for the executable to exit.
  ------------- -------------------------------------------

Example
-------

Open file.txt in notepad:

    import "mod_sys"

    Process Main()
    Private
        string arg;
    Begin
        arg = "file.txt";
        exec(_P_NOWAIT,"notepad.exe",1,&arg);
    End

Used in example: [exec](exec "wikilink")(),
[pointer](pointer "wikilink")

<Category:functions> <Category:programinteraction> <Category:mod_sys>
