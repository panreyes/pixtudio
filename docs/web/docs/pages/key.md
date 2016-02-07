Definition
----------

**INT** key( &lt;**INT** scancode&gt; )

Checks if a certain key is being pressed.

Parameters
----------

  ------------------ ------------------------------------------------------------------
  **INT** scancode   - The [scancode](scancodes "wikilink") of the key to be checked.
  ------------------ ------------------------------------------------------------------

Returns
-------

**INT** : [true](true "wikilink")/[false](false "wikilink"): Whether the
key is being pressed.

Notes
-----

Take a look at the [scancodes](scancodes "wikilink") for a complete
list.

Example
-------

    Program input_test;
    Begin

        While( !key(_esc) )

            delete_text(ALL_TEXT);

            if( key(_left) && !key(_right) )  
                write(0,160,120,4, "LEFT");
            end;
         
            if( key(_right) && !key(_left) ) 
                write(0,160,120,4, "RIGHT"); 
            end;

            frame;

        End;

        exit();

    End

Used in example: [delete\_text](delete_text "wikilink")(),
[write](write "wikilink")(), [exit](exit "wikilink")(),
[ALL\_TEXT](ALL_TEXT "wikilink")

This will output the words LEFT or RIGHT according to the keys you
press, or it will quit the program once ESCAPE is pressed.

<Category:functions> <Category:programinteraction> <Category:mod_key>
