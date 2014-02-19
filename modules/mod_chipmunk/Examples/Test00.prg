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

Begin
        set_mode(800,600,32);
	pelota=load_png("bola40.png");

	gphysics.gravity_Y=200;                                          //Se define la gravedad en Y
        gphysics.phresolution=1;                                         // para que las intersecciones de boundingbox se detecten a tiempo, usar una iteraci�n del motor de f�sica por frame
        //addInanimateShape(type_line, x1, x2, y1,y2, radio);
        //addInanimateShape(type_circle, x,y, radio);
        //addInanimateShape(type_convex_polygon, x,y, numeroVertices, listaVertices);
	addInanimateShape(type_line, 0.0, 600.0, 800.0,600.0, 0.0);      //Crea una l�nea para simular el piso y se agrega al fondo, pero no se pinta.
	pelota();                                                        //Pelota rebotando
	while (!key(_esc))
	if (key(_r))
       //    pelota();
	end
		frame;

	end
	let_me_alone();
end


process pelota()
private
id2;
begin
	x=400;   y=100;   graph=pelota;

        //Se definen las propiedades de la pelota
	lphysics.mass=10.0;                  //Masa de 10
	lphysics.ELASTICITY=0.9;           //Elasticidad del cuerpo (0-1, preferentemente)
	lphysics.friction=0.3;             //Coeficiente de fricci�n del material del cuerpo
	lphysics.ShapeType=TYPE_CIRCLE;    //Forma del cuerpo, el circular es el m�s econ�mico y f�cil de usar.
	forceCreateBody();                 //Se forza la creaci�n del cuerpo

	//Antes de llamar a getOptimalInertia hay que actualizar el cuerpo, ya sea forzando su creaci�n (cuando �ste a�n no existe) o haciendo un frame(v) antes, con v igual a cualquier valor o sin v.
       lphysics.inertia=GETOPTIMALINERTIA(lphysics.ShapeType,lphysics.shape);

	loop
/*	        while (id2=get_id(type pelota))
                	if (id2!=id &&INTERSECTSBB(id2))       //revisa si se intersectan los boundingbox de las esferas. Si no se usa gphysics.phresolution=1, las colisiones no son muy buenas porque la f�sica puede hacer rebotar las pelotas antes que se detecte la intersecci�n
                	   signal(id2,s_kill);
             	        end
        	end*/
	frame;
	end
end