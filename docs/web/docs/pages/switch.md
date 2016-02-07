Syntax
------

**Switch** **(** &lt;value&gt; **)**
   ( **Case** &lt;value&gt; **:**
        [ &lt;code&gt; ]
   **End** )
   [ **Default:**
       [ &lt;code&gt; ]
   **End** ]
**End**

Description
-----------

A *switch* is used to control the flow of a program by means of
comparing a value to other values and executing the code associated with
the correct value.

    switch ( <value> )
        case <value1>:
            // code1
        end
        case <value2>:
            // code2
        end
        default:
            // code3
        end
    end

When the **switch** is reached it will compare *value* with the values
in the **case**s, going from top to bottom. When a case matches, that
code is executed and the **switch** is exited. This is different from
the **switch** in C and probably more languages, because there the
**switch** is only exited when a break is reached or
when the **switch** ends. In Bennu there is no break; for the switch,
though.

A value in a **case** can also be a range: `<lowervalue>..<uppervalue>`.
Both the *lowervalue* and the *uppervalue* are part of the range.

You can also specify multiple values in a **case**, separated by a
comma: `<value1>,<value2>,...<code>`. These values can also be
ranges.

Example
-------

A scoretext function. Notice the **default**: when the points can be
0..100, that code should never be executed. However, an error can occur
and blurting an error to the user is not that fancy, so this is a way of
showing to the programmer there is an error, but still the user gets
some message. In such cases, **default** can be handy. Of course that
code could just as easily have been put under the **switch** with the
same result, in this case, because every case does a return.

    Function String scoretext( int points )
    Begin

        Switch( points )
            Case 100:
                return "Perfect!";
            End
            Case 90..100:
                return "Awesomely cool, dude!";
            End
            Case 80..90:
                return "You're getting the hang of it!";
            End
            Case 60..80:
                return "Not too shabby, mate.";
            End
            Case 50..60:
                return "Practice some more.";
            End
            Case 30..50:
                return "Dude...weak.";
            End
            Case 1..30:
                return "That's just awful";
            End
            Case 0:
                return "No points? n00b!";
            End
            Default:
                return "I dunno what you did, but...";
            End
        End

    End
