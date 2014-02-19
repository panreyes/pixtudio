local
	ball_type;
	real_colission;
end
// pedazo de coco roto que cae cuando se pierde un coco
process cocopart()
public
inc_y = -5;
inc_x = 0;
begin	
	file = cocofpg;
	x = father.x;
	y = father.y;
	region = father.region;
	switch(father.ball_type)
	case 1:
	graph = rand(2,7);
	end
	case 2:
	graph = rand(12,17);
	end
	case 3:
	graph = rand(19,24);
	end
	case 4:
	graph = rand(28,33);
	end
	case 5:
	graph = rand(39,40);
	end	
	case 6:
	graph = rand(36,36);
	end
	case 7:
	graph = rand(37,38);
	end
	end
	frame;	
	border();
	while (y < ALTO_PANTALLA)
		angle+=10000;
		
		y+=inc_y;
		if (inc_y<10)
			inc_y += 1;
		end
		
		x+=inc_x;
		if (inc_x > 1)
			inc_x --;
		end
		
		if (inc_x < -1)
			inc_x ++;
		end
		frame;
	end
end

/**
 * dibujo de la ballesta que dispara el coco
 */
process crossbow()
private
	int linea_izquierda_x = 0;
	int linea_izquierda_y = 0;
	int linea_derecha_x = 0;
	int linea_derecha_y = 0;
	int linea_izquierda = 0;
	int linea_derecha = 0;
begin
	file = cocofpg;
	graph = 26;
	// posicion en pantalla
	x = resolution_offset_x() + (ANCHO_PANTALLA/2)+1;
	y = (ALTO_PANTALLA/10)*8;
	z = -6;
	loop
		drawing_color(rgb(218,164,2));
		drawing_stipple(0ffffffffh);
		drawing_z(-1000);
		get_real_point(2,&linea_izquierda_x,&linea_izquierda_y);
		linea_izquierda = draw_line(palos_izquierda_x,palos_izquierda_y,linea_izquierda_x,linea_izquierda_y);
		get_real_point(1,&linea_derecha_x,&linea_derecha_y);
		linea_derecha = draw_line(palos_derecha_x,palos_derecha_y,linea_derecha_x,linea_derecha_y);
		frame;
		delete_draw(linea_izquierda);
		delete_draw(linea_derecha);
	end
	onexit
		delete_draw(linea_izquierda);
		delete_draw(linea_derecha);
end

/**
 * generic process to put images that doesn't need logic
 */
declare process trinchera(file,graph,x,y,z)
	public
		int must_shake = false;
	end
end



/**
 * proceso bola, o coco, en este caso.
 */
process my_ball(ball_type)

	public 
		byte shoot = false;
		byte coconut_type;
	end

private
	trinchera current_trinchera;
	
	float ball_next_y_gravity ;
	
	byte wall_colission = false;
	byte collision_bottom = false;
	
	float ball_x;
	float ball_y;
	int ball_next_x;
	int ball_next_y;
	float accel = 0;
	int distance,mouse_cur;
	enemy_block collided;
	int map, red, green, blue, pixel, i, j;
	float collision_angle, my_angle, sum_res, prev_x, prev_y, res_for_div;
	
	int disparando = false;
	
	pointer next_mayor; pointer next_menor; pointer coord_mayor; pointer coord_menor;
	
	int speed = 5;
	
	cocopart coco[1];
	
