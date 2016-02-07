Definition
----------

**FLOAT** pow ( &lt;**FLOAT** base&gt; , &lt;**FLOAT** power&gt; )

Returns *base* to the power of *power* (*base*\^*power*).

Parameters
----------

  ----------------- --------------
  **FLOAT** base    - The base.
  **FLOAT** power   - The power.
  ----------------- --------------

Returns
-------

**FLOAT** : *base* to the power of *power* (*base*\^*power*).

Example
-------

    Program powerful;
    Global
        float value1;
        int   value2;
    Begin

        write_float(0,0, 0,0,&value1);
        write_int  (0,0,10,0,&value2);

        value1 = pow(2.3,4.6);
        value2 = pow(2  ,3  );

        Repeat
            frame;
        Until(key(_ESC))

    End

Used in example: [write\_float](write_float "wikilink")(),
[write\_int](write_int "wikilink")(), [pow](pow "wikilink")(),
[key](key "wikilink")()

<Category:functions> <Category:math> <Category:mod_math>
