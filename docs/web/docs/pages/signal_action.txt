Definition
----------

**INT** signal\_action ( \[&lt;**INT** processID|processTypeID&gt; , \]
**INT** signal , **INT** action )

Sets the reaction of one or more [processes](process "wikilink") when
they receive a certain nonforceful-[signal](signals "wikilink"). Only
*existing* processes are affected, processes created afterwards are not.

Parameters
----------

  --------------------------------- -----------------------------------------------------------------------------------------------------------------------------------------------
  **INT** processID|processTypeID   - A [ProcessID](ProcessID "wikilink"),[ProcessTypeID](ProcessTypeID "wikilink") or `ALL_PROCESS`.
  **INT** signal                    - The code of a nonforceful-[signal](signals "wikilink") for which a reaction is to be specified.
  **INT** action                    - The [reaction](signal_actions "wikilink") of the process when it receives a signal. ([S\_DFL](S_DFL "wikilink")/[S\_IGN](S_IGN "wikilink"))
  --------------------------------- -----------------------------------------------------------------------------------------------------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")

Notes
-----

The reaction to an incoming forced signal (S\_KILL\_FORCE,
S\_SLEEP\_FORCE, etc) cannot be changed and is **S\_DFL** by default.

Example
-------

    // The current process ignores the kill signal from now on
    signal_action(S_KILL,S_IGN);

    // All currently existing processes ignore the kill signal from now on
    signal_action(ALL_PROCESS,S_KILL,S_IGN);

    // All currently existing processes of type 'Player' ignore the freeze signal from now on
    signal_action(type Player,S_FREEZE,S_IGN);

<Category:functions> <Category:processinteraction> <Category:mod_proc>
