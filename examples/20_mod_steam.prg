import "mod_steam"
import "mod_text"
import "mod_video"
import "mod_key"
import "mod_map"
import "mod_file"
import "mod_proc"
import "mod_rand"
import "mod_say"
import "mod_draw"

Global
    int scr_width=800, scr_height=600;
End

Process bouncer(graph)
Private
    int v_x = 5, v_y = 5;
Begin
    if(graph == -1)
        return;
    end

    x = scr_width / 2 + rand(-200, 200);
    y = scr_height / 2 + rand(-200, 200);
    v_x += rand(-2, 2);
    v_y += rand(-2, 2);
    Loop
        if(x > scr_width - 20 || x < 20)
            v_x = -v_x;
        End
        if(y > scr_height - 20 || y < 20) 
            v_y = -v_y;
        End
        x += v_x;
        y += v_y;

        FRAME;
    End

OnExit
    if(graph > -1)
        map_unload(0, graph);
    End
End

Process named_bouncer(int graph, string text)
Private
    int v_x = 5, v_y = 5;
    int w, h;
    int text_graph;
Begin
    if(graph < 0)
        return;
    end

    w = graphic_info(0, graph, G_WIDTH);
    h = graphic_info(0, graph, G_HEIGHT);

    ttf_set_size(0, 18);
    set_text_color(rgb(0, 0, 255));
    drawing_map(0, graph);
    text_graph = write_in_map(0, text, 7);
    if(text_graph < 0)
        return;
    end

    map_put(0, graph, text_graph, w/2, h - 5);


    x = scr_width / 2 + rand(-200, 200);
    y = scr_height / 2 + rand(-200, 200);
    v_x += rand(-2, 2);
    v_y += rand(-2, 2);
    Loop
        if(x > scr_width - 20 || x < 20)
            v_x = -v_x;
        End
        if(y > scr_height - 20 || y < 20) 
            v_y = -v_y;
        End
        x += v_x;
        y += v_y;

        FRAME;
    End

OnExit
    if(graph > -1)
        map_unload(0, graph);
    End
End

Process main()
Private
    int retval;
    int handle;
    int i;

Begin
    ttf_set_size(0, 30);
    set_mode(scr_width, scr_height);
    write(0, scr_width / 2, scr_height/2 - 40, 4, "Your steam username is: " + steam_username);
    // write(0, scr_width / 2, scr_height/2, 4, "and this app's appID is " + steam_appid);
    write(0, scr_width / 2, scr_height/2 + 40, 4, "Press esc to unlock WHOLE_TRIBE");

    // steam_achievement_get_icon will return a graph with the
    // current state for the achievement icon
    // meaning that if the achievement is unlocked, the icon will
    // be "disabled" (grayscale)
    bouncer(steam_achievement_get_icon("WHOLE_TRIBE"));

    while(!key(_esc))
        Frame;
    End

    if(! steam_achievement_check("WHOLE_TRIBE"))
        retval = steam_achievement_unlock("WHOLE_TRIBE");
        if(retval == 0)
            write(0, scr_width / 2, scr_height - 35, 4, "Achievement was unlocked");
        else
            write(0, scr_width / 2, scr_height - 35, 4, "Achievement was NOT unlocked");
        end
    else
        write(0, scr_width / 2, scr_height - 35, 4, "No need to unlock achievement");
    End

    write(0, scr_width / 2, scr_height/2 + 80, 4, "Press enter to show your Steam friends bouncing!");

    while(!key(_enter))
        Frame;
    End

    let_me_alone();
    delete_text(ALL_TEXT);

    named_bouncer(steam_avatar_get(AVATAR_LARGE), steam_username);
    for(i=0; i < steam_friend_count(); i++)
        named_bouncer(steam_friend_avatar(i, AVATAR_MEDIUM), steam_friend_name(i));
        say(steam_friend_name(i) + " (" + steam_friend_nickname(i) + ")");
    end

    ttf_set_size(0, 30);
    set_text_color(rgb(255, 255, 255));
    write(0, scr_width / 2, scr_height/2 + 40, 4, "Press space bar to quit");
        while(!key(_space))
        Frame;
    End

    let_me_alone();
End