begin
	
	coconut_type = ball_type;
	file = cocofpg;

	switch(ball_type)
		case 1:
		graph = 1;
		energy = 3;
		end
		case 2:
		graph=11;
		energy = 2;
		end
		case 3:
		graph=18;
		energy = 1;
		end
		case 4: // bola de bolos lol
		graph=27;
		energy = 4;
		end
		case 5: // bola de pinball
		graph=35;
		energy = 1;
		end
		case 6: // bola explosiva
		graph=36;
		energy = 3;
		end
		case 7: // bola oooooocho
		graph=34;
		energy = 2;
		end
	end
	border();
	ball_next_y = 0;
	ball_next_x = 0;
	collided = 0;
	mouse.x = x = resolution_offset_x() + (ANCHO_PANTALLA/2)+1;
	mouse.y = y = (ALTO_PANTALLA/10)*8;

	z = -10;
	
	loop
		if (exists(collided))
			collided.coco_collided =0;
		end
		
		// flag q indica que se estaba apretando el mouse.left
		if (disparando)
		    if (!(mouse.left or control(1,CONTROL_OK))) // Open Pandora: Button A
				shoot = true;
				if (sound_on)
					play_wav(disparo_wav,0);
				end
				disparando = false;
				signal( ballesta , s_kill_tree );
			end
		end
		
		
	
		// esperando por disparar
		if (shoot == false and !(mouse.left or control(1,CONTROL_OK))) // Open Pandora: Button A
			alpha = 255;//mostramos la bola			
			if(!touchscreen())
				// fijamos la posicion de la bolita en el centro y esperamos que arrastren para apuntar.
				mouse.x = x = resolution_offset_x() + (ANCHO_PANTALLA/2)+1;
				mouse.y = y = (ALTO_PANTALLA/10)*8;
			end
			frame;
		elseif (shoot == false and (mouse.left or control(1,CONTROL_OK))) // Open Pandora: Button A  // se esta arrastrando
			// limita el mouse al area de disparo
			if(!touchscreen())
				
				if (mouse.y < ((ALTO_PANTALLA/4) * 3 ) + 15)
					mouse.y = ((ALTO_PANTALLA/4) * 3) + 16;
				end
				
				
				if (mouse.x < resolution_offset_x())
					mouse.x = resolution_offset_x()+1;
				end
				
				if (mouse.x > resolution_offset_x() + ANCHO_PANTALLA)
					mouse.x = resolution_offset_x() + ANCHO_PANTALLA -1;
				end	
				
			else
				// si esta fuera del area de disparo ignoramos
				if (mouse.y < ((ALTO_PANTALLA/4) * 3 ) + 15)
					frame;
					continue;
				end
			end
			
			alpha = 0;//escondemos la bola
			
			if (control(1,CONTROL_LEFT))
				mouse.x--;
			end
			
			if (control(1,CONTROL_RIGHT))
				mouse.x++;
			end
			
			if (control(1,CONTROL_UP))
				mouse.y --;
			end
			
			if (control(1,CONTROL_DOWN))
				mouse.y++;
			end
			
			// calcula la velocidad y el angulo con el que va a salir la pelotita
			ball_next_x = ((mouse.x - (resolution_offset_x() + (ANCHO_PANTALLA/2)))) *-1 ;
			ball_next_y = -(80 - abs(ball_next_x));
			
			speed = (mouse.y - 180)/3;
			speed_used = speed; // guardamos el valor de la velocidad para poder asignar puntaje despues
			
			// configuramos la ballesta
			ballesta.angle = (fget_angle ( -(ball_next_x*2) , -(ball_next_y*2), ball_next_x , ball_next_y   ) ) - 90000;
			ballesta.x = mouse.x;
			ballesta.y = mouse.y;
			ballesta.z = -1000;
						
			
			// dibuja el path que va a hacer la pelotita, uno por frame
			draw_path(id,speed,energy, ball_next_x, ball_next_y, ball_type);
			
			mouse.file = file; 
			mouse.graph = graph;
			
			// setea flag de 
			disparando = true;
			//say(speed);
		
			frame;
		elseif (shoot == true) // ya se disparo y estamos jugando
			// la bola moviendose 		
			alpha = 255;
			// restoreamos el mouse a la forma de manito
			if(touchscreen() or joy_number()>0)
				mouse.file = 0;
				mouse.graph = 0;
			else
				mouse.file = ui_fpg;
				mouse.graph = 34;
			end
			wall_colission = false;
			
			ball_next_y_gravity = ball_next_y;
			
			
			/*Funcion personalizada para advance sin girar el gráfico*/
			
			if(abs(ball_next_x) < abs(ball_next_y))
				next_mayor = &ball_next_y;
				next_menor = &ball_next_x;
				coord_mayor = &y;
				coord_menor = &x;
			else
				next_mayor = &ball_next_x;
				next_menor = &ball_next_y;
				coord_mayor = &x;
				coord_menor = &y;
			end
			
			if (abs( *next_menor) == 0)
				res_for_div = abs( *next_mayor);
			else
				res_for_div = (abs( *next_mayor)) / (abs( *next_menor));
			end
			
			sum_res = res_for_div;
			for(i=0;i<=abs( *next_mayor)+1;i++)
				
				// arregla la posicion si la bola se salio de la pantalla (tambien detecta cuando choca contra la pared)
				if(y > (((ALTO_PANTALLA/10)*8))) 
					wall_colission = true; 
					collision_bottom = true;
					y = (((ALTO_PANTALLA/10)*8)); 
					ball_next_y *= -1;
					break; 
				End
				if(y < 6) 
					wall_colission = true; 
					collision_bottom = false;
					y = 6; 
					ball_next_y *= -1;
					break; 
				End
				if(x > resolution_offset_x() + (ANCHO_PANTALLA-6)) 
					wall_colission = true; 
					collision_bottom = false;
					x = resolution_offset_x() + (ANCHO_PANTALLA-6); 
					ball_next_x *= -1;
					break; 
				End
				if(x < resolution_offset_x() + 6) 
					wall_colission = true; 
					collision_bottom = false;
					x = resolution_offset_x() + 6; 
					ball_next_x *= -1;
					break; 
				End
				
				if(wall_colission == true)
				ball_next_y +=10;
				End
				
				if(i >= sum_res)
					if( *next_menor < 0)
						*coord_menor -= 1;
						if(collided == 0) 
							if (collided = collision_box(type enemy_block)) 
								if (collided.energy > 0) *coord_menor += 1; 
									Break; 
								else 
									collided=0; 
								end 
							End; 
						End;
					elseif( *next_menor > 0)
						*coord_menor += 1;
						if(collided == 0) 
							if (collided = collision_box(type enemy_block)) 
								if (collided.energy > 0) 
									*coord_menor -= 1; 
									Break; 
								else 
									collided=0; 
								end 
							End; 
						End;
					End
					sum_res += res_for_div;
				End
				if( *next_mayor < 0)
					*coord_mayor -= 1;
					if(collided == 0) if (collided = collision_box(type enemy_block)) if (collided.energy > 0) *coord_mayor += 1; Break; else collided=0; end End; End;
				elseif( *next_mayor > 0)
					*coord_mayor += 1;
					if(collided == 0) if (collided = collision_box(type enemy_block)) if (collided.energy > 0) *coord_mayor -= 1; Break; else collided=0; end End; End;
				End
				
				if (energy <= 0)
					frame;
					break;
				end
				
				if(ball_type == 5) // gravedad aplicada para la bola de pinball
					ball_next_y_gravity += 1.5 - ((speed+1) * 0.07) ;
					
					if(ball_next_y_gravity > 19)
						ball_next_y_gravity = 19;
					end;
					
					ball_next_y = ball_next_y_gravity;
				end
				
				if (i%speed==0)
					frame;
				end
				
				
			End
				
			
			
				
			/*Fin de la funcion advance*/
			
			// si chocamos...			
			if (wall_colission)
				if((ball_type == 5 && collision_bottom == true) || (ball_type != 5))
					energy--; 
				end
				hiteffect(id); 
				//points(-5); 
				if (sound_on) 
					play_wav(golpe_pared_wav,0); 
				end 
				if (ball_type == 4)
					while (current_trinchera = get_id(type trinchera))
						if (exists(current_trinchera))						
							current_trinchera.must_shake = true;
						end
					end
				end
			end
			
			if(exists(collided))
			
				//collided.coco_collided = ball_type;

				//collided.coco_pid = id;
				// sierra
				if (collided.enemy_type == 15 and collided.status != "closed")
					collided.energy++;
					energy = 0;
				end

				//chequeamos si la colision se hicon con un bot del 17 al 20
				hiteffect(collided);
				
				if (sound_on)
					play_wav(golpe_robot_wav,0);
					if(ball_type == 5)
						play_wav(pinball_wav,0); 
					end
					if(ball_type == 7)
						play_wav(ball8_wav,0); 
					end
				end

				// largar puntos aca appeer como
				//points(10);
				
				if(
				(collided.enemy_type == 17 && abs(y - collided.y) > abs(x - collided.x) && ball_next_y < y && collided.y < y-9) ||
				(collided.enemy_type == 18 && abs(y - collided.y) > abs(x - collided.x) && collided.y > y+9) ||
				(collided.enemy_type == 19 && abs(y - collided.y) < abs(x - collided.x) && ball_next_x < x && collided.x < x-9) ||
				(collided.enemy_type == 20 && abs(y - collided.y) < abs(x - collided.x) && collided.x > x+9)
				)
					real_colission = true;
				else
					real_colission = false;
				End
				
				//bot sierra, si pega en alguno de los lados con la sierra rompe el coco 
				if(
				(collided.enemy_type == 23 && abs(y - collided.y) > abs(x - collided.x) && ball_next_y < y && collided.y < y-9) ||
				(collided.enemy_type == 24 && abs(y - collided.y) > abs(x - collided.x) && collided.y > y+9) ||
				(collided.enemy_type == 21 && abs(y - collided.y) < abs(x - collided.x) && ball_next_x < x && collided.x < x-9) ||
				(collided.enemy_type == 22 && abs(y - collided.y) < abs(x - collided.x) && collided.x > x+9)
				)
					collided.energy++;
					energy = 0;
				End
				


				//si estamos para restar energía resta (segun condicion grande de arriba)
				//si es uno de los robots que choca de los lados y choca bien o si es otro robot manda a colisionar
				switch (collided.enemy_type)
					case 17..20:
						if(real_colission)
							collided.energy--; // resta energia al bloque
						End
					end
					default:
						collided.energy--; // resta energia al bloque
						if(ball_type == 7) //si es bola 8 lo mata de una
							collided.energy = 0;
						End
					end
				end
				
				//le damos la direccion despues del choque con un robot				
				if (collided.enemy_type == 26)
		            
			        
			        ball_next_x = cos(collided.ball_angle) * 17;
			        ball_next_y = sin(collided.ball_angle) * 17;
			        
			        x = collided.x ;
			        y = collided.y ;
		        else
							
				    // damos la direccion del robot con la bola 8
				    if (ball_type == 7 and energy>0)
					    collision_angle = get_angle(collided);					
					    collided.inc_x = cos(collision_angle) * (speed ) ;
					    collided.inc_y = (sin(collision_angle) * (speed )) * -1 ;
					
					    ball_next_x = ((cos(collision_angle) * (speed ))) * -1;
					    ball_next_y = sin(collision_angle) * (speed );
					    collided.coco_collided = ball_type;
					    collided.coco_energy = energy;
					
				    else
				
					    if (collided.energy <= 0 and collided.inc_x ==0)
						    collided.inc_x = (ball_next_x*0.1) * (speed * 0.1) ;
						    collided.inc_y = (ball_next_y*0.1) * (speed * 0.1) ;
						    collided.speed = speed;
					    end
					
					    if (ball_type != 4) // si no es bola de bolos
						    // cambiamos direccion de la pelota
						    if ( abs((y) - collided.y) > abs((x) - collided.x) )
							    // chocamos de arriba o de abajo
							    ball_next_y *= -1;
							    if(ball_type == 5 and ball_next_y<0)
								    ball_next_y -= 10;
							    end
						    else
							    ball_next_x *= -1;
							    // chocamos de izquierda o derecha
						    end
					    end
				
				    end
				end
				
				
				collided = 0; // reseteamos flag de colision
				//energy--; // se resta energia a si mismo 
				
			End
			
			if (energy <= 0)
				graph = 0;
				coco[0] = cocopart();
				coco[0].inc_x = -5;
				coco[0].inc_y = -5;
				
				coco[1] = cocopart();
				coco[1].inc_x = 5;
				coco[1].inc_y = -5;
				
				if(ball_type == 6)
					bomba();
				End
				
				if (sound_on)
					if(ball_type != 6)
						play_wav(coco_roto_wav,0); // sonido coco roto
					End
				end
				
				while (exists(coco[0]) or exists(coco[1]))
					frame;
				end
			
				break;
			end
		End
	End
