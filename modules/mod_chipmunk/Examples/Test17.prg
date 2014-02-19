//Cuerpo retorcido

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
import "mod_chipmunk"
import "mod_math"
import "mod_rand"

#define altoSoga 46
#define anchoSoga 15

global
	cuerda;
	posSoga;
	mapa;


Begin
  set_mode(800,600,32);
  cuerda=load_png("soga.png");
  mapa=load_png("bola40.png");
//  gphysics.gravity_Y=200;
  cuerda(400,100,300);
  mouseP();
  write(0,400,30,4,"haz click derecho del lado izquierdo de la soga");
  while (not key(_esc))
     if (mouse.right)
     trozo(mouse.x,mouse.y,0,mapa,TYPE_circle);
     APPLYIMPULSE(son,500,0,0,0);
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
 	 graph=mapa;
         lphysics.static=true;
	lphysics.ShapeType=TYPE_empty;                //No crearle cuerpos
	FORCECREATEBODY();
        size=30;	priority=5;	z=-100;
	loop
		x=mouse.x;
		y=mouse.y;
		 if (mouse.left)
			z = SpacePointQueryFirst( x, y, CP_ALL_LAYERS, CP_NO_GROUP);        //Toma el id de alg�n proceso que toque el punto dado por (x,y) y cuya capa est� comprendida por CP_ALL_LAYERS y pertenezca al grupo CP_NO_GROUP
			if (z and mouseJoint==0)                                            //Si z es distinto de cero y no se ha creado el joint
				WORLD2LOCAL(z, x, y,&x0, &y0);                              //Transforma las coordenadas del rat�n a coordenadas locales del proceso almacenado en z
				mouseJoint=addPivotJoint2(id, z, 0,0, x0,y0);               //crea el joint entre este proceso y el proceso apuntado por z en los puntos (0,0) de este proces y el (x0, y0) del proceso que se toca. Coordenadas locales
				DefConstraintF(mouseJoint,CP_C_MAXFORCE,5000);             //Define algunos valores del joint, v�ase la ayuda para m�s informaci�n
				DefConstraintF(mouseJoint,CP_C_BIASCOEF,0.004);
			end
		elseif (mouseJoint<>0)                                                      //Si no se presiona el bot�n izquierdo del rat�n eliminar el joint
			RemoveConstraint(mouseJoint);
			mouseJoint = 0;
		end
		frame;
	end
end

process trozo(x,y,g,graph,tipo)
private
id3;
begin
	lphysics.mass=1;
	lphysics.ELASTICITY=0;
	lphysics.friction=0;
	lphysics.Group=g;
	lphysics.ShapeType=tipo;
	forceCreateBody();
	lphysics.inertia=GETOPTIMALINERTIA(lphysics.ShapeType,lphysics.shape);
	loop
	if (y>800)
	   signal(id,s_kill);
	end
        	frame;
	end
end

process cuerda(x,y,altoC)
private
alto,id2,idAnt;
p1x,p1y,p2x,p2y;
begin
  alto=altoSoga-10;
  idAnt=trozo(x,y+z,1,cuerda,TYPE_line);
  WORLD2LOCAL(idAnt, x, y-(alto/2),&p1x, &p1y);
  addPivotJoint2(idAnt, 0, p1x,p1y, x,y-(alto/2));

  for (z=alto;z<altoC;z+=alto)
    id2=trozo(x,y+z,1,cuerda,TYPE_line);
    p1x=p2x=x;
    p1y=p2y=y+z-alto/2;
    WORLD2LOCAL(id2, p2x, p2y,&p2x, &p2y);
    WORLD2LOCAL(idAnt, p1x, p1y,&p1x, &p1y);
    addPivotJoint2(idAnt, id2, p1x,p1y, p2x,p2y);
//    addDampedRotarySpring(id2, idAnt, z*45000 + rand(-45000,45000),2,20);
//    addPivotJoint(idAnt, id2, x,y+z);
    idAnt=id2;
  end
end
