Definition
----------

**INT** get\_status ( &lt;**INT** processID&gt; )

Get the current status of a [ProcessID](ProcessID "wikilink"). With
this, you can check if a process is frozen, sleeping, dead, alive or
non-existing.

Parameters
----------

  ------------------- -------------------------------------------------------------
  **INT** processID   - The [ProcessID](ProcessID "wikilink") signal was send to.
  ------------------- -------------------------------------------------------------

Returns
-------

**INT** :

  --------------------------- --------------------------------------------------------------
  [false](false "wikilink")   - The specified processID does not exist (return status: 0).
  1,2,3 or 4                  - The state of the [processID](processID "wikilink").
  --------------------------- --------------------------------------------------------------

Return states
-------------

  --- -----------------------------------------
  0   - The specified process does not exist.
  1   - The specified process is dead.
  2   - The specified process is alive.
  3   - The specified process is sleeping.
  4   - The specified process is frozen.
  --- -----------------------------------------

Example
-------

    // import modules
    IMPORT "mod_say";
    IMPORT "mod_debug";
    IMPORT "mod_proc";
    IMPORT "mod_grproc";
    IMPORT "mod_key";


    GLOBAL

      int proc1;
      int proc2;
      int proc3;
      int proc4;
      int proc5;
      

    PROCESS main();

    PRIVATE

    BEGIN


       // create some processes
       proc1=dummy();
       proc2=dummy();
       proc3=dummy();
       proc4=dummy();

       // change the state
       signal(proc1,s_sleep);
       signal(proc2,s_freeze);
       signal(proc3,s_wakeup);
       signal(proc4,s_kill);
                
       // print the status of each instance            
       say("");
       say("status codes: ALIVE=2, SLEEP=3, FROZEN=4 ,DEAD=1, NON_EXISTING=0");
       say("");
       say("proc1 status: "+get_status(proc1)); // sleeping     (3)
       say("proc2 status: "+get_status(proc2)); // frozen       (4)
       say("proc3 status: "+get_status(proc3)); // alive        (2)
       say("proc4 status: "+get_status(proc4)); // dead         (1)
       say("proc5 status: "+get_status(proc5)); // not existing (0)
       
       
       LOOP
              
          // quit.
          IF (key(_esc))
               
             exit("",0);
          END
          FRAME;
       END
    END


    PROCESS dummy();

    PRIVATE

    BEGIN
       
       // endless loop
       LOOP
          FRAME;
       END
    END

Used in example: [exit](exit "wikilink")(), [say](say "wikilink")(),
[key](key "wikilink")(), [signal](signal "wikilink")

<Category:functions> <Category:processinteraction> <Category:mod_proc>
