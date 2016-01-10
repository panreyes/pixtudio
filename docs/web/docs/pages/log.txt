[**Up to Log.dll functions**](Functioncategory:Logdll "wikilink")

------------------------------------------------------------------------

Definition
----------

**FLOAT** log ( &lt;**FLOAT** n&gt; , \[&lt;**FLOAT** b&gt;\] )

Returns a [logarithm](http://en.wikipedia.org/wiki/Logarithm) of number
*n* with base *b*. If *b* is not specified, the number 10 will be used
as base.

Parameters
----------

  ---------------- ---------------------------------------------------
  **FLOAT** n      - The number that will be used for the logarithm.
  **FLOAT** base   - The base that will be used for the logarithm.
  ---------------- ---------------------------------------------------

Returns
-------

**FLOAT** : The logarithm of *n*.

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
            If (key(_1)) logarithm=log(1000,9); End 
            If (key(_2)) logarithm=log(1000); End

            Frame;
        End
    End

Used in example: [import](import "wikilink"),
[write\_float](write_float "wikilink")(), [key](key "wikilink")(),
[log](log "wikilink")()

<Category:functions> <Category:logdll> <Category:dll>
