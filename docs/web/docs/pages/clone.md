Syntax
------

**Clone**

:   &lt;sentences&gt;

**End**

Description
-----------

The [clone](#clone) command creates a copy of the actual
process which is called a "child process." The original process is then
called the "parent process".

Only the child process will run the sentences between the keyword CLONE
and the keyword END.

Example
-------

    import "mod_key";
    import "mod_map";
    import "mod_video";
    import "mod_proc";

    Process Main()
    Begin

        squares();

        repeat
            frame;
        until(key(_ESC));

        let_me_alone();

    End

    Process squares()
    Private
        int advance;
    Begin

        graph = map_new(5,5,16);
        map_clear(0,graph,rgb(255,0,255));
        advance = 1;

        clone
            graph = map_clone( 0, graph );
            map_clear(0,graph,rgb(255,255,255));
            advance = 2;
        end

        loop
            x += advance;
            frame;
        end
        map_unload(0,graph);

    End

Used in example: [key](#key)(),
[map\_new](#map_new)(), [map\_clear](#map_clear)(),
[rgb](#rgb)(), [map\_unload](#map_unload)() This
example shows two squares. One is the child process, that is the white,
and the other is the parent process.
