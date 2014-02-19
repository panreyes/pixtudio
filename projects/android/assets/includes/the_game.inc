FUNCTION int round ( float f )
//Redondea a las unidades cualquier valor real, probado y funciona con positivos y negativos
PRIVATE
	int n;
	float g;
BEGIN
	g = abs ( f );
	n = g;
	g = g - n;
	IF ( g >= 0.5 )
		IF ( f >= 0 )
			RETURN f + 1;
		ELSE
			RETURN f - 1;
		END
	ELSE
		RETURN f;
	END
END

/**
 * generic process to put images that doesn't need logic
 */
process trinchera(file,graph,x,y,z)
private
	type_effect shake_it_baby;
	my_ball ball;
	original_y = 0;
	anim = 0;
end
begin
	
	loop
		if (ball = collision(type my_ball) )
			if (exists(ball))
				if ( ball.shoot ==true and !exists(anim))
					original_y = y;
					shake_it_baby.property = &y;
					shake_it_baby.effectType = motion_effect.elasticEaseIn;
					shake_it_baby.fromValue = y+1;
					shake_it_baby.toValue=y;
					shake_it_baby.duration=10;
				
					anim=applyEffect(&shake_it_baby);
				end
			end
			
		end
		
		if ( must_shake == true and !exists(anim))
			//say('asda');
			original_y = y;
			shake_it_baby.property = &y;
			shake_it_baby.effectType = motion_effect.elasticEaseIn;
			shake_it_baby.fromValue = y+1;
			shake_it_baby.toValue=y;
			shake_it_baby.duration=10;
		
			anim = applyEffect(&shake_it_baby);
			must_shake = false;
		end
		
		if (!exists(anim) and original_y != 0)
			y=original_y;
		end
		frame;
		
	end
end

/**
 * proccess that assigns points to the player and shows a little number where that father is placed
 */
process points(int points)
private
type_effect anim;
int anim_running;
begin
	x = father.x;
	y = father.y;
	z = father.z - 1;
/*
	if (points>0)
		graph =  write_in_map ( plus_points_fnt ,"+" + (string) points , 4 );
	else
		graph =  write_in_map ( minus_points_fnt ,(string) points , 4 );
	end
*/	
	// configuramos una animacion 
	anim.property = &y;
	anim.effectType = motion_effect.regularEaseOut;
	anim.fromValue = y;
	anim.toValue = y - 15;
	anim.duration = 20;
	
	anim_running  = applyEffect(&anim);
	
	while(exists(anim_running))
		frame;
	end
	
	while (alpha>0)
		alpha -= 20;
		frame;
	end
	
onexit
	unload_map(0,graph);
end


/**
 * juega una pantalla ( GLOBAL current_stage)
 */
process the_game()
private	
	my_ball ball;
	int i,e;
	wait;
	current_ball = 0;
	int shooting_area;
	t_front,t_back;
	sign;
	byte puntaje;
	win = false; // flag q indica que se gano el juego
	button pause_button;
	byte unblock_special = false, unblocked_special = false;
	mono monkey;	
	boss;
