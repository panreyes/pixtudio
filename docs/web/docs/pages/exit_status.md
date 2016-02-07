<category:variables> <category:predefined> [category:global
variables](category:global_variables "wikilink") <category:libwm>

[**Up to Global Variables**](Global_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** exit\_status

**exit\_status** is a [predefined](predefined "wikilink") [global
variable](global_variable "wikilink"), holding whether or not Bennu
received a QUIT event this frame. A QUIT event is generated for example
by pressing the X button of the window.

  --------------------------- ---------------------------
  *Value*                     - *Description*
  [false](false "wikilink")   - There is no QUIT event.
  [true](true "wikilink")     - There is a QUIT event.
  --------------------------- ---------------------------


