Syntax
------

```pixtudio-syntax
IF ( <condition> )
   [ <code> ]
( ELSEIF ( <condition> )
   [ <code> ] ) 
[ ELSE
   [ <code> ] ]
END
```

Description
-----------

**if** statements are used to control the flow of your program by means
of checking conditions.

```pixtudio
    if( <condition1> )
        // code1
    elseif( <condition2> )
        // code2
    elseif( <condition3> )
        // code3
    else
        // code4
    end
    // code5
```

The action that will be performed depends on the *condition*s:
- If at the time the program reaches this **if** codeblock *condition1* evaluates as [true](#true), then *code1* will be executed and then *code5*.
- If *condition1* evaluates to [false](#false), the program will evaluate the next **elseif** and check if it is true or false: if *condition2* evaluates as:
    - **true**, *code2* and then *code5* is executed.
    - **false**, the program will check the next **elseif** and do the same thing over.

If all other conditions evaluate to false and an **else** condition is present, the code in the **else** block will be executed. This code block thus acts as a default action that will be performed when no other condition is **true**.

The **if** statement must be closed with an **end** statement.

Example
-------

### Execute function

This is a little example of how to make a function perform a certain
task depending on a command.

    Function int execute(String command, int* params)
    Begin

        if( command == "SEND" )
            NET_Send(atoi(params[0]),params[1]);
        elseif( command == "RECV" )
            NET_Recv(atoi(params[0]));
        elseif( command == "INIT" )
            NET_Init(atoi(params[0]),atoi(params[1]),atoi(params[2]));
        elseif( command == "QUIT" )
            NET_Quit();
        else
            // error: command unknown
            return -1;
        end

        return 0;

    End

### Movement

Movement with **If**s.

    Loop
        if(key(_up))    y-=5; end
        if(key(_down))  y+=5; end
        if(key(_left))  x-=5; end
        if(key(_right)) x+=5; end
    End

Of course, this is faster:

    Loop
        y += 5 * (key(_down )-key(_up  ));
        x += 5 * (key(_right)-key(_left));
    End
