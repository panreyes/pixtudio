process energy_ball(x,y,vel_x,vel_y)
private
byte anim_energy_ball[2] = 28,29,30;
byte anim_pos = 0;
byte count = 0;
int ball;
begin
	file = effects_fpg;
	count = sizeof(anim_energy_ball)/sizeof(byte);
	loop
		// anima 
		anim_pos++;
		if (anim_pos >= count)
			anim_pos = 0;
		end
		graph = anim_energy_ball[anim_pos];

		if(x > (resolution_offset_x() + ANCHO_PANTALLA-6) or x < resolution_offset_x() + 6)
			break;
		end
		
		x += vel_x;
		y += vel_y;

		if (ball = collision_box(type my_ball))
			ball.energy = 0;
			break;
		end 
		
		if (!exists(father))
			break;
		end
		frame;
	end
	while(alpha>0)
		alpha -= 20;
		size += 20;
		frame;
	end
end

process fueguito()
public
diff_x,diff_y;
begin
	z = father.z - 5;
	
	ctype = father.ctype;
	
	file = effects_fpg;

	graph = 1;
	size = 100;
	repeat		
		frame(100);
		if (!exists(father)) return; end
		x = father.x - diff_x;
		y = father.y - diff_y;
		
		graph++;
	until (graph >= 5 );
	
	repeat		
		frame(100);
		if (!exists(father)) return; end
		x = father.x - diff_x;
		y = father.y - diff_y;
		
		graph--;
	until (graph == 1 );

end

// animacion de la explosion de la bomba, no hace nada realmente loco
process bomba()
begin
	z = father.z - 1;
	x = father.x;
	y = father.y;
	ctype = father.ctype;
	
	file = effects_fpg;
	
	graph = 31;
	if (sound_on)
		play_wav(explosion_wav,0); // sonido coco roto
	end
	boom_wave();
	
	while (graph<43)
		if (graph>37)
			size += 5;
			alpha -= 50;
			frame(200);
		else
			frame;
		end
		graph++;
	end
end

// onda expansiva de la bomba, mata todo lo que toca
process boom_wave()
private
	collided;
begin
	z = father.z - 1;
	x = father.x;
	y = father.y;
	ctype = father.ctype;
	
	graph = new_map(100,100,16);	
	drawing_color(rgb(255,255,255));
	drawing_map(0,graph);
	draw_fcircle(50,50,50);
	
	size = 0;
	while (size<100)
		size +=20;
		alpha = ((100 - size) * 255) / 100;
		
		while ((collided = collision(0))!=0)
			if (collided.energy > 0)
				collided.energy = 0;
				hiteffect(collided); 
			end
		end
		frame;
	end
	
onexit
	unload_map(0,graph);

end

process explosion()
begin
	z = father.z - 1;
	x = father.x;
	y = father.y;
	ctype = father.ctype;
	
	file = effects_fpg;
	size = rand(130,170);
	graph = 27;
	frame;
	graph = 6;
	repeat		
		mini_explosion();
		frame;
		graph++;
	until (graph > 19 );
end

process mini_explosion()
begin
	z = father.z - 1;
	x = father.x + rand(-10,10) ;
	y = father.y + rand(-10,10) ;
	ctype = father.ctype;
	
	file = effects_fpg;
	size = rand(30,80);
	graph = 27;
	frame;
	graph = 6;
	repeat		
		frame;
		graph++;
	until (graph > 19 );
end

process smoke(inc_x,inc_y)
    
begin
	z = father.z - 10;
	x = father.x + rand(-5,5) ;
	y = father.y + rand(-5,5) ;
	ctype = father.ctype;
	
	file = effects_fpg;;
	size = rand(70,150);
	graph = rand(44,46);
	repeat
		alpha-=1;
		frame;
		size--;
		y += inc_y;
		x += inc_x;
	until (size<=0 );
	
end

process humo(inc_x,inc_y)
    
begin
	z = -11;
	x = father.x + rand(-5,5) ;
	y = father.y + rand(-5,5) ;
	ctype = father.ctype;
	
	file = effects_fpg;
	size = rand(10,100);
	graph = 20;
	repeat
		alpha-=30;
		frame;
		graph++;
		y += inc_y;
		x += inc_x;
	until (graph > 26 );
end

import "mod_blendop";

global
   shadowvar = false;
   hit_blend = false;
   bordervar = false;
end
 
process hiteffect(father)
private
i;
begin 
	if(!exists(father)) return; end
	
	if (!hit_blend)
		hit_blend=blendop_new();
		blendop_tint(hit_blend,1.00,255,255,255);			
	end
	
	i=3;
	blendop = father.blendop;		
	father.blendop = hit_blend;
	while (i>=0 and exists(father))
		frame;
		i--;
	end
	if(exists(father))
	father.blendop = blendop;
	end
