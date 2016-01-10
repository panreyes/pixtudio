[**Up to LCD.DLL Functions**](Functioncategory:Lcddll "wikilink")

------------------------------------------------------------------------

Definition
----------

**INT** LCD\_About ( )

Tells the user about [LCD.DLL](LCD_DLL "wikilink"), using the [Fenix
console](Fenix_console "wikilink").

Returns
-------

**INT** : The current LCD.DLL version (integer).

Example
-------

    Program example;
        include "LCD.fh";
    Begin

        LCD_About();
       
        Loop
            frame;
        End

    End

<Category:functions> <Category:lcddll> <Category:dll>