end
begin
	// seteo del modo de la pantalla
	autodetect_mode(ANCHO_PANTALLA,ALTO_PANTALLA,COLOR_DEPTH); // resolucion
	file = stage_fpg;
	fader = 0;
	fade(100,100,100,10);
	
	// define la region para saber cuando algo esta fuera de la pantalla jugable
	region_define ( 1 , resolution_offset_x() , 0 ,  ANCHO_PANTALLA , ALTO_PANTALLA ); 

	
	
	// pinta el fondo de la pantalla
	switch(current_stage)
		// primer mundo jungla
		case 0 .. 19:
			
			// pinta un patron en el fondo para ocupar la parte de la pantalla que sobre debido a la resolucion del dispositivo
			if (resolution_offset_x() > 0)
				start_scroll(1,file,11,0,0,15); // patron
				scroll[1].z=600;
			end
			
			sign = dummy_process(file,4,resolution_offset_x() + (ANCHO_PANTALLA / 2),(ALTO_PANTALLA / 2)); // detalles estaticos
			sign.z=512;
			start_scroll(0,file,2,1,1,5); // nubes
			scroll[0].z=513;
			
			sign = dummy_process(file,12,resolution_offset_x() + (ANCHO_PANTALLA / 2) -1,(ALTO_PANTALLA / 2)); // detalles estaticos
			sign.z = -1;
			
			// dibujamos la trinchera del mono!
			palos = palos_process(cocofpg, 25,resolution_offset_x() +73,188);
			t_front = trinchera(t_fpg,2,resolution_offset_x() + (ANCHO_PANTALLA/2),ALTO_PANTALLA-30-1,-5);
			t_back = trinchera(t_fpg,1,resolution_offset_x() + (ANCHO_PANTALLA/2),ALTO_PANTALLA-30-1,+5);
		end		
		// segundo mundo arbol
		case 20 .. 24:
			if (resolution_offset_x() > 0)
				// pinta un patron en el fondo para ocupar la parte de la pantalla que sobre debido a la resolucion del dispositivo
				start_scroll(1,file,17,0,0,15); // patron
				scroll[1].z=600;
			end
			
			sign = dummy_process(file,6,resolution_offset_x() + (ANCHO_PANTALLA / 2),(ALTO_PANTALLA / 2)); // detalles estaticos
			sign.z=512;
			start_scroll(0,file,5,0,1,5); // nubes			
			scroll[0].z=513;
			
			sign = dummy_process(file,12,resolution_offset_x() + (ANCHO_PANTALLA / 2) -1,(ALTO_PANTALLA / 2)); // detalles estaticos
			sign.z = -1;
			
			// dibujamos la trinchera del mono!
			palos = palos_process(cocofpg, 25,resolution_offset_x() +73,188);
			t_front = trinchera(t_fpg,2,resolution_offset_x() + (ANCHO_PANTALLA/2),ALTO_PANTALLA-30-1,-5);
			t_back = trinchera(t_fpg,1,resolution_offset_x() + (ANCHO_PANTALLA/2),ALTO_PANTALLA-30-1,+5);
		end
		// tercer mundo templo
		case 25 .. 44:
			if (resolution_offset_x() > 0)
				// pinta un patron en el fondo para ocupar la parte de la pantalla que sobre debido a la resolucion del dispositivo
				start_scroll(1,file,13,0,0,15); // patron
				scroll[1].z=600;
			end
	
			sign = dummy_process(file,3,resolution_offset_x() + (ANCHO_PANTALLA / 2),(ALTO_PANTALLA / 2)); // detalles estaticos			
			sign.z=512;
			start_scroll(0,file,5,0,1,5); // nubes			
			scroll[0].z=513;
			
			sign = dummy_process(file,14,resolution_offset_x() + (ANCHO_PANTALLA / 2) -1,(ALTO_PANTALLA / 2)); // detalles estaticos
			sign.z = -1;
			
			// dibujamos la trinchera del mono!
			palos = palos_process(cocofpg, 25,resolution_offset_x() +73,188);
		end
		case 45 .. 49: // nave de fondo
			if (resolution_offset_x() > 0)
				// pinta un patron en el fondo para ocupar la parte de la pantalla que sobre debido a la resolucion del dispositivo
				start_scroll(1,file,18,0,0,15); // patron
				scroll[1].z=600;
			end

			sign = dummy_process(file,7,resolution_offset_x() + (ANCHO_PANTALLA / 2),(ALTO_PANTALLA / 2)); // detalles estaticos			
			start_scroll(0,file,5,0,1,5); // nubes			
			scroll[0].z=513;
			sign.z=512;
			
			// dibujamos la trinchera del mono!
			palos = palos_process(cocofpg, 25,resolution_offset_x() +73,188);
		end
		default: // adentro de la nave
			if (resolution_offset_x() > 0)
				// pinta un patron en el fondo para ocupar la parte de la pantalla que sobre debido a la resolucion del dispositivo
				start_scroll(1,file,16,0,0,15); // patron
				scroll[1].z=600;
			end

			sign = dummy_process(file,8,resolution_offset_x() + (ANCHO_PANTALLA / 2),(ALTO_PANTALLA / 2)); // detalles estaticos
			sign.z=512;
			
			start_scroll(0,file,9,10,1, 10 ); // fondo que se mueve
			scroll[0].z=513;
			scroll[0].ratio = 0;
			
			sign = dummy_process(file,15,resolution_offset_x() + (ANCHO_PANTALLA / 2),(ALTO_PANTALLA / 2)); // fonde full screen
			sign.z = -1;
			
			// dibujamos la trinchera del mono!
			palos = palos_process(cocofpg, 25,resolution_offset_x() +73,188);
		end
	end
	sign = 0;
	// arreglo fondo segun resolucion
	scroll[0].x0 = resolution_offset_x();
	scroll[0].x1 = resolution_offset_x();
	
    
	//flip_current_stage(current_stage);
	
	// crea los enemigos en la pantalla
	for (i=0;i < 14;i++)
		for (e=0;e < 18;e++)			
			if (stages[current_stage].blocks[( i + (14 * (e)) )] != 0)
				enemy_block(resolution_offset_x() + (i*10) + 8 + 7, (e*10) + 8 + 7, stages[current_stage].blocks[( i + (14 * (e)) )]);
			end
		end
	end
	
	
	
	// lo metemo al mono
	monkey = mono();
	//say(map_info(0,0,G_WIDTH));
	// en mobile dibujamos el boton de pausa
	if (touchscreen())		
		pause_button = button(27,27,11,10);
		pause_button.alpha = 125;
	end
	
	balls_used = 0; // reiniciamos contador!!
	restart_stage = false;
	
	if (current_stage == STAGE_COUNT - 1)
		boss = dummy_process(boss_fpg,2,resolution_offset_x() + (ANCHO_PANTALLA / 2) + 6,20 + 6);
		boss.z = +1;
	end
	
	repeat
		
		if ((touchscreen() and pause_button.clicked) or control_(1,CONTROL_CANCEL))
			pause();
		end
		
		if (resolution_offset_x() > 0)
			// anima fondo
			scroll[1].y0++;		
			scroll[1].x0++;
		end
		
		switch(current_stage)
			// primer mundo
			case 0 .. 24:
			scroll[0].x1+=2;		
			scroll[0].x0++;
			end
			case 25 .. 49:
			scroll[0].x0--;
			end
			case 50 .. 1000:
			scroll[0].y1-=2;		
			scroll[0].y0--;
			end
		end
		
		// busca enemigos con energia, si no encuentra, entonces ganamos! ;D
		win = true;
		while( (x=get_id(type enemy_block)) ) // while there is an unprocessed process left and store that in 'x'
			if (x.energy > 0)
				win = false;
				break;
			end
		end
		
		// si no se mostro el how to play lo mostramo

		if (!how_to_play_shown and current_stage == 0)
			sign = how_to_play();			
			while (exists(sign))
				frame;
			end
		end

		// dependiendo de si se gano o no..
		if (win)
		
			if (current_stage < STAGE_COUNT - 1)
				// desbloqueamos la siguiente pantalla
				next_stage = current_stage + 1;
				
				// si la siguiente pantalla es la primera del siguiente mundo
				if ((current_stage  + 6 )% 25 == 0 and current_stage !=0 and current_stage < 51)
					next_stage = current_stage + 6;
				end
				
				// desbloqueamos siguiente pantalla (evitamos destrabar la ultima pantalla)
				if (next_stage != STAGE_COUNT - 1)
					if (stage_points[next_stage].status == 0)
						stage_points[next_stage].status = 1;					
					end				
				end
			end
			
			// le asigna puntaje obtenido a la pantalla actual
			puntaje = 4 - balls_used;
			if ((stage_points[current_stage].status - 1) < puntaje )
				stage_points[current_stage].status = 1 + puntaje;
			end
			
			// desnbloqueo de pantallas
			unblocked_special = false;
			
			// checkqueamos si tenemos que desbloquear la primera de las filas de pantallas especiales				
			if (current_stage < 51)
				e = round(current_stage/25);	
				e = (e*25); // posicionamos a e en el principio del "mundo" actual
				
				unblock_special = true;
				
				For (i = e; i <= e + 19; i++)
					if (i < STAGE_COUNT -1) 
						if (stage_points[i].status < 4)
							unblock_special = false;
							break;
						end
					end 
				End

				if (e+20 < STAGE_COUNT - 1)
					if (unblock_special and stage_points[e+20].status == 0)
						stage_points[e+20].status = 1;
						unblocked_special = true;
					end
				end
			
			end

			// checkeamos si tenemos que desbloquear la ultima pantalla
			unblock_special = true;
			for (i = 0; i < STAGE_COUNT - 1;i++)
				if (stage_points[i].status < 4)
					unblock_special = false;
					break;
				end
			end
			if (unblock_special and stage_points[STAGE_COUNT - 1].status == 0)
				stage_points[STAGE_COUNT - 1].status = 1;
				unblocked_special = true;
			end
			
			// guardamos el avance
			save(savefilepath,stage_points); 
			
			// dormimos la bolita para que deje de rebotar
			signal(ball,S_FREEZE); 
			
			// esperamos que los enemigos salgan de la pantalla
			while (exists(type enemy_block)) 
				frame;
			end
			
			// dormimos al resto de los procesos (como una pausa, vamos)
			signal(id,S_FREEZE_TREE); 
			signal(id,S_WAKEUP );
			signal(monkey,S_WAKEUP );
			
			// festeja el mono
			monkey.status = "win";
			monkey.anim_pos = 0;
			
			// si acabamos el juego
			if (current_stage == STAGE_COUNT - 1)
				next_stage = current_stage + 1;
				for (i=0;i<150;i++)
					x = rand(resolution_offset_x() , resolution_offset_x() + ANCHO_PANTALLA);
					y = rand(resolution_offset_y() , resolution_offset_y() + ALTO_PANTALLA);
					explosion();
					if (sound_on)
						play_wav(explosion_wav,0); 
					end
					frame;
				end
				fade_out_slow();
				return; // se acaba la joda!
			end
			
			// muestra el cartel de pantalla desblockeada
			if (unblocked_special)
				sign = stages_unblocked();
				while (exists(sign))
					frame;
				end
			end
			
			// muestra el cartel y espera a que se cierre
			sign = sign_clear();
			while (exists(sign))
				frame;
			end
			
			return; // se termina el juego
			
		else		
			// checkeamos si no hay bolita (quizas se acaba de morir, o quizas es la primera bolita)
			if (!exists(ball))
				if (current_ball < (sizeof(stages[0].balls)/sizeof(byte)) and stages[current_stage].balls[current_ball]!=0)
					// dibujamos la ballesta
					ballesta = crossbow();
					// le quedan bolitas
					ball = my_ball(stages[current_stage].balls[current_ball]);
					
					current_ball++;
					balls_used++;
				else
					// perdio todas las bolitas
				
					// espera x segundos
					signal(id,S_FREEZE_TREE); // dormimos al resto de los procesos (como una pausa, vamos)
					signal(id,S_WAKEUP );
					signal(monkey,S_WAKEUP );
					
					// llora el mono 
					monkey.status = "loose";
					monkey.anim_pos = 0;
					
					// espera x segundos
					sign = sign_fail();
					while (exists(sign))
						frame;
					end
					
					return; // se termina el juego
				end
			else
				//si hay bolita escondemos el control de disparar
				if (ball.shoot and exists(shooting_area))
					signal(shooting_area,S_KILL_TREE);
				end
			end
		end 
        frame;
    until(exit_to_menu or restart_stage)
	
	
OnExit	
	signal(id,S_KILL_TREE); // matamos todos los procesos creados en esta pantalla	
	stop_scroll(0);
	if (resolution_offset_x() > 0)
		stop_scroll(1);
	end
end