end

process border()
Begin 
	return;
	frame;
	if (!bordervar)
		bordervar=blendop_new();
		Blendop_tint(bordervar,1,10,10,10);
	end

	blendop = bordervar;

	while (exists(father)) 
		x=father.x;
		y=father.y;
		graph=father.graph;
		file=father.file;
		region=father.region;
		flags=father.flags;
		angle = father.angle;
		z=father.z + 10;
		alpha = father.alpha;
		if (map_info(file,graph,G_WIDTH)>0)
		size = father.size + (( (map_info(file,graph,G_WIDTH) + 1) * 100 /  map_info(file,graph,G_WIDTH) )-100);
		end
		Frame(50); 
		
	end
end


process shadows(shadowdistancex,shadowdistancey);
Begin 
	frame;
	if (!shadowvar)
		shadowvar=blendop_new();
		Blendop_tint(shadowvar,1,10,10,10);
		Blendop_Translucency (shadowvar, 0.5);
	end

	blendop = shadowvar;

	loop

	if(exists(father)) 
		x=father.x+shadowdistancex;
		y=father.y+shadowdistancey;
		graph=father.graph;
		file=father.file;
		region=father.region;
		flags=father.flags;
		angle = father.angle;
		z=father.z+1;
	else
		signal(id,s_kill);
	end 

	Frame(50); 
	end
end

process shadow(father, shadowdistancex,shadowdistancey);
Begin 
	frame;
	if (!shadowvar)
		shadowvar=blendop_new();
		Blendop_tint(shadowvar,1,10,10,10);
		Blendop_Translucency (shadowvar, 0.5);
	end

	blendop = shadowvar;

	loop

	if(exists(father)) 
		x=father.x+shadowdistancex;
		y=father.y+shadowdistancey;
		graph=father.graph;
		file=father.file;
		region=father.region;
		flags=father.flags;
		angle = father.angle;
		z=father.z+1;
	else
		signal(id,s_kill);
	end 

	Frame(50); 
	end
end


process transicion(cual)
private xf, ener;
begin
z=-99999;
flags=128;

graph=get_screen();


	switch (cual)

	case 1:
	   
	   set_center(0,graph,0,0);   
	   x=99999;   
	   While(xf>-320) 
		 xf--; 
		 fideo(xf); 
	   End 
	   while(get_id(type fideo)) frame; end
	   
	end

	case 2:
	   
	   set_center(0,graph,0,0);      
	   repeat
		angle-=ener;
		ener+=50;
		frame;
	   until(angle<=-45000)
	   
	   ener=0;
	   
	   repeat
		y+= ener;
		ener++;
		frame;
	   until(out_region(id,0))
	   
	end

	case 3:
		
		pantallay(1);
		pantallay(2);
		x=9999;	
		repeat frame; until(!get_id(type pantallay))
		
	end

	case 4:
		
		pantallax(1);
		pantallax(2);
		x=9999;	
		repeat frame; until(!get_id(type pantallax))
		
	end

	end
onexit
	unload_map(0,graph);

end 

process pantallay(cual)
private
 ener,est;
begin
z=-99999;
graph=new_map(160,240,16);
y=120;
flags=128;
if(cual==1)
	x=240;
	map_put(file, graph, father.graph, 0, 120);
	ener=-1;
else
	x=80;
	map_put(file, graph, father.graph, 160, 120);
	ener=1;
end

repeat
	est+=ener;
	y+=est;
	frame;
until(out_region(id,0))
onexit
	unload_map(0,graph);

end

process pantallax(cual)
private
ener,est;
begin
z=-99999;
graph=new_map(320,120,16);
x=160;
flags=128;
if(cual==1)
	y=60;
	map_put(file, graph, father.graph, 160, 120);
	ener=-1;
else
	y=180;
	map_put(file, graph, father.graph, 160, 0);
	ener=1;
end

repeat
	est+=ener;
	x+=est;
	frame;
until(out_region(id,0))
onexit
	unload_map(0,graph);
end

process fideo(cual) 
 
 private
 float vy; 
 int a;
 ener,est;
 begin 
 z=-99999;
 flags=128;
 y=240;x=-cual+(1/2); 
 a=-50; 
 vy=rand(10,25);
 graph=new_map(1,480,16); 
 map_put(0,graph,father.graph,cual,0);  
 repeat 
   a++;
   y+=vy; 
   vy+=0.05;
   if(a==5) a=0; vy+=0.05; end
   //angle+=ang;
   alpha--;
   frame; 
 until(out_region(id,0)) 
 onexit
	unload_map(0,graph);
 end
