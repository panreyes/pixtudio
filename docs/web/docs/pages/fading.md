<category:variables> <category:predefined> [category:global
variables](category:global_variables "wikilink") <category:librender>

[**Up to Global Variables**](Global_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** fading = false

**Fading** is a [global variable](global_variable "wikilink"), holding
whether the screen is currently fading. This can be caused by the
functions [fade](fade "wikilink")(), [fade\_on](fade_on "wikilink")() or
[fade\_off](fade_off "wikilink")(). Its value will be
[true](true "wikilink") if there is fading going on and
[false](false "wikilink") if not.

Example
-------

    Program faders;
    Private
        int text_id;
    Begin

        // Write something
        text_id = write(0,160,100,4,"Look at this fading text!");

        // Fade screen on and off
        fade_off_and_on();

        // Wait for ESC key
        Repeat
            frame;
        Until(key(_ESC))

        // Kill all other processes and clear up text
        let_me_alone();
        delete_text(text_id);

    End

    Process fade_off_and_on()
    Begin
        Loop
            fade(0,0,0,4); // Fade to black
            while(fading) frame; end // Wait for the fading to finish
            fade(100,100,100,4); // Fade to normal
            while(fading) frame; end // Wait for the fading to finish
        End
    End

Used in example: [write](write "wikilink")(), [key](key "wikilink")(),
[let\_me\_alone](let_me_alone "wikilink")(),
[delete\_text](delete_text "wikilink")(), [fade](fade "wikilink")()
