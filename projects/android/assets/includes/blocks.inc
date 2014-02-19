/*
 Proceso enemigo
 Estan todos los enemigos en el mismo proceso para poder preguntar la collision por un solo tipo
 valores type:
  1: Gear
  2: tubo con pinchos
  3: pinza. 2 golpes
  4: cangrejo, 2 golpes
  5: cubo que se mueve a la derecha
  6: cubo que se mueve para arriba
  7: cubo que se mueve para abajo
  8: cubo que se mueve hacia izquierda
  9: enemigo que desaparece
  10: enemigo que aparece
  ------- Fin 1er mundo --------
  11: cañon que dispara a la derecha
  12: cañon que dispara a la izquierda
  13: arañita que camina hacia arriba (pared izquierda)
  14: arañita que camina hacia arriba pero para pared derecha
  15: sierra q rompe coco
  16: Bomba
  ------- Fin 2do mundo --------
  17: Robot de un solo lado golpeable Abajo 
  18: Robot de un solo lado golpeable Arriba
  19: Robot de un solo lado golpeable Derecha
  20: Robot de un solo lado golpeable Izquierda
  21: Robot de una sierra (derecha) 
  22: Robot de una sierra (izquierda) 
  23: Robot de una sierra (abajo) 
  24: Robot de una sierra (arriba) 
  25: Smoker
  26: Prisma
  27: Boss Ojo izq
  28: Boss Ojo cent
  29: Boss Ojo der
 */
process enemy_block(x, y,  block_type)
public
	inc_y = 0;
	inc_x = 0;
	
	byte coco_collided = 0;
	byte coco_energy = 0;
	
	enemy_type;
	string status = "";
	speed=1;
	float ball_angle;
end
private
	byte anim_default[11]  = 1,1,1,2,2,2,3,3,3,4,4,4;
	byte anim_type_2[11]   = 5,5,5,6,6,6,7,7,7,8,8,8;
	byte anim_type_3[11]   = 9,9,9,10,10,10,11,11,11,12,12,12;
	byte anim_type_3_1[3] = 13,14,15,16;
	byte anim_type_4[11] = 17,17,17,18,18,18,19,19,19,20,20,20;
	byte anim_type_4_1[3] = 21,22,23,24;
	
	// enemigo que se mueve en forma horizontal
	byte anim_type_5 = 25;
	byte anim_type_5_opening_left[11] = 26,26,27,27,28,28,29,29,30,30,31,31;
	byte anim_type_5_closing_left[11] = 31,31,30,30,29,29,28,28,27,27,26,26;
	byte anim_type_5_open_left = 31;
	byte anim_type_5_opening_right[11] = 38,38,39,39,40,40,41,41,42,42,43,43;
	byte anim_type_5_closing_right[11] = 43,43,42,42,41,41,40,40,39,39,38,38;
	byte anim_type_5_open_right = 43;
	// enemigo q se mueve en forma vertical
	byte anim_type_6 = 25;
	byte anim_type_6_opening_bottom[11] = 44,44,45,45,46,46,47,47,48,48,49,49;
	byte anim_type_6_closing_bottom[11] = 49,49,48,48,47,47,46,46,45,45,44,44;
	byte anim_type_6_open_bottom = 49;
	byte anim_type_6_opening_top[11] = 32,32,33,33,34,34,35,35,36,36,37,37;
	byte anim_type_6_closing_top[11] = 37,37,36,36,35,35,34,34,33,33,32,32;
	byte anim_type_6_open_top = 37;
	
	// enemigo que desaparece
	byte anim_type_9[47] = 50,50,51,51,56,56,56,57,57,57,58,58,58,55,55,50,50,50,51,51,52,52,52,53,53,53,54,54,54,55,55,50,50,50,51,51,56,56,56,57,57,57,58,58,58,55,55,50;
	byte anim_type_9_hide[9] = 59,59,60,60,61,61,62,62,63,63;
	byte anim_type_9_show[9] = 64,64,65,65,66,66,67,67,68,68;
	
	// enemigo que dispara
	byte anim_type_11[87] = 69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,70,71,72,69,
				69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,70,71,72,69,
				69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,70,71,72,69,
				69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69;
	
	byte anim_type_13_subiendo[15] = 73,73, 74,74, 75,75, 76,76, 77,77, 78,78, 79,79, 80,80;
	byte anim_type_13_bajando[15] = 80,80, 79,79, 78,78, 77,77, 76,76, 75,75, 74,74, 73,73;
	
	byte anim_type_15_closed = 88;
	byte anim_type_15_opening[3] = 89,89,90,90;
	byte anim_type_15_closing[5] = 85,85,86,86,87,87;
	byte anim_type_15_running[3] = 81,82,83,84;
	
	byte anim_type_16[15] = 91,91,91,91,92,92,92,92,93,93,93,93,94,94,94,94;
	
	// enemigos duros que se rompen solo desde un lado
	// abajo
	byte anim_type_17[15] = 95,95,95,96,97,98,99,95,95,95,95,95,95,95,95,95;
	//arriba
	byte anim_type_18[15] = 100,100,100,101,102,103,104,100,100,100,100,100,100,100,100,100;
	// derecha
	byte anim_type_19[15] = 105,105,105,106,107,108,109,105,105,105,105,105,105,105,105,105;
	// izquierda
	byte anim_type_20[15] = 110,110,110,111,112,113,114,110,110,110,110,110,110,110,110,110;

	// enemigos con sierra a un lado
	// derecha
	byte anim_type_21[5] = 115,115,116,116,117,117;
	//izq
	byte anim_type_22[5] = 118,118,119,119,120,120;
	// abajo
	byte anim_type_23[5] = 121,121,122,122,123,123;
	// arriba
	byte anim_type_24[5] = 124,124,125,125,126,126;
	
	// enemigo que tira humito para arriba
	byte anim_type_25[7] = 131,131,132,132,133,133,134,134;
	
	// enemigo que desvia linea guia
	byte anim_type_26[7] = 127,127,128,128,129,129,130,130;
	
	//boss izq
	byte anim_type_27[7] = 136,135,136,136,136,135,135,135;	
	//boss cent
	byte anim_type_28[9] = 139,139,139,138,138,138,139,139,138,138;	
	//boss der
	byte anim_type_29[4] = 141,142,142,142,141;
	
	byte anim_pos = 0;
	
	
	
	byte pointer anim_pointer;
	byte count;

	framecounter=0;

	// tiempo de espera del cubo que se mueve en que se queda quiero
	stay_time=30;
	type_effect motion;
	current_motion;
	
	fueguito fuego;
	enemy_block block_collided;
	collitioned =0;
	
	
