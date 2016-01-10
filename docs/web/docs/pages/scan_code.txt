<category:variables> <category:predefined> [category:global
variables](category:global_variables "wikilink") <category:mod_key>

[**Up to Global Variables**](Global_variables "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** scan\_code

Scan\_code is defined in the module [mod\_key](mod_key "wikilink") and,
in contrast to [ascii](ascii "wikilink"), it contains the last key
pressed, not the last character. That means “A” and “a” will have the
same scan\_code, but different [ascii](ascii "wikilink") value.

Notes
-----

Take a look at the [scancodes](scancodes "wikilink") for a complete
list.

Example
-------

    import "mod_text"
    import "mod_key"
    import "mod_video"

    process main()
    begin
        set_mode(640,320);

        write( 0, 60, 10, 0, "Use lower and upper case characters to see the difference");
        write( 0, 60, 20, 0, "between ascii and scan_code.    (ESC to exit)  ");

        write( 0, 60, 40, 0, "ascii: ");
        write_var( 0, 110, 40, 0, ascii);

        write( 0, 26, 50, 0, "scan_code: ");
        write_var( 0, 110, 50, 0, scan_code);

        while ( !key(_esc))
            frame;
        end
    end   
