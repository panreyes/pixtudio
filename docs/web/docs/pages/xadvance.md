Definition
----------

**INT** xadvance ( &lt;**INT** angle&gt; , &lt;**INT** distance&gt; )

Moves a process a certain distance in a certain direction.

Parameters
----------

  ------------------ -------------------------------------------------------------------------------------------
  **INT** angle      - The [angle](angle "wikilink") in which to move the process, in thousandths of a degree.
  **INT** distance   - The distance to move the process, in pixels.
  ------------------ -------------------------------------------------------------------------------------------

Returns
-------

**INT** : Successrate

  --------------------------- ------------
  [true](true "wikilink")     - Success.
  [false](false "wikilink")   - Error.
  --------------------------- ------------

Example
-------

    Program example;
    Global
        myproc;

    Begin
     
        myproc=proc();

        Loop
            frame;
        End
    End

    Process proc();
    Begin

        x=100;
        y=100;

        Loop
            xadvance(90000,10); //moves the process vertically (90 degrees) 10 pixels
            frame;
        End

    End

<Category:functions> <Category:processinteraction> <Category:mod_grproc>
