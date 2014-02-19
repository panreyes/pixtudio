import "mod_m7"
import "mod_key"
import "mod_map"
import "mod_scroll"
import "mod_video"
import "mod_draw"
import "mod_grproc"
import "mod_proc"

GLOBAL
    int graficos1;
    int color;
    
Process main()
BEGIN
    set_mode(320,240,8);
    set_fps(50,0);
    
    graficos1=load_fpg("archive.fpg");
    
    start_mode7(0,graficos1,1,-1,0,64);
    start_mode7(1,graficos1,2,0,0,64);
    m7[0].color=15;
    m7[0].camera=id;
    
    m7[0].height=9;
    m7[0].distance=20;
    m7[0].focus=256;
    
    m7[1].color=15;
    m7[1].camera=id;
    
    m7[1].height=-6;
    m7[1].distance=20;
    m7[1].focus=256;
    m7[1].z=m7[0].z-1;
    ctype=c_m7;
    
    resolution=100;
    coche(graficos1);
    
    coche2(graficos1);
    
    while (!key(_esc))
        color=map_get_pixel(graficos1,2,x/resolution,y/resolution);
        if (key(_up)) x+=100; end
        if (key(_down)) x-=100; end
        if (key(_left)) y-=100; end
        if (key(_right)) y+=100; end
        if (key(_c_minus) && m7[0].height>9)
            m7[0].height--;
            m7[1].height--;
        end
        if (key(_c_plus))
            m7[0].height++;
            m7[1].height++;
        end
        if (key(_w)) advance(100); end
        if (key(_s)) advance(-100); end
        if (key(_a)) angle+=2000; end
        if (key(_d)) angle-=2000; end
        
        if (key(_f1)) m7[0].focus--; end
        if (key(_f2)) m7[0].focus++; end
        if (key(_z)) m7[0].distance--; end
        if (key(_x)) m7[0].distance++; end
        if (key(_c)) m7[1].height--; end
        if (key(_v)) m7[1].height++; end
        frame;
    end
    stop_mode7(0);
    stop_mode7(1);
    let_me_alone();
END

process coche (file)
begin
    priority=father.priority-1;
    resolution=100;
    graph=3;
    
    ctype=c_m7;
    cnumber=c_0;
    
    loop
        x=father.x;
        y=father.y;
        frame;
    end
end

process coche2 (file)
begin
    x=100;
    y=100;
    graph=3;
    ctype=c_m7;
    cnumber=c_0;

    loop
        if (key(_o)) height--; end
        if (key(_p)) height++; end
        frame;
    end
end
