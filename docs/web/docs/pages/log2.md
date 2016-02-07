[**Up to Log.dll functions**](Functioncategory:Logdll "wikilink")

------------------------------------------------------------------------

Definition
----------

**FLOAT** log2 ( &lt;**FLOAT** n&gt; )

Returns a [logarithm](http://en.wikipedia.org/wiki/Logarithm) of number
*n* with base 2.

Parameters
----------

  ------------- ---------------------------------------------------
  **FLOAT** n   - The number that will be used for the logarithm.
  ------------- ---------------------------------------------------

Returns
-------

**FLOAT** : The logarithm of *n* with base 2.

Example
-------

    Import "log.dll";

    Global
        float logarithm=0.0;
    End

    Process main()
    Begin
        write_float(0,160,100,4,&logarithm);
        
        While(not(key(_esc)))
            If (key(_1)) logarithm=log2(1024); End 

            Frame;
        End
    End

Used in example: [import](import "wikilink"),
[write\_float](write_float "wikilink")(), [key](key "wikilink")(),
[log2](log2 "wikilink")()

<Category:functions> <Category:logdll> <Category:dll>
