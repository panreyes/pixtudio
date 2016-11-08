Datatype declaration
--------------------

### Definition

```
Type {name}
    {variables}
End
```

Creates a new [datatype](#datatype). It's handled as if it
were a [struct](#struct), so the declared variables are
members of the struct.

While it's a convention to use a `_` as first character in the name of
a datatype, it's not mandatory.

When used as an [argument](#argument) in a
[function](#function) or [process](#process), the
[parameter](#parameter) is not a copy, but the variable
itself, as shown in the first example, and any change made to the
parameter is also changed in the argument. It's more elegant to use a
[pointer](#pointer) though, as it also displayed.

### Example

A file with name and path. Note that the assignment `myFile2 = myFile;`
makes a copy of `myFile` and throws it into `myFile2`, which is normal.
But when it's used as an argument in a function, the parameter is not a
copy but the `_file` itself.

```
    Type _file
        String path;
        String name;
    End

    Process Main()
    Private
        _file myFile;
        _file myFile2;
    Begin

        myFile.path = "C:\";
        myFile.name = "autoexec.bat";
        say("1: " + myFile.path + myFile.name);

        myFile2 = myFile;
        myFile2.name = "config";
        say("1: " + myFile.path + myFile.name);
        say("2: " + myFile2.path + myFile2.name);

        setName(myFile,"pagefile");
        say("1: " + myFile.path + myFile.name);

        setName2(&myFile2,"pagefile");
        say("2: " + myFile2.path + myFile2.name);

        Repeat
            frame;
        Until(key(_ESC))

    End

    Function setName(_file f, string name)
    Begin
        f.name = name;
    End

    Function setName2(_file* f, string name)
    Begin
        f.name = name; // this is actually (*f).name = name, but . can be used like this
    End
```

Used in example: [say](#say)(), [key](#key)(),
[Pointer](#pointer)

A point with x and y.

```
    // Declare the type _point
    Type _point
        float x;
        float y;
    End

    // Declare the function distance(), because the function returns a datatype
    // other than int, so it needs to be declared before usage.
    Declare float distance(_point a,_point b)
    End

    Process Main()
    Private
        _point p1,p2;
    Begin

        p1.x = 15.3;
        p1.y = 34.9;
        p2.x = 165.4;
        p2.y = 137.2;

        write(0,0,0,0,"Distance: " + distance(p1,p2));
        drw_line(p1,p2);

        Repeat
            frame;
        Until(key(_ESC))

    End

    Function float distance(_point a, _point b)
    Begin
        return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
    End

    Function int drw_line(_point a, _point b)
    Begin
        return draw_line( a.x , a.y , b.x , b.y );
    End
```

Used in example: [write](#write)(), [key](#key)(),
[sqrt](#sqrt)(), [draw_line](#draw_line)()

ProcessType
-----------

### Definition

```
Type {processname}
```

Acquires the [processTypeID](#processtypeid) of a
[processType](#processtype) or
[function](#function). This can be useful for example with
[get_id](#get_id)() and [signal](#signal)().

### Example

```
    Program example;
    Private
        proc proc_id; //int could be used too
    Begin

        // Start 3 proc's
        proc();
        proc();
        proc();

        // Display all alive proc's
        y = 0;
        while( (proc_id=get_id(type proc)) )
            write(0,0,(y++)*10,0,"proc: " + proc_id);
        end

        // Wait for key ESC
        Repeat
            frame;
        Until(key(_ESC))

    End

    Process proc()
    Begin
        Loop
            frame;
        End
    End
```

Used in example: [get_id](#get_id)(), [write](#write)(), [key](#key)()
