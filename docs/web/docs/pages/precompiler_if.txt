<category:precompiler>

Definition
----------

**\#if** <what to check>

:   <if block>

\['''\#else

:   <else block>\]

**\#endif**

Checks if *what to check* is true. If it is, the code in *if block* will
be compiled. If it isn't, the code in *else block* will be compiled or
when there is no *else block*, the compiler will continue after
[\#endif](precompiler_endif "wikilink").

Example
-------

Consider a define to set the framepercentage in a certain process. Now
for some reason you might want to just have a frame; compiled when that
define is set to *100*.

    Loop
        #ifdef FRAMEPERC
            #if FRAMEPERC == 100
                frame;
            #else
                frame(FRAMEPERC);
            #endif
        #else
            frame;
        #endif
    End

Used in example: [Loop](Loop "wikilink"), [End](End "wikilink"),
[frame](frame "wikilink"), [\#if](precompiler_if "wikilink"),
[\#else](precompiler_else "wikilink"),
[\#endif](precompiler_endif "wikilink")
