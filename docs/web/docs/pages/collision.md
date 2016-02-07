Definition
----------

**INT** collision ( &lt;**INT** processID|processTypeID&gt; )

Checks if a [process](process "wikilink") collided with the process
calling Collision().

When a [processTypeID](processTypeID "wikilink") is specified, there
could be multiple fitting collisions. In this case, collision() returns
a [processID](processID "wikilink") on each subsequent call, until it
returns 0. This can be reset by use of the [frame](frame "wikilink");
statement, and in such case, frame(0); can be handy.

Parameters
----------

  --------------------------------- ---------------------------------------------------------------------------------------------
  **INT** processID|processTypeID   - The ProcessID of the process or the ProcessTypeID of the type of processes to be checked.
  --------------------------------- ---------------------------------------------------------------------------------------------

Returns
-------

**INT** : The ID of the collided process.

  ------- -------------------------------------------------------------------
  0       - No collision
  &gt;0   - The processID of the process colliding with the current process
  ------- -------------------------------------------------------------------

Example
-------

    Process SpaceShip( int file , int graph , int x , int y , int angle , int maxspeed , int maxturnspeed )
    Private
        int speed;
        int collisionID;
        string text;
    Begin
        write_string(0,0,0,0,&text);
        Loop
            // Handle movement
            speed+=key(_up)*(speed<maxspeed)-key(_down)*(speed>-maxspeed);
            angle+=(key(_left)-key(_right))*maxturnspeed;
            advance(speed);
            // Handle collision
            if( (collisionID = collision(type main)))
                text = "collision with: " + collisionID;
            else
                text = "no collision";
            end
            frame;
        End
    End

    Process Main()
    Private
        int map;
    Begin

        // Create the graph for the ship
        map = new_map(20,20,8);
        map_clear(0,map,rgb(0,255,255));

        // Create the graph for the Main process
        graph = new_map(50,50,8);
        map_clear(0,graph,rgb(255,255,0));

        // Position the main process and create the ship
        x = y = z = 100;
        SpaceShip(0,map,100,100,0,20,5000);

        Repeat
            frame;
        Until(key(_ESC))

        let_me_alone();

    End

Used in example: [write\_string](write_string "wikilink")(),
[key](key "wikilink")(), [collision](collision "wikilink")(),
[new\_map](new_map "wikilink")(), [map\_clear](map_clear "wikilink")(),
[advance](advance "wikilink")(),
[let\_me\_alone](let_me_alone "wikilink")(), [graph](graph "wikilink"),
[type](type "wikilink")

<Category:functions> <Category:processinteraction> <Category:mod_grproc>
