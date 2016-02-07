[**Up to LCD.DLL Functions**](Functioncategory:Lcddll "wikilink")

------------------------------------------------------------------------

Definition
----------

**STRING** LCD\_Version ( )

Returns the current [LCD.DLL](LCD_DLL "wikilink") version.

Returns
-------

**STRING** : The current [LCD.DLL](LCD_DLL "wikilink") version (string).

Example
-------

    Program example;
        include "LCD.fh";
    Private
        string lcdver;
    Begin

        lcdver = LCD_Version();
       
        Loop
            frame;
        End

    End

<Category:functions> <Category:lcddll> <Category:dll>