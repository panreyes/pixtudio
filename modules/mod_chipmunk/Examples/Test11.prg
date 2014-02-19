//PRG, ejemplo para el motor de f�sica

import "mod_key";
import "mod_text";
import "mod_proc";
import "mod_grproc";
import "mod_video";
import "mod_wm";
import "mod_map";
import "mod_say";
import "mod_math";
import "mod_screen";
import "mod_chipmunk";
import "mod_draw";


global
	pelota;                                                //Gr�fico de la pelota
local
joint;
jointGear;
Begin
        set_mode(800,600,32);
	pelota=load_png("bola40.png");

	gphysics.gravity_Y=200;                                          //Se define la gravedad en Y
	gphysics.phresolution=1;
        write(0,400,30,4,"Presiona espacio para que las pelotas no colisionen con el rect�ngulo verde");
	addInanimateShape(type_line, 0.0, 600.0, 800.0,600.0, 0.0);      //Crea una l�nea para simular el piso y se agrega al fondo, pero no se pinta.
	addInanimateShape(type_line, 0.0, 0.0, 800.0,0.0, 0.0);
	addInanimateShape(type_line, 0.0, 0.0, 0.0,600.0, 0.0);
	addInanimateShape(type_line, 800.0, 0.0, 800.0,600.0, 0.0);
	pelota1();                                                        //Pelota rebotando
	pelota2();                                                        //Pelota rebotando
	caja();
	mouseP();
        SPACEADDCOLLISIONHANDLER(3,2,"inicia","","postsolve","separate",15,null,null,null);    //agrega inicio, postsolve y separate como callback. Cada callback recibe como par�metro un arbitro y lo que se le pase por esta funci�n a partir del valor 15 (par�metro 7)
        SPACEADDCOLLISIONHANDLER(2,1,"inicia","presolve","","separate",5,null,null,null);
	while (!key(_esc))

	if (key(_r))
	   SPACEREMOVECOLLISIONHANDLER(3,2);
	end
		frame;

	end
	let_me_alone();
end

process mouseP()
private
	mouseJoint;
	x0,y0;
begin
 	lphysics.static=true;
	lphysics.ShapeType=TYPE_empty;                //No crearle cuerpos
	FORCECREATEBODY();

	graph=pelota;	size=30;	priority=5;	z=-100;
	loop
		x=mouse.x;
		y=mouse.y;
		 if (mouse.left)
			z = SpacePointQueryFirst( x, y, CP_ALL_LAYERS, CP_NO_GROUP);        //Toma el id de alg�n proceso que toque el punto dado por (x,y) y cuya capa est� comprendida por CP_ALL_LAYERS y pertenezca al grupo CP_NO_GROUP
			if (z and mouseJoint==0)                                            //Si z es distinto de cero y no se ha creado el joint
				WORLD2LOCAL(z, x, y,&x0, &y0);                              //Transforma las coordenadas del rat�n a coordenadas locales del proceso almacenado en z
				mouseJoint=addPivotJoint2(id, z, 0,0, x0,y0);               //crea el joint entre este proceso y el proceso apuntado por z en los puntos (0,0) de este proces y el (x0, y0) del proceso que se toca. Coordenadas locales
				DefConstraintF(mouseJoint,CP_C_MAXFORCE,80000);             //Define algunos valores del joint, v�ase la ayuda para m�s informaci�n
				DefConstraintF(mouseJoint,CP_C_BIASCOEF,0.000005822);
			end
		elseif (mouseJoint<>0)                                                      //Si no se presiona el bot�n izquierdo del rat�n eliminar el joint
			RemoveConstraint(mouseJoint);
			mouseJoint = 0;
		end
		frame;
	end
end

//funci�n para callback cuando se colisiona por primera vez con un objeto. Si retorna false los objetos se traspasar�n, adem�s presolve y postsolve no se llamar�n.
function inicia(int arb, int * p )
private
float fa,fb;
begin
say("toca "+p);
  if (key(_space))
     return false;           //que no colisione
  end
  return true;               //que s� colisione
