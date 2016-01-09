//PRG, ejemplo para el motor de física
import "mod_key"
import "mod_text"
import "mod_proc"
import "mod_grproc"
import "mod_video"
import "mod_wm"
import "mod_map"
import "mod_say"
import "mod_math"
import "mod_screen"
import "mod_rand"
import "mod_chipmunk"
import "mod_joy"

global
    int num = 4;
    cpVect verts[] =
        -3,-20,
        -3, 20,
         3, 20,
         3,-20;

    float u = 0.6;
    ball;
private
    press;

Begin
    scale_resolution=06400480;
    set_mode(1280,800,16,MODE_FULLSCREEN );
    cpResetShapeIdCounter();
    ball=load_png("ball.png");
    gphysics.gravity_y=300;
    gphysics.interval=1/25.0;
    gphysics.iterations=30;
    gphysics.sleepTimeThreshold=0.5;
    SpaceResizeActiveHash( 30.0, 2999);
    SpaceResizeStaticHash( 30.0, 999);
    plano();
    write(0,400,10,4,"Press button A to shoot ball");
    creaPiramide();

    while (!key(_esc) && !joy_getbutton(0, 6))
        if (key(_space) || joy_getbutton(0, 0))
            if (not press)
                cubo();
                press=true;
            end
        else
            press=false;
        end
        frame;

    end
    let_me_alone();
end

process plano()
begin
    lphysics.static=true;
    lphysics.mass=infinity;
    lphysics.inertia=infinity;
    lphysics.ShapeType=TYPE_LINE;
    lphysics.elasticity=1;
    lphysics.friction=1;
    lphysics.layers=NOT_GRABABLE_MASK;
    graph=new_map(1200,20,16);
    map_clear(file,graph,rgb(0,255,0));
    x=640;
    y=780;
    z=15;
    priority=father.priority+4;
    loop
        frame;
    end
end


process dominos(x,y,angle)
begin
    lphysics.mass=0.1;
    lphysics.inertia=cpMomentForPoly(1.0, num, &verts,0.0,0.0);
    priority=father.priority;
    lphysics.ShapeType=TYPE_CONVEX_POLYGON;
    lphysics.elasticity=0.2;
    lphysics.friction=u;
    graph=new_map(6,40,16);
    map_clear(file,graph,rgb(100,255,255));
    loop
        frame;

    end
end

#define reajuste 770
#define n 9

function creaPiramide()
private
cpVect offs,pos,aux;
begin

for(x=n; x>0; x--)
    cpv(-x*60/2.0, (n - x)*52 +240,&offs);
    for(y=x-1; y>=0; y--)
        cpvadd(cpv(y*60, -220,aux), &offs,&pos);
        dominos(640+pos.x,reajuste-pos.y,0);
        cpvadd(cpv(y*60, -197,aux), &offs,&pos);
        dominos(640+pos.x,reajuste-pos.y,PI/2.0);
        if(y == (x - 1)) continue;  end
        cpvadd(cpv(y*60 + 30, -191,aux), &offs,&pos);
        dominos(640+pos.x,reajuste-pos.y,PI/2.0);
    end
    cpvadd(cpv(-17, -174,aux), &offs,&pos);
    dominos(640+pos.x,reajuste-pos.y,0);

    cpvadd(cpv((x - 1)*60 + 17, -174,aux), &offs,&pos);
    dominos(640+pos.x,reajuste-pos.y,0);
    end
end

process cubo()
private
    esferaShape1;
begin
    x=400;
    y=100;
    lphysics.mass=10;
    lphysics.inertia= cpMomentForCircle(10.0, 0.0, 10.0, 0.0,0.0);
    priority=father.priority;
    lphysics.ShapeType=TYPE_circle;
    lphysics.elasticity=0.1;
    lphysics.friction=0.6;
    graph=ball;
    FORCECREATEBODY(); //forza la creación del cuerpo físico inmediatamente para comenzar a usarlo
    Slew( rand(300,900),500, 1);
    loop
        if (out_region(id,0))
            signal(id,s_kill);
        end
        frame;
    end
end

