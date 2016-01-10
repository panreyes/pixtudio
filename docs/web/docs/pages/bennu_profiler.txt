(We will keep this page as it is right now, as the profiler does not
exist in Bennu yet.)

The Bennu profiler is a handy debugging tool. It shows how much power is
needed for certain systems of Bennu, most particularly the drawing and
the interpreting.

To use the profiler,import the debug module
([mod\_debug](mod_debug "wikilink")) in your sorce code and compile it
in bgdc.exe with the argument "-g", and then show it in-program with
ALT+P.

Shortcuts:

  ------- -----------------------------------------------------
  ALT-P   - Show/hide the Bennu profiler
  ALT-R   - Resets the profile history of the Bennu Profiler.
  ALT-S   - Activate/Deactivate the Bennu Profiler.
  ------- -----------------------------------------------------

Example
-------

    Process Main()
    Begin

        // To make sure the profiler is updated every frame
        restore_type = COMPLETE_RESTORE;

        A();

        Loop
            frame;
        End

    End

    Process A()
    Begin
        Loop
            frame;
        End
    End

Used in example: [restore\_type](restore_type "wikilink"),
[process](process "wikilink"), [frame](frame "wikilink")

<Category:general> <Category:debugging>
