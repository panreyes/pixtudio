Syntax
------

```
INT sizeof ( {datatype} )
```

Description
-----------

Calculates the size of a [block of memory](#memoryblock).
Returns the size in [bytes](#byte).

Parameters
----------

  * {datatype}   - The type, i.e. any valid bennu [datatypes](#datatypes). Can also be a user defined [types](#type) or [structs](#struct).

Returns
-------

**INT** : The size of the data type, in bytes.

Definition
----------

The `sizeof()` operator is used to calculate the size of datatypes. This
is important for creating dynamic data structures wich are created with
the functions [alloc](#alloc)(), [calloc](#calloc)()
and [realloc](#realloc)(). These three functions allocate
space in [bytes](#byte). For instance, an
[int](#int) in bennu is 4 bytes long. When dealing with data
structures of self-defined [types](#type), it can be tedious
to calculate the exact size manually. But this is not the only reason,
for instance, when a linked list is created, the
[struct](#struct) may be changed by the programmer, and in
that case the size changes. By using `sizeof()`, you can avoid the
problems of allocating too few or too much space.

Further reading
---------------

[General article about the use of
sizeof](http://en.wikipedia.org/wiki/Sizeof)

Example
-------

```
    // import modules
    IMPORT "mod_say";
    IMPORT "mod_debug";
    IMPORT "mod_mem";

    // user defined data type, should be 29 bytes in size.
    TYPE custom_datatype;
       int cat;
       int dog;
       
       byte kind;
       
       char name[19];
    END


    GLOBAL
      STRUCT custom_datatype2;
         char name[19];
         STRUCT animal[9];
            char remarks[255];

            int age;
            int speed;

            byte kind;
            byte fur_color;
            byte sound;    
            byte num_legs;
            bool can_fly;
            bool has_horns;
         END
            
      END

      int var1;             // 4 bytes
      byte var2;            // 1 byte
      float var3;           // 4 bytes

      char text1[4]="hello";     // 5 bytes
      string text2="world";       // 4 bytes, is sort of pointer thingy 

      int integer_array[255];      // (0-255), 256 x 4 bytes = 1024 bytes


    PROCESS main();

    BEGIN

       say("");
       say("");
       say("sizeof() demonstration");
       say("");
       say("");
       say ("the size of custom_datatype: "+sizeof(custom_datatype)+" is bytes");
       say ("the size of custom_datatype2: "+sizeof(custom_datatype2)+" is bytes");
       say ("the size of var1: "+sizeof(var1)+" is bytes");
       say ("the size of var2: "+sizeof(var2)+" is bytes");
       say ("the size of var3: "+sizeof(var3)+" is bytes");
       say ("the size of text1: "+sizeof(text1)+" is bytes");
       say ("the size of text2: "+sizeof(text2)+" is bytes");
       say ("the size of int_array: "+sizeof(integer_array)+" is bytes");
       
    END
```

Used in example: [alloc](#alloc)(),
[calloc](#calloc)(), [realloc](#realloc)(),
[struct](#struct), [type](#type),
[say](#say)(), [Global](#global)
