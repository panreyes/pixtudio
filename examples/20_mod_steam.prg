import "mod_steam"
import "mod_text"
import "mod_video"
import "mod_key"
import "mod_map"
import "mod_file"
import "mod_proc"

Global
    int handle = -1;
    int scr_width=800, scr_height=600;
End

Process say(string text)
Begin
    if(handle == -1)
        if(file_exists("stdout.txt"))
            fremove("stdout.txt");
        end
        handle = fopen("stdout.txt", O_WRITE);
    end

    if(handle == 0)
        return;
    end

    fputs(handle, text);
End

Process bouncer(graph)
Private
    int v_x = 5, v_y = 5;
Begin
    say("Bouncer graph: " + graph);
    if(graph == -1)
        return;
    end

    x = scr_width / 2;
    y = scr_height / 2;
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
    int font, retval;
    int handle;

Begin
    font = ttf_load("ttf/DejaVuSans.ttf");
    ttf_set_size(font, 30);
    set_mode(scr_width, scr_height);
    write(font, scr_width / 2, scr_height/2 - 40, 4, "Your steam username is: " + steam_username);
    write(font, scr_width / 2, scr_height/2, 4, "and this app's appID is " + steam_appid);
    write(font, scr_width / 2, scr_height/2 + 40, 4, "Press esc to unlock WHOLE_TRIBE");

    // steam_get_achievement_icon will return a graph with the
    // current state for the achievement icon
    // meaning that if the achievement is unlocked, the icon will
    // be "disabled" (grayscale)
    bouncer(steam_get_achievement_icon("WHOLE_TRIBE"));

    while(!key(_esc))
        Frame;
    End

    retval = steam_unlock_achievement("WHOLE_TRIBE");
    if(retval == 0)
        write(font, scr_width / 2, scr_height - 35, 4, "Achievement was unlocked");
    else
        write(font, scr_width / 2, scr_height - 35, 4, "Achievement was NOT unlocked");
    end

    write(font, scr_width / 2, scr_height/2 + 80, 4, "Press enter to quit");

    while(!key(_enter))
        Frame;
    End

    let_me_alone();

    say("Achivement unlocked? " + steam_check_achievement("WHOLE_TRIBE"));
    steam_delete_achievement("WHOLE_TRIBE");

OnExit
    fclose(handle);
End