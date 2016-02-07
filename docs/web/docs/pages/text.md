<category:general> <category:texts>

Definition
----------

A text is a text written on screen with [texts
functions](Functioncategory:texts "wikilink"), like
[write](write "wikilink")() or [write\_int](write_int "wikilink")(). A
text is addressed using the associated [TextID](TextID "wikilink").

There are two kinds of texts:

-   Static text is any text written with [write](write "wikilink")(); it
    is static, because the content of the text cannot be changed after
    writing, but the text can be moved and deleted.
-   Dynamic text is any text written with write\_xxx() functions; it is
    dynamic because the content of the text always reflects the current
    value of the variable specified. Of course moving and deleting is
    also possible.

Writing texts
-------------

There are multiple ways to write texts: the write() function,
write\_xxx() functions and the write\_in\_map() function. With the first
two, some the [global variable](global_variable "wikilink")
[text\_z](text_z "wikilink") is important and with all three of them,
the following are important:

-   The functions [set\_text\_color](set_text_color "wikilink")() and
    [get\_text\_color](get_text_color "wikilink")()
-   The [font](font "wikilink")
-   The [alignment](alignment "wikilink")
-   The global variable [text\_flags](text_flags "wikilink")

Also the function [move\_text](move_text "wikilink")() can be handy, as
it moves a previously written text to a different location.

Example
-------

    Program texts;
    Const
        maxtexts = 10;
    Private
        int textid[maxtexts-1];
        string str;
        float flt;
    Begin

        // Set FPS
        set_fps(60,0);

        // Init text settings:
        text_z = 0;
        text_flags = 0;
        set_text_color(rgb(255,255,255));

        // Write some texts
        textid[0] = write(0,0,0,0,"FPS:");
        textid[1] = write_int(0,30,0,0,&fps);
        textid[2] = write_string(0,160,95,1,&str);
        textid[3] = write_float(0,160,105,0,&flt);

        // Show z workings
        set_text_color(rgb(50,150,150));
        textid[4] = write(0,20,20,0,"Underlying text");
        text_z = -1;
        set_text_color(rgb(255,255,255));
        textid[5] = write(0,22,22,0,"On top text");

        // Update the texts until ESC is pressed
        Repeat
            // Notice the texts get updated as the values of str and flt changes.
            // The same goes for the value of fps.
            str = "This program is running for " + time()/100 + " seconds.";
            flt = (float)time()/100;
            frame;
        Until(key(_esc));

        // Delete the texts (this section would be good for OnExit)
        for(x=0; x<maxtexts; x++)
            if(textid[x]!=0)
                delete_text(textid[x]);
            end
        end

    End

Used in example: [set\_fps](set_fps "wikilink")(),
[set\_text\_color](set_text_color "wikilink")(),
[write](write "wikilink")(), [write\_int](write_int "wikilink")(),
[write\_string](write_string "wikilink")(),
[write\_float](write_float "wikilink")(), [key](key "wikilink")(),
[delete\_text](delete_text "wikilink")(), [text\_z](text_z "wikilink"),
[text\_flags](text_flags "wikilink"), [fps](fps "wikilink")