end

//funci�n que se llamar� cuando la colisi�n se haya resuelto. Aqu� se pueden llamar funciones como GETARBITERTOTALIMPULSEWITHFRICTION y GETARBITERTOTALIMPULSE
function postsolve(int arb, int * p )
begin

end

//funci�n que se llama antes de resolverse la colisi�n. Aqu� se puede llamar a SETARBITERFRICTION, GETARBITERFRICTION,SETARBITERELASTICITY y GETARBITERELASTICITY.
function presolve(int arb, int * p )
begin
return true;
end

//funci�n que se llama cuando dos cuerpos dejan de tocarse
function separate(int arb, int * p )
begin
say("separado");
end

process pelota1()
private
id3;
begin
	x=300;   y=100;   graph=pelota;

        //Se definen las propiedades de la pelota
	lphysics.mass=10;                  //Masa de 10
	lphysics.ELASTICITY=0.8;           //Elasticidad del cuerpo (0-1, preferentemente)
	lphysics.friction=0.3;             //Coeficiente de fricci�n del material del cuerpo
	lphysics.ShapeType=TYPE_CIRCLE;    //Forma del cuerpo, el circular es el m�s econ�mico y f�cil de usar.
	forceCreateBody();                 //Se forza la creaci�n del cuerpo
        lphysics.collisionType=3;
	//Antes de llamar a getOptimalInertia hay que actualizar el cuerpo, ya sea forzando su creaci�n (cuando �ste a�n no existe) o haciendo un frame(v) antes, con v igual a cualquier valor o sin v.
        lphysics.inertia=GETOPTIMALINERTIA(lphysics.ShapeType,lphysics.shape);
        lphysics.sensor=false;
	loop
        	frame;
	end
end


process pelota2()
private
id3;
begin
	x=500;   y=100;   graph=pelota;

        //Se definen las propiedades de la pelota
	lphysics.mass=10;                  //Masa de 10
	lphysics.ELASTICITY=0.8;           //Elasticidad del cuerpo (0-1, preferentemente)
	lphysics.friction=0.3;             //Coeficiente de fricci�n del material del cuerpo
	lphysics.collisionType=1;             //Coeficiente de fricci�n del material del cuerpo
	lphysics.ShapeType=TYPE_CIRCLE;    //Forma del cuerpo, el circular es el m�s econ�mico y f�cil de usar.
	forceCreateBody();                 //Se forza la creaci�n del cuerpo

	//Antes de llamar a getOptimalInertia hay que actualizar el cuerpo, ya sea forzando su creaci�n (cuando �ste a�n no existe) o haciendo un frame(v) antes, con v igual a cualquier valor o sin v.
        lphysics.inertia=GETOPTIMALINERTIA(lphysics.ShapeType,lphysics.shape);
	loop
        	frame;
	end
end

process caja()
begin
	x=400;   y=300;
        graph=new_map(400,20,32);
        map_clear(file,graph,rgb(0,255,0));

        //Se definen las propiedades de la pelota
	lphysics.mass=10;                  //Masa de 10
	lphysics.ELASTICITY=0.9;           //Elasticidad del cuerpo (0-1, preferentemente)
	lphysics.friction=0.3;             //Coeficiente de fricci�n del material del cuerpo
	lphysics.collisionType=2;             //Coeficiente de fricci�n del material del cuerpo
	lphysics.ShapeType=TYPE_box;    //Forma del cuerpo, el circular es el m�s econ�mico y f�cil de usar.
        lphysics.static=true;
        forceCreateBody();                 //Se forza la creaci�n del cuerpo

	//Antes de llamar a getOptimalInertia hay que actualizar el cuerpo, ya sea forzando su creaci�n (cuando �ste a�n no existe) o haciendo un frame(v) antes, con v igual a cualquier valor o sin v.
        lphysics.inertia=GETOPTIMALINERTIA(lphysics.ShapeType,lphysics.shape);
	loop
        frame;
        end
	onexit;
	unload_map(file,graph);
end