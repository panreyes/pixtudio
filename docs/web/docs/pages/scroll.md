Definition
----------

**STRUCT[9]** Scroll

Scroll is a [global variable](#global_variable)
[struct](#struct) [array](#array), containing
information about the current state of the ten available scrolls (0..9).
It is used to influence the settings of a [scroll
window](#scroll_window), initiated by
[start_scroll](#start_scroll)().

Members of the scroll struct
----------------------------

|  Member name            | Description                                                                                            |
| ----------------------- | ------------------------------------------------------------------------------------------------------ |
|  **INT** x0             | The [X](#X)-coordinate of the foreground graphic.*                                                     |
|  **INT** y0             | The [Y](#Y)-coordinate of the foreground graphic.*                                                     |
|  **INT** x1             | The [X](#X)-coordinate of the the background graphic.*                                                 |
|  **INT** y1             | The [Y](#Y)-coordinate of the the background graphic.*                                                 |
|  **INT** z              | The [Z](#Z)-coordinate of the scroll window (default: 512).**                                          |
|  **INT** camera         | The [processID](#processID) of the process to be followed (default: 0).***                             |
|  **INT** ratio          | The ratio in percent the foreground will move related to the background (default: 200).\*\*\*,\*\*\*\* |
|  **INT** speed          | The maximum speed of the foreground, 0 for no limit (default: 0).***                                   |
|  **INT** region1        | The [region](#region) in which the scroll won't move, -1 for none (default: -1).***                    |
|  **INT** region2        | The [region](#region) in which the maximum speed is ignored, -1 for none (default: -1).***             |
|  **INT** flags1         | The [bit flags](#bit_flags) for the foreground graphic.                                                |
|  **INT** flags2         | The [bit flags](#bit_flags) for the background graphic.                                                |
|  **INT** follow         | The scrollID of the [scroll window](#scroll_window) to follow, -1 means none (default: -1).            |
|  **INT[6]** reserved    | Seven reserved integers.                                                                               |

  
|                |                                                                                                     |
| -------------- | --------------------------------------------------------------------------------------------------- |
| **\***         | These fields become *read only* when the scroll window is in automatic mode (see notes). |
| **\*\***       | [Processes](#Process) on the scroll use this [z](#z) value (see notes).                  |
| **\*\*\***     | These fields only make sense when the scroll window is in automatic mode (see notes).    |
| **\*\*\*\***   | The ratio is in percent: 200 means the background moves twice as slow.                              |

Notes
-----

There are two main methods of controlling a [scroll
window](#scroll_window). One is the manual way, thus changing
the values of the x0,y0,x1 and y1 manually. This mode is used when the
*camera* field is not set (is 0). When it is set with a
[processID](#processID), the scroll window is in automatic
mode and will follow that [process](#process)' coordinates and
will try to keep it centered. This can be influenced by other members of
the scroll struct.

The foreground is the plane to be controlled and the background moves
relative to the foreground. If you want to move the background manually,
you first need to set the scroll ratio to 0.

[Processes](#Process) in a scroll take over the
[z](#z) value of that scroll's z. Between processes on the
same scroll the [local variable](#local_variable)
[z](#z) of that process does have the expected effect.

