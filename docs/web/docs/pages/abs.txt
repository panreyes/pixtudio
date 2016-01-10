Definition
----------

**FLOAT** abs ( &lt;**FLOAT** value&gt; )

Returns the absolute value of *value*.

Parameters
----------

  ----------------- --------------
  **FLOAT** value   - The value.
  ----------------- --------------

Returns
-------

**FLOAT** : The absolute value of *value*.

Example
-------

    Global
        float value1;
        int value2;
    End

    Process Main()
    Begin

        write_float(0,0, 0,0,&value1);
        write_int(0,0,10,0,&value2);

        value1 = abs(3);
        value2 = abs(-4);

        Repeat
            frame;
        Until(key(_ESC))

    End

Used in example: [write\_float](write_float "wikilink")(),
[write\_int](write_int "wikilink")(), [abs](abs "wikilink")(),
[key](key "wikilink")()

<Category:functions> <Category:math> <Category:mod_math>
