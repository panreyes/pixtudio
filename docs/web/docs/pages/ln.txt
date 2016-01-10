[**Up to Log.dll functions**](Functioncategory:Logdll "wikilink")

------------------------------------------------------------------------

Definition
----------

**FLOAT** ln ( &lt;**FLOAT** n&gt; )

Returns the [natural
logarithm](http://en.wikipedia.org/wiki/Natural_logarithm) of number *n*
([logarithm](http://en.wikipedia.org/wiki/Logarithm) with base ε
(Euler)).

Parameters
----------

  ------------- ---------------------------------------------------
  **FLOAT** n   - The number that will be used for the logarithm.
  ------------- ---------------------------------------------------

Returns
-------

**FLOAT** : The natural logarithm of *n*.

Example
-------

    Import "log.dll";

    Global
        float logarithm=0.0;
    End

    Process main()
    Begin
        write_float(0,160,100,4,&logarithm);
        
        While(not(key(_ESC)))
        If (key(_1)) logarithm=ln(13.37); End 

            Frame;
        End
    End

Used in example: [import](import "wikilink"),
[write\_float](write_float "wikilink")(), [key](key "wikilink")(),
[ln](ln "wikilink")()

<Category:functions> <Category:logdll> <Category:dll>
