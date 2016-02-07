[**Up to LCD.DLL Functions**](Functioncategory:Lcddll "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** LCD\_IntVersion ( )

Returns the current [LCD.DLL](LCD_DLL "wikilink") version.

Returns
-------

**INT** : The current [LCD.DLL](LCD_DLL "wikilink") version (int).

Example
-------

    Program example;
        include "LCD.fh";
    Private
        int lcdver;
    Begin

        lcdver = LCD_IntVersion();
       
        Loop
            frame;
        End

    End

<Category:functions> <Category:lcddll> <Category:dll>
