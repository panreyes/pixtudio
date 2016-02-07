List of Operators
-----------------

### General

  --------------------------- ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  *Operator*                  - *Description*
  Type                        - Get the [ProcessTypeID](ProcessTypeID "wikilink") of a [ProcessType](ProcessType "wikilink") or define a new [datatype](datatype "wikilink"). See [Type](Type "wikilink").
  . <small>(period)</small>   - Element access. `<struct>.<element>`. In case of a struct array, if no arrayelement is specified, it points to \[0\] (see [example](#Example "wikilink")).
  --------------------------- ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

### Maths

  ------------ ------------------------
  *Operator*   - *Description*
  +            - Addition.
  -            - Deduction
  \*           - Multiplication.
  /            - Division.
  %            - Modulus (remainder).
  ------------ ------------------------

### Logic

  ------------ ---------------------------------------- ---------------------------------
  *Operator*   - *Description*
  <nowiki>     </nowiki>
  &&           - AND. Both.
  \^\^         - XOR. One or the other, but not both.
  !            - NOT.
  ------------ ---------------------------------------- ---------------------------------

### Bitwise

(Logical operation per bit.)

  ------------ ---------------------------------------------------------------------------
  *Operator*   - *Description*
  |            - BOR. One or the other or both.
  &            - BAND. Both.
  \^           - BXOR. One or the other, but not both.
  \~           - BNOT.
  &lt;&lt;     - Bitshift left, causes bits to move left a certain number of positions.
  &gt;&gt;     - Bitshift left, causes bits to move right a certain number of positions.
  ------------ ---------------------------------------------------------------------------

### Memory

  ------------ ----------------------------------------------------------------------------------------------------
  *Operator*   - *Description*
  &            - OFFSET. Get the memory address of a variable. See [pointer](pointer "wikilink").
  \*           - POINTER. Get access to the variable a pointer is pointing to. See [pointer](pointer "wikilink").
  ------------ ----------------------------------------------------------------------------------------------------

Example
-------

    Type _point
        int x;
        int y;
    End

    Global
        int int_1 = 1;
        int int_3 = 3;
        int int_4 = 4;
        int someint = -5;
        String somestring = "AAP";
        String anotherstring = "BEER";
        byte somebyte = 6;
        signed byte sbyte = -2;
        byte b_5 = 5;
        byte b_12 = 12;
        Struct Person[9]
            string name;
            int age;
        End
        _point myPoint;
    End

    Process Main()
    Begin

        say("---------- maths");

        say(int_3 + int_4);
        say(int_3 * int_4 + 1);

        say("---------- strings with numerical datatypes");

        say(somestring + anotherstring);
        say(somestring + ": " + int_3);
        say(anotherstring + ": " + int_3*sbyte);

        say("---------- mixed numberical types and typecasting");

        say(somebyte+someint);
        say((signed byte)someint);
        say((unsigned byte)someint);

        say("---------- logic");

        say(int_1&&int_4);
        say(int_4==int_3+int_1);
        say(!(somestring==anotherstring));

        say("---------- bitwise");

        say(b_5|b_12);  // 00000101
                        // 00001100
                        // -------- |
                        // 00001101 = 13

        say(b_5&b_12);  // 00000101
                        // 00001100
                        // -------- &
                        // 00000100 = 4

        say(b_5^b_12);  // 00000101
                        // 00001100
                        // -------- ^
                        // 00001001 = 9

        say(~b_12);     // 00001100
                        // -------- ~
                        // 11110011 = 243

        person.name    = "Mies"; // these are the same
        person[0].name = "Mies"; //

        person[1].name = "Aap";
        person[2].name = "Noot";
        // ...etc...
        person[9].name = "Last person"; // last array element

        setXY(&myPoint);

        Repeat
            frame;
        Until(key(_ESC))

    End

    Function int setXY(_point* p)
    Begin
        p.x = 3; // this is actually (*p).x = 3, but . can be used like this
        p.y = 5; // this is actually (*p).y = 5, but . can be used like this
        return 0;
    End

Used in example: [say](say "wikilink")(), [key](key "wikilink")(),
[Global](Global "wikilink"), [Type](Type "wikilink"),
[Struct](Struct "wikilink"), [Array](Array "wikilink"),
[Pointer](Pointer "wikilink"), [period](period "wikilink")

This will result in something like:\

<Category:General>