end

begin
	enemy_type = block_type;
	region = 1;
	
	switch(block_type)
		case 3,4:
			energy	= 2;
			file = enemies_fpg;
		end
		default:
			energy	= 1;
			file = enemies_fpg;
		end
	end
	
	// estado inicial para enemigos que se mueven
	switch(block_type)
		case 5:
			status = "wait to left"; // de izq a derecha
		end
		case 6:
			status = "wait to bottom"; // de abajo a arriba
		end
		case 7:
			status = "wait to top"; // de arriba a abajo
		end
		case 8:
			status = "wait to right"; // de derecha a izquierda
		end
		case 9:
			status = "wait to hide"; // enemigo que desaparece
		end
		case 10:
			status = "hidden"; // enemigo que aparece
			framecounter = 0;
			anim_pos = 0;
			alpha=0;
			y -= 160;
			// le tenemos que chantar una animacion de prepo
			anim_pointer = &anim_type_9;
			count = sizeof(anim_type_9)/sizeof(byte);
		end
		case 13: //arañita q sube
			status = "going up";
		end 
		case 12: //damos vuelta el bot que dispara
			flags = 1;
		end 
		case 14: //arañita q sube
			status = "going up";
			flags = 1;
		end
		case 15: // sierra
			status = "closed";
			framecounter = 0;
		end
	end
	border();
	Loop
	
		switch(block_type)
		
			case 15: // sierra
				switch(status)
					case "closed":
						anim_pointer = &anim_type_15_closed;
						count = sizeof(anim_type_15_closed)/sizeof(byte);
						framecounter++;
						if (framecounter > stay_time)
							status = "opening";
							anim_pointer = &anim_type_15_opening;
							count = sizeof(anim_type_15_opening)/sizeof(byte);
							anim_pos=0;
						end
					end
					case "opening":
						if (anim_pos == count -1)
							status = "running";							
							framecounter = 0;
							anim_pointer = &anim_type_15_running;
							count = sizeof(anim_type_15_running)/sizeof(byte);
							anim_pos=0;							
						end						
					end
					case "running":						
						framecounter++;
						if (framecounter > stay_time)
							status = "closing";
							anim_pointer = &anim_type_15_closing;
							count = sizeof(anim_type_15_closing)/sizeof(byte);
							anim_pos=0;							
						end
					end
					case "closing":
						if (anim_pos == count -1)
							status = "closed";							
							framecounter = 0;
							anim_pointer = &anim_type_15_closed;
							count = sizeof(anim_type_15_closed)/sizeof(byte);
							framecounter = 0;
							anim_pos = 0;
						end						
					end
				end
				
				
			end
			case 5,6,7,8:
				switch (status)
					case "wait to bottom","wait to top":
						// si esta quieto en el lugar espera a tener que abrir
						anim_pointer = &anim_type_6;

						count = sizeof(anim_type_6)/sizeof(byte);
						framecounter++;
						
						// se paso el tiempo de espera
						if (framecounter>=stay_time)
							// setea nueva anim 							
							anim_pos = 0;

							framecounter = 0;
							
							switch (status)
								case "wait to bottom":
									status = "opening bottom";
									// anim de abrir compuerta
									anim_pointer = &anim_type_6_opening_bottom;
									count = sizeof(anim_type_6_opening_bottom)/sizeof(byte);
								end
								case "wait to top":
									status = "opening top";
									// anim de abrir compuerta
									anim_pointer = &anim_type_6_opening_top;
									count = sizeof(anim_type_6_opening_top)/sizeof(byte);
								end
							end
						end
					end
					case "wait to left","wait to right":
						// si esta quieto en el lugar espera a tener que abrir
						anim_pointer = &anim_type_5;
						count = sizeof(anim_type_5)/sizeof(byte);
						framecounter++;
						
						// se paso el tiempo de espera
						if (framecounter>=stay_time)
							// setea nueva anim 							
							anim_pos = 0;
							framecounter = 0;
							
							switch (status)
								case "", "wait to left":
									status = "opening left";
									// anim de abrir compuerta
									anim_pointer = &anim_type_5_opening_left;
									count = sizeof(anim_type_5_opening_left)/sizeof(byte);
								end
								case "wait to right":
									status = "opening right";
									// anim de abrir compuerta
									anim_pointer = &anim_type_5_opening_right;
									count = sizeof(anim_type_5_opening_right)/sizeof(byte);
								end
							end
						end
					end
					case "opening bottom":
					
						// si termina la anim pasa al siguiente estado
						if (anim_pos == count-1)
							status = "moving bottom";
							anim_pos = 0;
							
							// termino de abrirse
							anim_pointer = &anim_type_6_open_bottom;
							count = sizeof(anim_type_6_open_bottom)/sizeof(byte);					

							
							// setea anim de moverse
							motion.property = &y;
							motion.effectType = motion_effect.regularEaseOut;
							motion.fromValue = y;

							motion.toValue = y - 60;
							motion.duration  = 50;
							
							current_motion = applyEffect(motion);
							

							fuego = fueguito();
							fuego.diff_x = 0;
							fuego.diff_y = -12;
							fuego.angle = 270000;
						end
						
					end
					case "opening left":
					
						// si termina la anim pasa al siguiente estado
						if (anim_pos == count-1)
							status = "moving left";
							anim_pos = 0;
							
							// termino de abrirse
							anim_pointer = &anim_type_5_open_left;
							count = sizeof(anim_type_5_open_left)/sizeof(byte);					
							
							// setea anim de moverse
							motion.property = &x;
							motion.effectType = motion_effect.regularEaseOut;
							motion.fromValue = x;
							motion.toValue = x + 60;
							motion.duration  = 50;
							
							current_motion = applyEffect(motion);
							
							fuego = fueguito();
							fuego.diff_y = 0;
							fuego.diff_x = 12;
						end
						
					end
					case "opening right":
					
						// si termina la anim pasa al siguiente estado
						if (anim_pos == count-1)
							status = "moving right";
							anim_pos = 0;
							
							// termino de abrirse
							anim_pointer = &anim_type_5_open_right;
							count = sizeof(anim_type_5_open_right)/sizeof(byte);					
							
							// setea anim de moverse
							motion.property = &x;
							motion.effectType = motion_effect.regularEaseOut;
							motion.fromValue = x;
							motion.toValue = x - 60;
							motion.duration  = 50;
							
							current_motion = applyEffect(motion);
							
							fuego = fueguito();
							fuego.diff_y = 0;
							fuego.diff_x = -12;
							fuego.angle = 180000;
						end
					end	
					case "opening top":

					
						// si termina la anim pasa al siguiente estado
						if (anim_pos == count-1)

							status = "moving top";
							anim_pos = 0;
							
							// termino de abrirse
							anim_pointer = &anim_type_6_open_top;
							count = sizeof(anim_type_6_open_top)/sizeof(byte);					
							
							// setea anim de moverse
							motion.property = &y;

							motion.effectType = motion_effect.regularEaseOut;
							motion.fromValue = y;
							motion.toValue = y + 60;
							motion.duration  = 50;
							
							current_motion = applyEffect(motion);

							
							fuego = fueguito();
							fuego.diff_x = 0;
							fuego.diff_y = 12;
							fuego.angle = 90000;
						end
						
					end
					case "moving bottom" , "moving top","moving left" , "moving right":
						if (!exists(current_motion))

							switch (status)
								case "moving top":
									status = "closing top";
									anim_pos = 0;
									// termino de abrirse
									anim_pointer = &anim_type_6_closing_top;
									count = sizeof(anim_type_6_closing_top)/sizeof(byte);
								end
								case "moving bottom":
									status = "closing bottom";
									anim_pos = 0;
									// termino de abrirse
									anim_pointer = &anim_type_6_closing_bottom;

									count = sizeof(anim_type_6_closing_bottom)/sizeof(byte);
								end
					
								case "moving right":
									status = "closing right";
									anim_pos = 0;
									// termino de abrirse
									anim_pointer = &anim_type_5_closing_right;
									count = sizeof(anim_type_5_closing_right)/sizeof(byte);
								end
								case "moving left":
									status = "closing left";
									anim_pos = 0;
									// termino de abrirse
									anim_pointer = &anim_type_5_closing_left;
									count = sizeof(anim_type_5_closing_left)/sizeof(byte);
								end
							end
						end						
					end
					case "closing left" , "closing right", "closing bottom" , "closing top":
						if (anim_pos == count-1)
							anim_pointer = &anim_type_5;
							count = sizeof(anim_type_5)/sizeof(byte);
							anim_pos = 0;
							switch (status)
								case "closing left":
									status = "wait to right";
									
								end
								case "closing right":
									status = "wait to left";
									
								end
					
								case "closing bottom":
									status = "wait to top";
									
								end
								case "closing top":
									status = "wait to bottom";
									
								end
							end
						end						
					end									
				end
				
			end
			
			// enemigo que desaparece
			case 9,10:
				
				switch(status)
					case "wait to hide":
						anim_pointer = &anim_type_9;
						count = sizeof(anim_type_9)/sizeof(byte);
						if (anim_pos == count -1)
							status = "hiding";
							anim_pointer = &anim_type_9_hide;
							count = sizeof(anim_type_9_hide)/sizeof(byte);
							anim_pos=0;
						end
					end
					case "hiding":
						if (anim_pos == count -1)
							status = "hidden";							
							framecounter = 0;
							anim_pos = 0;
							alpha=0;
							y -= 160;
						end						
					end
					case "hidden":
						
						framecounter++;
						if (framecounter > sizeof(anim_type_9)/sizeof(byte))
							status = "showing";
							anim_pointer = &anim_type_9_show;
							count = sizeof(anim_type_9_show)/sizeof(byte);
							anim_pos=0;
							alpha=255;
							y+=160;
						end
					end
					case "showing":
						if (anim_pos == count -1)
							status = "wait to hide";							
							framecounter = 0;
							anim_pointer = &anim_type_9;
							count = sizeof(anim_type_9)/sizeof(byte);
							
							anim_pos = 0;
						end						
					end
				end				
			end
			
			case 11,12:	// dispara a la derecha	
				anim_pointer = &anim_type_11;
				count = sizeof(anim_type_11)/sizeof(byte);			
				if (anim_pointer[anim_pos]==70)
					if(block_type==12)
						energy_ball(x-10,y,-1,0);
					else
						energy_ball(x+10,y,1,0);
					end
				end
			end

			case 13,14: // araña
				switch (status)
					case "going up":
						anim_pointer = &anim_type_13_subiendo;
						count = sizeof(anim_type_13_subiendo)/sizeof(byte);
						y -= 1;
						if(y < 6)
							status = "going down";
							y += 1;
						end
					end
					case "going down":
						anim_pointer = &anim_type_13_bajando;
						count = sizeof(anim_type_13_bajando)/sizeof(byte);
						y += 1;
						if(y > (((ALTO_PANTALLA/10)*8)))
							status = "going up";
							y -= 1;
						end
					end
				end
			end
			
			case 4:	
				if (energy>1)
					anim_pointer = &anim_type_4;
					count = sizeof(anim_type_4)/sizeof(byte);
				else
					anim_pointer = &anim_type_4_1;
					count = sizeof(anim_type_4_1)/sizeof(byte);
				end
			end
		
			case 3:
				if (energy>1)
					anim_pointer = &anim_type_3;
					count = sizeof(anim_type_3)/sizeof(byte);
				else
					anim_pointer = &anim_type_3_1;
					count = sizeof(anim_type_3_1)/sizeof(byte);
				end
			end
		
			case 2:
				anim_pointer = &anim_type_2;
				count = sizeof(anim_type_2)/sizeof(byte);
			end
			case 1:
				anim_pointer = &anim_default;
				count = sizeof(anim_default)/sizeof(byte);
			end
			
			case 16:
				anim_pointer = &anim_type_16;
				count = sizeof(anim_type_16)/sizeof(byte);
			end
			
			case 17:
				anim_pointer = &anim_type_17;
				count = sizeof(anim_type_17)/sizeof(byte);
			end
			case 18:
				anim_pointer = &anim_type_18;
				count = sizeof(anim_type_18)/sizeof(byte);
			end
			case 19:
				anim_pointer = &anim_type_19;
				count = sizeof(anim_type_19)/sizeof(byte);
			end
			case 20:
				anim_pointer = &anim_type_20;
				count = sizeof(anim_type_20)/sizeof(byte);
			end
			case 21:
				anim_pointer = &anim_type_21;
				count = sizeof(anim_type_21)/sizeof(byte);
			end
			case 22:
				anim_pointer = &anim_type_22;
				count = sizeof(anim_type_22)/sizeof(byte);
			end
			case 23:
				anim_pointer = &anim_type_23;
				count = sizeof(anim_type_23)/sizeof(byte);
			end
			case 24:
				anim_pointer = &anim_type_24;
				count = sizeof(anim_type_24)/sizeof(byte);
			end
			case 25:
				anim_pointer = &anim_type_25;
				count = sizeof(anim_type_25)/sizeof(byte);
				smoke(rand(-1,1),rand(-3,-7));
				son.y -= 30;
			
				
			end
			case 26:
				anim_pointer = &anim_type_26;
				count = sizeof(anim_type_26)/sizeof(byte);
				
			end
			case 27:
				anim_pointer = &anim_type_27;
				count = sizeof(anim_type_27)/sizeof(byte);
			end	
			case 28:
				anim_pointer = &anim_type_28;
				count = sizeof(anim_type_28)/sizeof(byte);
			end	
			case 29:
				anim_pointer = &anim_type_29;
				count = sizeof(anim_type_29)/sizeof(byte);
			end
		end
		
		
	
		// anima 
		anim_pos++;
		if (anim_pos >= count)
			anim_pos = 0;
		end
		graph = anim_pointer[anim_pos];			

		// chocado por la bola 8 (sale disparado y choca otros enemigos)
		if (coco_collided ==7)
			while (!out_region(id,1))
				
				speed = speed / 8;
				if(speed <1) speed = 1;	end
				
				x+= inc_x * speed;
				y+= inc_y * speed;
				
				speed-=1;
					
				angle+=5000;	

				if (rand(1,100) > 25)
					humo(0,0);
				else
					explosion();
				end				
				
				if (block_collided = collision_box(type enemy_block))
					if(collitioned < 10) //para que solo choque 10 veces asi no se cuelga
						block_collided.energy = 0;
						block_collided.coco_collided = 7;
						block_collided.inc_x = inc_x;
						block_collided.inc_y = inc_y;
						block_collided.speed = speed;
						collitioned++;
						if (sound_on)
							play_wav(ball8_wav,0);
							//play_wav(golpe_robot_wav,0); // sonido coco roto
						end
						inc_x *= -1;
						inc_y *= -1;
					end
				end	
				
				frame;
			end;
		End	
		
		ball_angle += 2500;	
		        
        if (ball_angle>360000)
            ball_angle = 0;				
	    end
		
		if (energy == 0)
			if (block_type == 16)
				bomba();
			else
				if (exists(current_motion))
					signal(current_motion,s_kill);
				end
				// sin energia se muere
				explosion();
				while (!out_region(id,1))
					if (rand(1,100) > 25)
					humo(0,0);
					else
					explosion();
					end
					
					angle+=5000;
					
					y+=inc_y;
					if (inc_y<15)
						inc_y += 1;
					end
					
					x+=inc_x;
					
					frame;
				end
			end
			break;
		end

        frame;
		
		
		
	End;
onexit:
	if (exists(current_motion))
		signal(current_motion,s_kill);
	end
	//signal(id,s_kill_tree);
End
