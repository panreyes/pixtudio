<category:general> <category:scroll>

Definition
----------

A [scroll window](scroll_window "wikilink") is a
[region](region "wikilink") in which a scroll has been started by
[start\_scroll](start_scroll "wikilink")() and setup with the [global
variable](global_variable "wikilink") [scroll](scroll "wikilink"). This
scroll window provides a view window into the scroll that has been setup
there, with certain background and foreground
[graphics](graphics "wikilink"). The view window can be 'scrolled' over
the scroll (and the graphics).

The use of scrolls can be various, but mostly they are used for
scrolling games, like
[sidescrollers](http://en.wikipedia.org/wiki/Side-scrolling_video_game).

[Processes](Process "wikilink") can also be added to a scroll (see the
[global variable](global_variable "wikilink")
[ctype](ctype "wikilink")), in which case a lot of things related to
that process change.

-   The [graphic](graphic "wikilink") of the process is not drawn to the
    screen, but to the scroll window, using the
    [region](region "wikilink") of the scroll.
-   The [z](z "wikilink") of an added process only has a meaning to the
    scroll window and compared to other processes added to the same
    scroll, meaning from a user perspective, the process is drawn at the
    z value of the scroll. If two processes are added to the same
    scroll, the one with the lower z value will be drawn over the
    other one.
-   The [x](x "wikilink")- and [y](y "wikilink")-coordinates are not
    relative to the upper left corner of the *screen*, but relative to
    the upper left corner of the *scroll*.

You can control scrolls in multiple ways.

-   Change the scroll coordinates directly using `x0`, `y0`, `x1`, `y1`
    in the [global variable](global_variable "wikilink")
    [scroll](scroll "wikilink"). Be sure to alter the correct scroll.
-   Tell the scroll to 'follow' another scroll, by using
    `[[scroll]].follow`.
-   Use a 'camera' process, which the scroll try to follow, by using
    `[[scroll]].camera`.

More about scrolls:

-   A scroll with a lower z value will be drawn over a scroll with a
    lower z value.
-   The foreground is the plane to be controlled and the background
    moves relative to the foreground.

Example
-------

    Const
        SCREEN_WIDTH = 320;
        SCREEN_HEIGHT = 200;
        SCREEN_DEPTH = 8;
        MAP_WIDTH  = 500;
        MAP_HEIGHT = 400;
        SHIP_WIDTH  = 30;
        SHIP_HEIGHT = 30;
        SHIP_SPEED = 6;
    End

    Declare Process playership(int x, int y)
    End
    Declare Function int makeMap(int width, int height, int depth)
    End
    Declare Function int makeShipGfx(int width, int height, int depth)
    End

    Process Main()
    Private
        int map;
    Begin
        // Setup the screen
        set_mode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_DEPTH);

        // Create the background graphic
        map = makeMap(MAP_WIDTH,MAP_HEIGHT,SCREEN_DEPTH);

        // Start a new scroll
        // scrollNumber = 0
        // fileID = 0
        // foregroundGraphID = map
        // backgroundGraphID = 0: no background
        // region = 0: use entire screen
        // lockindicator = 0: don't repeat graphics
        start_scroll(0,0,map,0,0,0);

        // Start a controllable object on the scroll
        playership(320,200);

        // Wait till the key ESC is pressed
        Repeat
            frame;
        Until(key(_esc))

    OnExit
        // Kill all other processes
        let_me_alone();

        // Clean up memory used for map
        unload_map(0,map);
    End


    Process playership(int x, int y)
    Private
        int sp = SHIP_SPEED;
        int halfWidth;
        int halfHeight;
    Begin

        // This process should be displayed on a scroll only
        ctype = c_scroll;

        // This process should be tracked by the scroll
        Scroll.camera = id;

        // Create a graph for this process
        graph = makeShipGfx(SHIP_WIDTH,SHIP_HEIGHT,SCREEN_DEPTH);

        // Obtain the value of half the width of the graphic
        halfWidth  = graphic_info(0,graph,G_WIDTH )/2;
        halfHeight = graphic_info(0,graph,G_HEIGHT)/2;

        // React on keys LEFT and RIGHT
        Loop

            // Adjust x,y on input
            x+=(key(_right)-key(_left))*sp;
            y+=(key(_down)-key(_up))*sp;

            // Make sure the ship stays on the scroll
            if(x > MAP_WIDTH-halfWidth)
                x = MAP_WIDTH-halfWidth;
            elseif(x < halfWidth)
                x = halfWidth;
            end
            if(y > MAP_HEIGHT-halfHeight)
                y = MAP_HEIGHT-halfHeight;
            elseif(y < halfHeight)
                y = halfHeight;
            end

            frame;

        End

    OnExit
        // Clean up used memory for graph
        unload_map(0,graph);
    End

    Function int makeMap(int width, int height, int depth)
    Private
        int n;
        int x1,y1;
        int m;
    Begin

        // New map
        m = new_map(width,height,depth);

        // Put on some pretty stars
        rand_seed(100);
        for(n=0;n<1000;n++)
            map_put_pixel(0,m,rand(0,width),rand(0,height),rgb(150,170,200));
        end

        // Return it
        return m;

    End

    Function int makeShipGfx(int width, int height, int depth)
    Private
        int g;
    Begin

        // Return a map of one color (RGB(150,200,170))
        g=new_map(width,height,depth);
        map_clear(0,g,rgb(200,100,170));
        return g;

    End

Used in example: [set\_mode](set_mode "wikilink")(),
[start\_scroll](start_scroll "wikilink")(), [key](key "wikilink")(),
[let\_me\_alone](let_me_alone "wikilink")(),
[unload\_map](unload_map "wikilink")(),
[graphic\_info](graphic_info "wikilink")(),
[new\_map](new_map "wikilink")(), [rand\_seed](rand_seed "wikilink")(),
[rand](rand "wikilink")(), [rgb](rgb "wikilink")(),
[map\_put\_pixel](map_put_pixel "wikilink")(),
[map\_clear](map_clear "wikilink")(), [ctype](ctype "wikilink"),
[scroll](scroll "wikilink")
