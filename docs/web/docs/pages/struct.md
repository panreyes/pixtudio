Definition
----------

```
Struct {struct name}
    {Members}
End
```

**Struct**s are [datatypes](#datatypes) able to contain
variables of all datatypes.

To address a member of a struct, use the `.` operator:
`{structname}.{membername}`. Like all datatypes, one can have a whole
range of them, as displayed in the example (also see
[Array](#array)).

There are two ways to fill a struct on declaration:

* Per member
* Afterwards, like [Arrays](#array).

See the examples on how to do it.

## Example

Structs can be handy for many aspects of programming.

### Grouping of variables

This is for clarity and to avoid colliding variable names.

```
    Struct Fileinfo
        String name;
        String path;
    End
```

Note that the struct [fileinfo](#fileinfo) is a predefined
global variable.

Maybe you want to group some other data, like settings of the screen:

```
    Struct Window
        int width = 320;
        int height = 200;
        int depth = 8;
    End
```

or (using other initializing syntax):

```
    Struct Window
        int width;
        int height;
        int depth;
    End = 320,200,8;
```

This example can also be done by [defining your own
type](#type).

### Multiple identical data groups

```
    Struct Ship[9]
        int x;
        int y;
        int speed;
        int angle;
    End
```

There are 10 `Ship`s now. The data can be accessed like:

```
    Ship[0].speed++;
    Ship[8].angle = 0;
```