End


global
	int path_stiple[7] = 80401004h,40200802h,20100401h,10080200h,8040100h,4020080h,2010040h,1008020h;
	int stiple_step = 0;
	int stiple_color = 1;
	int stiple_color_increment = 20;
end

process draw_path(ball,frame_limit,energy,ball_next_x,ball_next_y, ball_type)
private
	frames = 0; // contador de frames
	
	collision_limit = 4;
	map; // mapa donde voy a dibujar el path
	x0,x1,y0,y1; // x e y de las lineas a dibujar
	
	float ball_next_y_gravity;
	
    // private var copy from ball process
	float ball_x;
	float ball_y;
	int  distance,mouse_cur;
	enemy_block collided, last_collided;
	int red, green, blue, pixel, i, j;
	float collision_angle, my_angle, sum_res, prev_x, prev_y, res_for_div;
	pointer next_mayor; pointer next_menor; pointer coord_mayor; pointer coord_menor;
	speed;
	
	next_x, next_y;
begin
	
	// configura la linea punteada
	drawing_stipple(path_stiple[stiple_step]);
	
	/*
	if (stiple_color >= 250)
		stiple_color_increment = -20;
	elseif (stiple_color <= 1)
		stiple_color_increment = 20;
	end
	
	stiple_color += stiple_color_increment;
	*/
	if(current_stage >49)
		stiple_color = 250;
	else
		stiple_color = 1;
	end
	drawing_color(rgb(stiple_color,stiple_color,stiple_color));
	
	stiple_step++;	
	if (stiple_step==8) 
		stiple_step = 0; 
	end
	
	// crea el mapa donde va a dibujar el path
	map = new_map(ANCHO_PANTALLA,ALTO_PANTALLA,16);
	drawing_map(0,map);
	set_center(0,map,0,0);
	

	// copiamos grafico y posicion inicial de la bola para este proceso
	x = ball.x;
	y = ball.y;
	file = ball.file;
	graph = ball.graph;
	

	// toma parametros con que se va a disparar la bola
	x = resolution_offset_x() + (ANCHO_PANTALLA/2)+1;
	y = (ALTO_PANTALLA/10)*8;
	
	collided = 0;	
	speed = frame_limit;
	ball_next_y_gravity = ball_next_y;
	
	
	// calculamos todo el recorrido de la pelota durante una cantidad de frames limitados
	repeat
	
		x0 = x;
		y0 = y;
		
			

		//Funcion personalizada para advance sin girar el gráfico		
		if(abs(ball_next_x) < abs(ball_next_y))
			next_mayor = &ball_next_y;
			next_menor = &ball_next_x;
			coord_mayor = &y;
			coord_menor = &x;
		else
			next_mayor = &ball_next_x;
			next_menor = &ball_next_y;
			coord_mayor = &x;
			coord_menor = &y;
		end
		if (abs( *next_menor) == 0)
			res_for_div = abs( *next_mayor);
		else
			res_for_div = (abs( *next_mayor)) / (abs( *next_menor));
		end
		sum_res = res_for_div;
		
		
			
		for(i=0;i<=abs( *next_mayor)+1;i++)
		
		
		
			// controlamos la energia tambien
			if (energy <=0 && ball_type != 5)
				break;
			end
			
			// arregla la posicion si la bola se salio de la pantalla
			if(y > (((ALTO_PANTALLA/10)*8))) y = (((ALTO_PANTALLA/10)*8)); ball_next_y *= -1; energy--; collision_limit--; break; End
			if(y < 6) y = 6; ball_next_y *= -1; energy--; collision_limit--; break; End
			if(x > resolution_offset_x() + (ANCHO_PANTALLA-6)) x = resolution_offset_x() + (ANCHO_PANTALLA-6); ball_next_x *= -1; energy--; collision_limit--; break; End
			if(x < resolution_offset_x() +6) x = resolution_offset_x() +6; ball_next_x *= -1; energy--; collision_limit--; break; End
			
			if(i >= sum_res)
				if( *next_menor < 0)
					*coord_menor -= 1;
					if(collided == 0) if (collided = collision_box(type enemy_block)) if (collided.energy > 0 and last_collided != collided) *coord_menor += 1; Break; else collided=0; end End; End;
				elseif( *next_menor > 0)
					*coord_menor += 1;
					if(collided == 0) if (collided = collision_box(type enemy_block)) if (collided.energy > 0 and last_collided != collided) *coord_menor -= 1; Break; else collided=0; end End; End;
				End
				sum_res += res_for_div;
			end
			
			if( *next_mayor < 0)
				*coord_mayor -= 1;
				if(collided == 0) if (collided = collision_box(type enemy_block)) if (collided.energy > 0 and last_collided != collided) *coord_mayor += 1; Break; else collided=0; end End; End;
			elseif( *next_mayor > 0)
				*coord_mayor += 1;
				if(collided == 0) if (collided = collision_box(type enemy_block)) if (collided.energy > 0 and last_collided != collided) *coord_mayor -= 1; Break; else collided=0; end End; End;
			end
			
			if(ball_type == 5) // gravedad aplicada para la bola de pinball
				ball_next_y_gravity += 1.5 - ((speed+1) * 0.07) ;
				
				if(ball_next_y_gravity > 19)
					ball_next_y_gravity = 19;
				end;
				
				ball_next_y = ball_next_y_gravity;				
				
			end
		
		end
		
		
				
		/*Fin de la funcion advance*/
		
		// si chocamos...
		if(exists(collided))
			if (collided.enemy_type == 26)
		        
			    
			    ball_next_x = cos(collided.ball_angle) * 17;
			    ball_next_y = sin(collided.ball_angle) * 17;
			    
			    x = collided.x ;
			    y = collided.y ;
		    else
			    collision_limit--;
			    
			    // damos la direccion del robot con la bola 8
			    if (ball_type == 7)
				    collision_angle = get_angle(collided);					
				
				    ball_next_x = (cos(collision_angle) * (speed )) * -1;
				    ball_next_y = sin(collision_angle) * (speed );
				
			    else
				    if (ball_type != 4) // si no es bola de bolos
					    // cambiamos direccion de la pelota
					    if ( abs((y) - collided.y) > abs((x) - collided.x) )
						    // chocamos de arriba o de abajo
						    ball_next_y *= -1;
						    if(ball_type == 5 and ball_next_y<0)
							    ball_next_y -= 10;
						    end
					    else
						    ball_next_x *= -1;
						    // chocamos de izquierda o derecha
					    end
				    end
				end
			
			end
			last_collided = collided;
			collided = 0;
		end
		
		x1 = x;
		y1 = y;		
		
		collision(0);
		
		draw_line( x0 - resolution_offset_x(), y0 , x1 - resolution_offset_x(), y1);
		
		frames++;
	until(frames >= frame_limit or collision_limit<=0)
	
	x = resolution_offset_x();
	y=0;
	
	file = 0;
	graph = map;
	alpha = 255;
	
	frame;
	
	onexit
	unload_map(0,map);
end
