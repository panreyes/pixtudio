Definition
----------

**INT** get\_id ( &lt;**INT** processTypeID&gt; )

Returns a [ProcessID](ProcessID "wikilink") of a
[process](process "wikilink") of the specified
[ProcessType](ProcessType "wikilink"). On the next call of get\_id() in
the same process and in the same frame, the next process will be
returned of the given type. After a [frame](frame "wikilink") statement,
get\_id() is reset and will return the first process of the given
processType. When there are no more processes of a given type, which
have not been returned, it will return 0.

get\_id(0) returns processes of any type.

Parameters
----------

  ----------------------- -----------------------------------------------------------------------------------------------------------------------------------
  **INT** processTypeID   - The [processTypeID](processTypeID "wikilink") of the [processType](processType "wikilink") to get the processes' processIDs of.
  ----------------------- -----------------------------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : The [processID](processID "wikilink") of a process of the
given processType.

  ------- ---------------------------------------------------------------------------------------
  0       - There are no more processes of the given processType, which have not been returned.
  &gt;0   - The [processID](processID "wikilink") of a process of the given processType.
  ------- ---------------------------------------------------------------------------------------

Example
-------

    Program example;
    Begin
        signaltype(type Monkey,s_kill);
    End

    /**
     * Empty process
     */
    Process Monkey()
    Begin
    End

    /**
     * Signals every process of type 't' the signal 'signal'.
     */
    Function int signaltype(int t, int signal)
    Begin
        while( (x=get_id(t)) ) // while there is an unprocessed process left and store that in 'x'
            signal(x,signal); // signal the process with processID 'x'.
        end
    End

    // Of course, the very observant of you already noticed that signaltype(my_type,my_signal)
    // does the same thing as the function signal(my_type,my_signal), but this is just to
    // illustrate the workings.

    /**
     * Signals every process the signal 'signal'.
     */
    Function int signalall(int signal)
    Begin
        while( (x=get_id(0)) ) // while there is an unprocessed process left and store that in 'x'
            signal(x,signal); // signal the process with processID 'x'.
        end
    End

    // get_id(0) returns a process of any type. This is a possible implementation of a
    // function which signals all existing processes. Note that this can be dangerous to use,
    // as in some cases you might want one or two processes to stay alive.

Used in example: [signal](signal "wikilink")()

<Category:functions> <Category:processinteraction> <Category:mod_proc>
