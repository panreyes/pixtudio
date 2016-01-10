Definition
----------

**INT** minimize ( )

Iconifies/minimizes the window.

Returns
-------

**INT** : success

  ---- ------------------------------------------------------------------------------------
  0    - If minimizing/iconification is not support or was refused by the window manager.
  !0   - Success.
  ---- ------------------------------------------------------------------------------------

Example
-------

    import "mod_key"
    import "mod_wm"

    Process Main()
    Begin

        Repeat
            if(key(_M))
                while(key(_M)) frame; end
                minimize();
            end
            frame;
        Until(key(_ESC)||exit_status)

    End

Used in example: [key](key "wikilink")(),
[minimize](minimize "wikilink")(),
[exit\_status](exit_status "wikilink")

<Category:functions> <Category:programinteraction> <Category:mod_wm>
