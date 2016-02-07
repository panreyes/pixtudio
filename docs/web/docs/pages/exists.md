Definition
----------

**INT** Exists ( &lt;**INT** processID|processTypeID&gt; )

Checks if a [process](process "wikilink") is alive, using its
[processID](processID "wikilink") or checks if there is a process alive
of a certain [processType](processType "wikilink"), using its
[processTypeID](processTypeID "wikilink").

Parameters
----------

  --------------------------------- ---------------------------------------------------------------------------------------------
  **INT** processID|processTypeID   - The ProcessID of the process or the ProcessTypeID of the type of processes to be checked.
  --------------------------------- ---------------------------------------------------------------------------------------------

Returns
-------

**INT** : The result of the check

  ----------- ----------------------------------------------------------------------------------------------------------------
  0 (false)   - The process with given processID is not alive or there are no processes alive of the given processTypeID.
  1 (true)    - The process with given processID is alive or there is at least one process alive of the given processTypeID.
  ----------- ----------------------------------------------------------------------------------------------------------------

Example
-------

    import "mod_proc"
    import "mod_say"

    Process Main()
    Begin

        Proc();

        if(exists(id))
            say("I exist! (id)");
        end

        if(exists(0))
            say("0 exists!");
        else
            say("0 doesn't exist!");
        end

        if(exists(type proc))
            say("1- Proc exists!");
        else
            say("1- Proc doesn't exist!");
        end

        let_me_alone();

        if(exists(type proc))
            say("2- Proc exists!");
        else
            say("2- Proc doesn't exist!");
        end

    End

    Process Proc()
    Begin
        Loop
            frame;
        End
    End

Used in example: [exists](exists "wikilink")(), [say](say "wikilink")(),
[let\_me\_alone](let_me_alone "wikilink")()

<Category:functions> <Category:processinteraction> <Category:mod_proc>
