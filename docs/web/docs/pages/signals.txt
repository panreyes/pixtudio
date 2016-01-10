Description
-----------

Signals are used to specify the signal to be sent to a
[process](process "wikilink") or all processes of a
[processType](processType "wikilink"), by passing one of them to the
function [signal](signal "wikilink")() as the signal
[parameter](parameter "wikilink"). The reaction a process has on an
incoming signal can be influenced by
[signal\_action](signal_action "wikilink")().

List
----

  ------------------------ ----------- --------------------------------------------------------------------------
  *Constant*               - *Value*   - *Description*
  S\_KILL                  - 0         - Kill the process.
  S\_WAKEUP                - 1         - Wakeup the process.
  S\_SLEEP                 - 2         - Put the process to sleep.
  S\_FREEZE                - 3         - Freeze the process.
  S\_KILL\_FORCE           - 50        - Kill the process forcefully.
  S\_WAKEUP\_FORCE         - 51        - Wakeup the process forcefully.
  S\_SLEEP\_FORCE          - 52        - Put the process to sleep forcefully.
  S\_FREEZE\_FORCE         - 53        - Freeze the process forcefully.
  S\_KILL\_TREE            - 100       - Kill the process and all its connected descendants.
  S\_WAKEUP\_TREE          - 101       - Wakeup the process and all its connected descendants.
  S\_SLEEP\_TREE           - 102       - Put the process and all its connected descendants to sleep.
  S\_FREEZE\_TREE          - 103       - Freeze the process and all its connected descendants.
  S\_KILL\_TREE\_FORCE     - 150       - Kill the process and all its connected descendants forcefully.
  S\_WAKEUP\_TREE\_FORCE   - 151       - Wakeup the process and all its connected descendants forcefully.
  S\_SLEEP\_TREE\_FORCE    - 152       - Put the process and all its connected descendants to sleep forcefully.
  S\_FREEZE\_TREE\_FORCE   - 153       - Freeze the process and all its connected descendants forcefully.
  ------------------------ ----------- --------------------------------------------------------------------------

A descendant is connected when all its ascendants up until the process
are still alive.

Note: The constants S\_FORCE, S\_TREE and ALL\_PROCESS are for internal
use only.

More info
---------

### General

-   S\_KILL - Order to kill the process. The process will not appear in
    the following [frames](frame "wikilink") of the game any longer. If
    the process has an [onexit](onexit "wikilink") part, it is executed
    in the same frame as the process was killed.
-   S\_WAKEUP - Order to wake up the process. It returns a slept or
    frozen process to its normal state. The process will be executed and
    displayed again from the moment that it recieves theis
    signal normally. A process that has been killed cannot be returned
    to its normal state by this method (or at all).
-   S\_SLEEP - Order to make the process dormant. The process will
    remain paralyzed, without executing its code and without being
    displayed on screen (nor being detected by other processes), as if
    it had been killed. But the process will continue to exist in the
    computer's memory.
-   S\_FREEZE - Order to freeze the process. The process will remain
    motionless without running its code. But it will continue to be
    displayed on screen and it will be possible to detect it (in
    the collisions) by the rest of the processes. The process will
    continue to exist in the computers memory even if its code is
    not executed.

### Tree

In addition to these there are the following signals that have the same
effect, but affect a range of processes, not just a single process:

-   S\_KILL\_TREE
-   S\_WAKEUP\_TREE
-   S\_SLEEP\_TREE
-   S\_FREEZE\_TREE

These will have the effect of their non-tree counterparts, but will
affect the process indicated by the
[processID](processID "wikilink")|[processTypeID](processTypeID "wikilink")
parameter and all of the processes created by those processes, either
directly, or indirectly. So if an S\_KILL\_TREE signal is sent to a
process, that process will die, all of the processes that it created
will die, and all of the processes that they created will die, and so
on. The exception to this is where there is an [orphan
process](orphan_process "wikilink"), that is a process to whose
[father](father "wikilink") is already dead, because the grandfather
process of the orphaned process cannot know the orphaned process is a
descendant of his.

### Forcefully

All normal (=non forced) signals have a forceful equivalent, meaning
they get carried out *whether the target process ignores it or not*:

-   S\_KILL\_FORCE
-   S\_WAKEUP\_FORCE
-   S\_SLEEP\_FORCE
-   S\_FREEZE\_FORCE
-   S\_KILL\_TREE\_FORCE
-   S\_WAKEUP\_TREE\_FORCE
-   S\_SLEEP\_TREE\_FORCE
-   S\_FREEZE\_TREE\_FORCE

Normal incoming signals can be influenced by
[signal\_action](signal_action "wikilink")(), but these signals cannot
be influenced. This means that sending a process `S_KILL_FORCE` it
*will* be killed.

<Category:constantcategories>
