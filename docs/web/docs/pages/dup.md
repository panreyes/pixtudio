Syntax
------

**Dup** [ **(** {value} **)** ] **;**

Description
-----------

The `dup(value);` return a space data filled with the given value. For
example a `10 dup(0)` return an array of 10 elements, all with a zero
value.

Example 1
---------

```
    import "mod_say";

    global
        array[] = 10 dup(0);

    begin
        say ( sizeof(array)/sizeof(array[0]) );
    end
```

This example prints 10 because the size of array is ten and the size of
the first element is one.

Example 2
---------

```
    import "mod_say";

    global
        int array[5] = 1 , 4 dup(0);
        int arrayPosition;
    begin
        for ( arrayPosition = 0 ; arrayPosition < 5 ; arrayPosition = arrayPosition + 1 )
            say ( array[arrayPosition] );
        end
    end
```

This example prints:

    1 0 0 0 0

As it duplicates "0" four times in the array data.
