<category:precompiler>

Definition
----------

**\#ifndef** <what to check>

:   <if block>

\['''\#else

:   <else block>\]

**\#endif**

Checks if *what to check* was previously defined in the code. If it
isn't, the code in *if block* will be compiled. If it is, the code in
*else block* will be compiled or when there is no *else block*, the
compiler will continue after [\#endif](precompiler_endif "wikilink").

It is the opposite of [\#ifdef](precompiler_ifdef "wikilink").
