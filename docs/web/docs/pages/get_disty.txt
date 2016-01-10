Definition
----------

**INT** get\_disty ( &lt;**INT** angle&gt; , &lt;**INT** distance&gt; )

Returns the vertical distance in pixels of a specified displacement.

This is the same as `-[[sin]](''angle'')*''distance''`.

Parameters
----------

  ------------------ -----------------------------------------------------------------------
  **INT** angle      - [Angle](Angle "wikilink"), in thousandths of degrees (90° = 90000).
  **INT** distance   - Length (in pixels) to measure.
  ------------------ -----------------------------------------------------------------------

Returns
-------

**INT** : The vertical distance, in pixels, of a specified displacement.

Notes
-----

This function returns the height of an imaginary rectangle who's
opposite corners are the specified distance apart, at the specified
[angle](angle "wikilink") from each other.

Example
-------

    Global
        xdist;
        ydist;
        dist;
        ang;
        mydraw;
    End

    Process Main()
    Begin

        set_mode(640,480,16);
        set_fps (50,0);
        graph = new_map(3,3,16);
        map_clear(0,graph,rgb(0,255,0));
        x = 320;
        y = 240;

        set_text_color(rgb(0,0,0));
        write    (0,60, 0,2,"X Diff: ");
        write_int(0,60, 0,0,&xdist);
        write    (0,60,10,2,"Y Diff: ");
        write_int(0,60,10,0,&ydist);
        write    (0,60,20,2,"Angle: ");
        write_int(0,60,20,0,&ang);
        write    (0,60,30,2,"Distance: ");
        write_int(0,60,30,0,&dist);

        write    (0,10,40,0,"Left/right rotates your angle, up/down changes your distance");
        
        put(0,graph,x,y);
        drawing_background();

        repeat
            if(key(_up))
                dist++;
            end

            if(key(_down))
                dist--;
            end

            if(key(_left))
                ang-=1000;
            end

            if(key(_right))
                ang+=1000;
            end

            xdist = get_distx(ang,dist);
            ydist = get_disty(ang,dist);

            x = 320 + xdist;
            y = 240 + ydist;

            frame;

        until(key(_esc))

        let_me_alone();
        exit();

    End

    Process drawing_background()
    Begin
        graph = new_map(640,480,16);
        set_ceter   (0,graph,0,0);
        map_clear    (0,graph,rgb(64,0,0));
        drawing_map  (0,graph);
        drawing_color(rgb(0,0,0));
        loop
            map_clear(0,graph,rgb(255,255,255));
            mydraw = draw_line(320,240,father.x,father.y);
            frame;
            delete_draw(mydraw);
        end
    OnExit
        unload_map(0,graph);
    End

Used in example: [set\_mode](set_mode "wikilink")(),
[set\_fps](set_fps "wikilink")(), [new\_map](new_map "wikilink")(),
[set\_text\_color](set_text_color "wikilink")(),
[write](write "wikilink")(), [write\_int](write_int "wikilink")(),
[put](put "wikilink")(), [key](key "wikilink")(),
[get\_distx](get_distx "wikilink")(),
[get\_disty](get_disty "wikilink")(),
[let\_me\_alone](let_me_alone "wikilink")(), [exit](exit "wikilink")(),
[set\_center](set_center "wikilink")(),
[map\_clear](map_clear "wikilink")(), [rgb](rgb "wikilink")(),
[drawing\_map](drawing_map "wikilink")(),
[drawing\_color](drawing_color "wikilink")(),
[draw\_line](draw_line "wikilink")(),
[delete\_draw](delete_draw "wikilink")(),
[unload\_map](unload_map "wikilink")()

<Category:functions> <Category:math> <Category:mod_math>
