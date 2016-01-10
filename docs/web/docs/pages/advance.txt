Definition
----------

**INT** advance ( &lt;**INT** distance&gt; )

Moves the [calling](function_call "wikilink")
[process](process "wikilink") forward by *distance* units in the
direction of the process' [angle](angle "wikilink").

This function is influenced by the [local
variables](local_variable "wikilink") [angle](angle "wikilink") and
[resolution](resolution "wikilink").

Parameters
----------

  ------------------ ---------------------------------
  **INT** distance   - Distance to advance in units.
  ------------------ ---------------------------------

Returns
-------

  --------------------------------------------------------------------------------------------------
  **INT** : Returns [true](true "wikilink") if successful and [false](false "wikilink") if failed.
  --------------------------------------------------------------------------------------------------

Example
-------

    import "mod_grproc"
    import "mod_map"
    import "mod_wm" // for exit_status
    import "mod_key" // for key()
    import "mod_proc"

    Process Main()
    Private
        int my_proc;
    Begin

        proc(); //create a new process
        proc2(); //create a new process

        Repeat
            frame;
        Until(key(_ESC) || exit_status)

    OnExit

        signal(my_proc,S_KILL);

    End

    Process proc()
    Begin

        // Create a cyan square and assign it to 'graph'
        graph = map_new(100,100,8);
        map_clear(0,graph,rgb(0,255,255));

        // Set starting position
        x = 50;
        y = 50;

        // This loop makes this process advance 3 pixels every frame
        Loop
            advance(3); // advance 3 pixels
            frame;
        End

    End

    Process proc2()
    Begin

        // Set resolution to 100
        resolution = 100;

        // Create a cyan square and assign it to 'graph'
        graph = map_new(100,100,8);
        map_clear(0,graph,rgb(0,255,255));

        // Set starting position
        x = 50*resolution;
        y = 150*resolution;

        // This loop makes this process advance 3/100 pixels every frame
        Loop
            advance(3); // advance 3/100 pixels
            frame;
        End

    OnExit

        map_unload(0,graph);

    End

Used in example: [key](key "wikilink")(), [signal](signal "wikilink")(),
[map\_new](map_new "wikilink")(), [map\_clear](map_clear "wikilink")(),
[rgb](rgb "wikilink")(), [advance](advance "wikilink")(),
[map\_unload](map_unload "wikilink")(),
[exit\_status](exit_status "wikilink"), [graph](graph "wikilink"),
[x](x "wikilink"), [y](y "wikilink"),
[resolution](resolution "wikilink")

<Category:functions> <Category:processinteraction> <Category:mod_grproc>
