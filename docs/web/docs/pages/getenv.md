Definition
----------

**STRING** getenv ( &lt;**STRING** variablename&gt; )

Returns the value of an environment variable (like PATH).

Parameters
----------

  ------------------------- -------------------------------------------------
  **STRING** variablename   - The name of the variable to get the value of.
  ------------------------- -------------------------------------------------

Returns
-------

**STRING** : The value of the variable.

  ----- -------------------------------------
  ""    - The variable is invalid or empty.
  !""   - The value of the variable.
  ----- -------------------------------------

<Category:functions> <Category:programinteraction> <Category:mod_sys>
