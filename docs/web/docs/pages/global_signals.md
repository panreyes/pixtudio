This article, originally made by SplinterGU, tries to explain how to do
a signal to all process and how to recover the initial state of all
affected processes.

Here there are the code of the two functions needed to do it.

    import "mod_proc";

    /* ---------------------------------- */

    #define S_FORCE             50
    #define S_TREE              100

    /* ---------------------------------- */

    local
        saved_status ;
    end

    /* ---------------------------------- */

    function save_state_and_signal( int pid, int sig )
    begin
        if ( sig >= S_TREE )
            sig -= S_TREE;
        end

        if ( sig >= S_FORCE )
            sig -= S_FORCE;
        end

        if ( !pid )
            while ( pid = get_id(ALL_PROCESS) )
                if ( pid != id && pid != father )
                    pid.saved_status = get_status( pid );
                    signal( pid, S_FORCE + sig );
                end
            end
        else
            if ( pid != father )
                pid.saved_status = get_status( pid );
                signal( pid, S_FORCE + sig );
            end
        end
    end

    /* ---------------------------------- */

    function restore_state( int pid )
    begin
        if ( !pid )
            while ( pid = get_id(ALL_PROCESS) )
                if ( pid != id && pid != father )
                    signal( pid, S_FORCE + pid.saved_status );
                end
            end
        else
            if ( pid != father )
                signal( pid, S_FORCE + pid.saved_status );
            end
        end
    end

    /* ---------------------------------- */

You can add it to your main ".prg" code or make a file named
"global\_signal.prg" and add a include line to it in your code.

Here is an example of how to call they:

    save_state_and_signal( 0 , s_freeze );      // Freezes all processes.
    restore_state(0);  // restore all processes

You can use it like [signal](signal "wikilink") function that saves the
original state of the process, too.

<Category:General> <Category:Tutorials>
