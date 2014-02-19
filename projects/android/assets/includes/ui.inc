global
	type_effect letra_effect[8];
	int letra_img[8];
end

/**
 * proceso boton con propiedad clicked (on mouse up) 
 */
local
normal_graph,pressed_graph;
end




process new_feature(int fpg, int map, string pointer description)
private
	type_effect anim, anim2;
	int anim_running, anim2_running;
	int icon,sign;
	int text[2];
	byte i;
	
begin
	// mostramos fondo	
	autodetect_mode(ANCHO_INTERFAZ,ALTO_INTERFAZ,COLOR_DEPTH); frame; // cambia resolucion
	screen_clear();
	
	
	// pinta un patron en el fondo para ocupar la parte de la pantalla que sobre debido a la resolucion del dispositivo
	start_scroll(1,stage_fpg,13,0,0,15); // patron
	scroll[1].z=600;		
	
	// pinta tele 
	sign = dummy_process(ui_fpg,23,resolution_offset_x() + (ANCHO_INTERFAZ / 2),(ALTO_INTERFAZ / 2)); // detalles estaticos				
	sign.z=512;
	
	shadow(sign, 10,10);
	
	// mostramos el icono
	icon=dummy_process(fpg,map,resolution_offset_x() + 160,180);
	
	// animamos tamaño
	anim.property = &icon.size;
	anim.effectType = motion_effect.elasticEaseOut;
	anim.fromValue = 0;
	anim.toValue = 350;
	anim.duration = 30; // in frames	
	anim_running  = applyEffect(&anim); // animamos
	// animamos angulo
	anim2.property = &icon.angle;
	anim2.effectType = motion_effect.elasticEaseOut;
	anim2.fromValue = 45000;
	anim2.toValue = 0;
	anim2.duration = anim.duration; // in frames	
	anim2_running  = applyEffect(&anim2); // animamos
	
	from i=0 to 2;
		text[i] = write( stage_select_fnt , resolution_offset_x() + 160, 340 + (i*40),  4 , description[i]);
	end
	
	// esperamos que termine la animacion
	while (exists(anim_running)) 
		// anima fondo
		scroll[1].y0++;		
		scroll[1].x0++;
		frame; 
	end
	
	repeat 
		// anima fondo
		scroll[1].y0++;		
		scroll[1].x0++;
		frame; 
	until(mouse.left or control_(1,CONTROL_OK)) // Open Pandora: Button A
	
onexit:
	from i=0 to 2;
		delete_text(text[i]);
	end
	screen_clear();
	stop_scroll(1);
	mouse.left = false;
	signal( id , s_kill_tree );	
end

// how to play: shows only a single image until mouse click
process how_to_play()
private
	background_p;
	type_effect anim;
	int anim_running;
	int graphic;
begin
		
	z=-1000;
	
	how_to_play_shown = true;
	
	if (touchscreen())
		graphic = 70; // touch
	elseif(joy_number()>0)
		graphic = 72; // press button	
	else
		graphic = 71; // click
	end
	
	background_p = dummy_process(ui_fpg,graphic,resolution_offset_x() + (ANCHO_PANTALLA/2),ALTO_PANTALLA/2);
	
	
	// configuramos una animacion 
	anim.property = &background_p.size;
	anim.effectType = motion_effect.elasticEaseOut;
	anim.fromValue = 1;
	anim.toValue = 100;
	anim.duration=30;
	// animamos
	anim_running  = applyEffect(&anim);
	
	// esperamos que termine la animacion
	while (exists(anim_running))		
		frame;
	end
	
	
	repeat
		frame;
	until(mouse.left or control_(1,CONTROL_OK) or control_(1,CONTROL_CANCEL));
	
	onexit
	mouse.left = false;
	signal( id , s_kill_tree );	
end


// intro animation
process the_intro(stage)
private	
	type_effect anim;
	int anim_running;
	scroll_map;
	
	image_index = 66;
	sign;
	t,
begin
	
	autodetect_mode(ANCHO_INTERFAZ,ALTO_INTERFAZ,COLOR_DEPTH); frame; // cambia resolucion	
	
	switch (stage)
		case STAGE_COUNT - 1: // anim final del juego
			image_index = 39;
			intro_music = load_song("res/music/kastenfrosch_gewonnen2.ogg");
		end
		case 50: // intro a la nave		
			image_index = 37;
			intro_music = load_song("res/music/pizzicato_orchestral_roll.ogg");
		end
		case 25: // intro al templo
			image_index = 36;
			intro_music = load_song("res/music/pizzicato_orchestral_roll.ogg");
		end
		default: // intro primera pantalla
			image_index = 66;
			intro_music = load_song("res/music/pizzicato_orchestral_roll.ogg");
		end		
	end
	
	
	
	// creamos un scroll para la animacion con el dibujo que queremos mostrar
	scroll_map = map_new(map_info(0 ,0, G_WIDTH),map_info(ui_fpg , 38, G_HEIGHT),16);		
	
	drawing_color(rgb(1,1,1));
	drawing_map( 0 , scroll_map);
	draw_box (0,0,resolution_offset_x(),map_info(ui_fpg , 38, G_HEIGHT));
	draw_box (resolution_offset_x() + ANCHO_INTERFAZ,0,resolution_offset_x()*2 + ANCHO_INTERFAZ,map_info(ui_fpg , 38, G_HEIGHT));
	map_xputnp ( 0 , scroll_map , ui_fpg , 38 , map_info(0 ,0, G_WIDTH)/2 ,map_info(ui_fpg , 38, G_HEIGHT)/2 , 0 , 100 , 100 , 0 );		
	
	Start_scroll ( 1 , 0 , scroll_map, 0 , 0 , 15);
	SCROLL[1].x0 = 0;
	SCROLL[1].z = -100;
	
	set_center(ui_fpg , image_index,0,0);
	sign = dummy_process(ui_fpg , image_index ,0 ,0); // detalles para el full screen
	sign.z = 2;
	
	// configuramos una animacion 
	if (map_info(ui_fpg ,image_index,G_WIDTH) < map_info(ui_fpg ,image_index,G_HEIGHT))
		anim.property = &sign.y;		
		sign.x = resolution_offset_x();
		if (image_index == 37)
			anim.toValue = 0;
			anim.fromValue = - (map_info(ui_fpg ,image_index, G_HEIGHT) - ALTO_INTERFAZ);
		else
			anim.fromValue = 0;
			anim.toValue = - (map_info(ui_fpg ,image_index, G_HEIGHT) - ALTO_INTERFAZ);
		end
	else
		anim.property = &sign.x;
		anim.toValue =  resolution_offset_x() - map_info(ui_fpg ,image_index, G_WIDTH) + ANCHO_INTERFAZ;
		sign.x = resolution_offset_x();
		anim.fromValue = resolution_offset_x();
	end
	
	anim.effectType = motion_effect.strongEaseIn;
	
	if (stage == STAGE_COUNT - 1) // anim final del juego
	anim.duration = (25 * 4); // 4 seconds	
	else
	anim.duration = (25 * 7); // 7 seconds	
	end
	
	// musica
	if (music_on and sound_on)
		play_song ( intro_music , 0);
	end
	
	fade(100,100,100,10); // mostramos la pantalla	
	
	anim_running  = applyEffect(&anim);	// animamos
	
	// esperamos que termine la animacion
	while (exists(anim_running) or is_playing_song())
		SCROLL[1].y0 += 300;
		frame;
		if (mouse.left or control(1,CONTROL_OK)) // Open Pandora: Button A
			break;
		end
	end
	
	
	
	// despues q termino la animación esperamos a que se haga un click o que pase 2 segundos
	t = 200; 
    t += timer[0];
    While(timer[0]<t) 
		if (mouse.left or control(1,CONTROL_OK)) // Open Pandora: Button A
			break;
		end
		SCROLL[1].y0 += 300;
		frame; 
	End


	
onexit:
	
	stop_scroll(1);
	unload_map(0,scroll_map);
	
	
	mouse.left = false; // limpiamos el click
	if (music_on and sound_on)
		stop_song ();
		play_song ( game_music_1 , -1);
	end
	unload_song(intro_music);
	signal( id , s_kill_tree );	
end



process button(normal_graph,pressed_graph,x,y)
public 
	byte clicked = false; // public property to check if the button was pressed
	byte reverse_sound = false; // when true will play sound if the game is muted 
	byte focus = false;
private
	byte _button_pressed = false;	
	button item, previous_item;
	byte another_have_focus;
	byte assigned;
	byte assign_next;
	
begin
	file = ui_fpg;	
	z = father.z - 50;
	priority = father.priority; // will be executed before other processes.
	
	loop
		clicked = false;
	
		// si ningun boton en pantalla tiene foco nos asignamos el foco a nosotros mesmos
		if (!focus)
			another_have_focus = false;
			while (item = get_id(type button))
				if (item.focus == true)
					another_have_focus = true;
					break;
				end
			end
			if (!another_have_focus)
				focus = true;
				mouse.x = x;
				mouse.y = y;
			end
		end
		
		// si el dispositivo no es touchscreen dibujamos un efecto hover al boton con foco
		if (mouse.graph == 0 and !touchscreen())
			if (get_id(type hand_focus_effect) == 0)
				hand_focus_effect();
			end
		end
		
		// si se aprieta el boton con el mouse
		if (( (mouse_event(MOUSE_DOWN) and collision(type mouse)) or (focus and control(1,CONTROL_OK)) ) and !_button_pressed)
			_button_pressed = true;		
			
			
			// le choreamos el foco a los otros botones
			if (!focus)
			button_set_focus(id);
			end
		elseif (_button_pressed and ((mouse_event(MOUSE_UP) and !collision(type mouse)) or !focus))
			_button_pressed = false; // si se suelta el mouse afuera del boton se suelta el boton sin disparar evento click
		elseif (mouse_event(MOUSE_DRAG) or mouse_event(MOUSE_DROP))
			_button_pressed = false; // evitamos disparar click si el usuario esta arrastrando la pantalla		
		elseif (_button_pressed and ((mouse_event(MOUSE_UP) and collision(type mouse)) or (focus and control_(1,CONTROL_OK))))
			_button_pressed = false;			
			clicked = true;		
			
		elseif(focus) // navegacion por controles
			if (control_(1,CONTROL_DOWN) or control_(1,CONTROL_LEFT))
				assigned = false;
				focus = false;
				assign_next = false;
				while (item = get_id(type button))
					if (assign_next)
						button_set_focus(item);
						
						assigned = true;
						break;
					end					
					if (item == id)
						assign_next = true; // marcamos al proximo para que se asigne como en foco
					end
				end
				// si no se asigno a ninguno asignamos al primero de la lista
				if (!assigned)
					frame(0);
					item = get_id(type button);
					button_set_focus(item); 					
				end
				if (sound_on)
					play_wav(boton_click_wav,0); // sonido del boton apretandose
				end
			elseif (control_(1,CONTROL_UP) or control_(1,CONTROL_RIGHT))
				assigned = false;
				focus = false;
				previous_item = null;
				while (item = get_id(type button))
					if (item == id)						
						break;
					end
					previous_item = item;
				end
				
				if (previous_item == null)
					while (item = get_id(type button))
						previous_item = item;
					end
				end
				if (exists(previous_item))
					button_set_focus(previous_item);
					if (sound_on)
						play_wav(boton_click_wav,0); // sonido del boton apretandose
					end
				end
			end
		end
		
		// asigna grafico 
		if (!_button_pressed)
			graph = normal_graph;
		else
			graph = pressed_graph;
		end
		
		
		if (focus)
			size = 110;
		else
			size = 100;
		end
		
		// si se hizo click reproducimos sonido
		if (clicked)
			if (sound_on )
				if (!reverse_sound)
					play_wav(boton_click_wav,0); // sonido del boton apretandose
				end
			else
				if (reverse_sound)
					play_wav(boton_click_wav,0); // sonido del boton apretandose
				end
			end
		end
		
		frame;
	end
end

process hand_focus_effect()
private
	button item;
	inc = 1;
	val = 0;
	current_x,current_y;
begin
	file = ui_fpg;
	if (map_info(0,0,G_WIDTH)  <= 160)
		graph = 24;
	else		
		graph = 34;
	end
	loop
		item = null;
		
		while (item = get_id(type button))
			if (item.focus == true)
				if (current_x != item.x or current_y != item.y)
					current_x = item.x;
					current_y = item.y;
					
					x = item.x;
					z = item.z -1;
					ctype = item.ctype;
				
				end
				
				break;
			end
		end

		val += inc;
		if (val == 10)
		 inc = -1;
		elseif(val == 0)
			inc = 1;
		end
		y = current_y + val;
		
		frame;
	end
	onexit:
		signal( id , s_kill_tree );	
end

function button_set_focus(button button_id)
private
button item;
begin
	while (item = get_id(type button))
		item.focus = false;
	end			
	button_id.focus = true;	
end

function fade_in_slow()
begin
	fade(100,100,100,4); // Fade to normal
	while(fading) frame; end // Wait for the fading to finish
end

function fade_out_slow()
begin
	fade(0,0,0,4); // Fade to black
	while(fading) frame; end // Wait for the fading to finish
end

function anim_letter(letter_element,graph_number,letter_x,anim_sent)
begin
	/*letra*/
	letra_img[letter_element] = dummy_process(ui_start_fpg,graph_number,resolution_offset_x() + letter_x,-30);
	// configuramos una animacion 
	letra_effect[letter_element].property = &letra_img[letter_element].y;
	letra_effect[letter_element].effectType = anim_sent;
	letra_effect[letter_element].fromValue = -30;
	letra_effect[letter_element].toValue = 210;
	letra_effect[letter_element].duration = 40-(letter_element*2);
	return applyEffect(&letra_effect[letter_element]);
end

process pixelatom_sign()
private 
	i=0, j=0;
	anim_to_use[5];
	anim_proccess[8];
	anim_sent = 0;
begin
	fade_out_slow();
	map_clear(0,BACKGROUND,RGB(255,255,255));
	fade_in_slow();
	mouse.left = false;
	
	anim_to_use[0] = 2;
	anim_to_use[1] = 5;
	anim_to_use[2] = 6;
	anim_to_use[3] = 9;
	anim_to_use[4] = 15;
	
	rand_seed(time());
	anim_sent = anim_to_use[rand(0,4)];
	
	/*letra p*/
	anim_proccess[0]=anim_letter(0,36,71,anim_sent);
	/*letra i*/
	anim_proccess[1]=anim_letter(1,37,93,anim_sent);
	/*letra x*/
	anim_proccess[2]=anim_letter(2,38,110,anim_sent);
	/*letra e*/
	anim_proccess[3]=anim_letter(3,39,138,anim_sent);
	/*letra l*/
	anim_proccess[4]=anim_letter(4,40,157,anim_sent);
	/*letra a*/
	anim_proccess[5]=anim_letter(5,41,175,anim_sent);
	/*letra t*/
	anim_proccess[6]=anim_letter(6,42,195,anim_sent);
	/*letra o*/
	anim_proccess[7]=anim_letter(7,43,215,anim_sent);
	/*letra m*/
	anim_proccess[8]=anim_letter(8,44,245,anim_sent);
	
	repeat
		j++;
		frame;
	until(mouse.left or control_(1,CONTROL_OK) or j > 60); // Open Pandora: Button A
	
	
	mouse.left = false;
	fade_out_slow();
	for(i=0;i<=8;i++)
		signal( letra_img[i] , s_kill_tree );
		signal( anim_proccess[i] , s_kill_tree );
	end
	signal( id , s_kill_tree );	
	
	onexit
	
end

process bennu_sign()
private 
	j=0;
begin
	mouse.left = false;
		
	screen_clear();
	start_scroll(0,ui_start_fpg,1,0,0,0);

	dummy_process(ui_start_fpg,2,resolution_offset_x()+160,240);
	
	fade_in_slow();
	
	
	repeat
		j++;
		frame;
	until(mouse.left or control_(1,CONTROL_OK) or j > 60); // Open Pandora: Button A
	frame;
onexit:
	stop_scroll(0);
	mouse.left = false;
	screen_clear(); 
end

process stages_unblocked()
private
	background_p,credits_text;
	type_effect anim;
	int anim_running;
	int graphic;
begin
		
	z=-1000;
	
	if (touchscreen())
		graphic = 20; // touch
	elseif(joy_number()>0)
		graphic = 22; // press button
	else
		graphic = 21; // click
	end
	
	background_p = dummy_process(ui_fpg,graphic,resolution_offset_x() + (ANCHO_PANTALLA/2),ALTO_PANTALLA/2);
	
	
	// configuramos una animacion 
	anim.property = &background_p.size;
	anim.effectType = motion_effect.elasticEaseOut;
	anim.fromValue = 1;
	anim.toValue = 100;
	anim.duration=30;
	// animamos
	anim_running  = applyEffect(&anim);
	
	// esperamos que termine la animacion
	while (exists(anim_running))		
		frame;
	end
	
	
	repeat
		frame;
	until(mouse.left or control_(1,CONTROL_OK) or control_(1,CONTROL_CANCEL));
	
	onexit
	signal( id , s_kill_tree );	
	
end

process about_dialog()
private
	background_p,credits_text;
	type_effect anim;
	int anim_running;
begin
		
	z=-1000;
	
	priority = 1;
	
	background_p = dummy_process(ui_fpg,18,resolution_offset_x() + (ANCHO_INTERFAZ/2),ALTO_INTERFAZ/2);
	background_p.size = 250;
	
	//region_define ( 2 , 55 , 80 , ANCHO_INTERFAZ - 55, ALTO_INTERFAZ - 80 );
	
	credits_text = dummy_process(0,about_map, resolution_offset_x() + 55, 80);
	//credits_text.region = 2;
	//credits_text.z = -1002;
	
	// configuramos una animacion 
	anim.property = &background_p.size;
	anim.effectType = motion_effect.elasticEaseOut;
	anim.fromValue = 1;
	anim.toValue = 250;
	anim.duration=30;
	// animamos
	anim_running  = applyEffect(&anim);
	
	// esperamos que termine la animacion
	while (exists(anim_running))
		if (mouse.left)			
			mouse.left = false;			
		end 
		credits_text.size_y = background_p.size - 150;
		frame;
	end
	
	
	repeat
		if (mouse.left)			
			mouse.left = false;
			break;			
		end 
		frame;
	until(control_(1,CONTROL_OK) or control_(1,CONTROL_CANCEL)); // Open Pandora: Button A
	
	onexit
	signal( id , s_kill_tree );	
	
end

/**
 * pantalla de titulo
 */
process start_sign()
private 
	i=0;
	anim_to_use[5];
	anim_sent = 0;
	button start_button, sound_button, credits_button, exit_button, buy_button;
	credits_dialog;
	pbackground;
	type_effect anim;
	int anim_running;
	titulo;
begin
	fade_out_slow();
	screen_clear();
	
	game_intro_music = load_song("res/music/pol-coconut-land-short.ogg");
	
	// ubicamos fondo	
	center_set ( ui_fpg,12,0,0);
	pbackground = dummy_process(ui_fpg,12,0,0);
	pbackground.z = 512;	
	pbackground.size = (map_info(0,0,G_WIDTH) * 100) / map_info(ui_fpg,12,G_WIDTH);
	
	// arreglamos fondo para version mobile
	if (!resolution_offset_x()>0)
		pbackground.size = (map_info(0,0,G_HEIGHT) * 100) / map_info(ui_fpg,12,G_HEIGHT);
	end
	
	// ponemos el titulo
	titulo = dummy_process(ui_fpg,13,0,0);
	titulo.x = map_info(0,0,G_WIDTH) / 2;
	titulo.y = map_info(ui_fpg,13,G_HEIGHT)/2;
	titulo.z = 510;	
	titulo.size = ((map_info(0,0,G_HEIGHT) * 100) / map_info(ui_fpg,13,G_HEIGHT)) * 0.5;
	
	shadow(titulo,1,2);
	
	// configuramos una animacion 
	anim.property = &titulo.size;
	anim.effectType = motion_effect.elasticEaseOut;
	anim.fromValue = 1;
	anim.toValue = titulo.size;
	anim.duration=80;
	// animamos
	anim_running  = applyEffect(&anim);
	
	// ubicamos varios botones
	if (touchscreen())
		start_button = button(56,57,resolution_offset_x() + (320/3) - 50,330);
		sound_button = button(52,53,resolution_offset_x() + ((320/3) * 2) - 50,330);
		credits_button = button(50,51,resolution_offset_x() + ((320/3) * 3) - 50,330);
	else
		start_button = button(82,83,(map_info(0,0,G_WIDTH) / 2),260);
		if (is_demo())
			buy_button = button(41,42,(map_info(0,0,G_WIDTH) / 2),440);
		else
			exit_button = button(74,75,(map_info(0,0,G_WIDTH) / 2),440);
		end
		credits_button = button(76,77,(map_info(0,0,G_WIDTH) / 2),380);		
		sound_button = button(78,79,(map_info(0,0,G_WIDTH) / 2),320);		
	end
	
	sound_button.reverse_sound = true;
	if (!sound_on)
		if (touchscreen())
			sound_button.normal_graph=54;
			sound_button.pressed_graph=55;
		else
			sound_button.normal_graph=80;
			sound_button.pressed_graph=81;
		end
	end
	
	// musica
	if (music_on and sound_on)
		play_song ( game_intro_music , -1);
	end
	
	mouse.left = false;
	fade_in_slow();
	repeat
		
		if (exists(exit_button) and exit_button.clicked)
			exit(0,0);
		end
		
		if (is_demo())
			if (exists(buy_button) and buy_button.clicked)
				// compra
				buy_full_version();
				// salimos del loop porque queremos restartear
				break;
			end
		end
		// animamos fondo en version pantalla completa
		if (resolution_offset_x()>0)
			if (map_info( ui_fpg,12,G_HEIGHT)-map_info( 0,0,G_HEIGHT) > 0)
				if (pbackground.y > -(map_info( ui_fpg,12,G_HEIGHT)-map_info( 0,0,G_HEIGHT)))
					pbackground.y -- ;
				end
			end
		end
		
		 
		// accion del boton de la musica
		if (sound_button.clicked)
			if (!sound_on)
				sound_on=true;				
				resume_song();
				if(!is_playing_song())
					play_song ( game_intro_music , -1);
				end
				if (touchscreen())
					sound_button.normal_graph=52;
					sound_button.pressed_graph=53;
				else
					sound_button.normal_graph=78;
					sound_button.pressed_graph=79;
				end
			else				
				sound_on=false;
				pause_song();
				if (touchscreen())
					sound_button.normal_graph=54;
					sound_button.pressed_graph=55;
				else
					sound_button.normal_graph=80;
					sound_button.pressed_graph=81;
				end
			else
		end
		
		if (credits_button.clicked and !exists(credits_dialog))
			credits_dialog = about_dialog();
		end
	
		frame;
	until(start_button.clicked);
	
	
	
onexit:
	mouse.left = false;
	screen_clear(); 
	
	if (music_on and sound_on)
		stop_song ();		
	end
	unload_song(game_intro_music);
	signal( id , s_kill_tree );	
end




/**
 * seleccion de pantalla
 */

process stage_select_screen()
private
	int reference_point = 0;
	
	last_unbloqued;
	
	i,graphic = 0;
	button stage_select[STAGE_COUNT - 1];
	type_effect anim_stage;
	type_effect scroll_anim;
	new_map_id, new_text_map;
	current_effect;
	button return_button;
	
	scroll_to = 2000;
	
	scroll_map;
	
	last_move = 0;
	sign;
	dummy;
begin
	fade_out_slow();
	// inicializa la pantalla 
	autodetect_mode(ANCHO_INTERFAZ,ALTO_INTERFAZ,COLOR_DEPTH); frame; // cambia resolucion
	
	// carga el fpg de esta pantalla temporalmente
	file = load_fpg("res/fpg/stage_select.fpg");
	
	scroll_map =  map_new ( 10 , 2000 , 16);
	
	start_scroll ( 1 , file ,  10 ,0 , 0 , 15 ); // scroll superloco de fondo para pantalla completa
	scroll[1].z = 600;
	
	start_scroll ( 0 , 0 ,  scroll_map ,0 , 0 , 0 ); // ponemos imagen de fondo
	
	if (map_info(0,0,G_WIDTH) != 320 )
		sign = dummy_process(file,11,resolution_offset_x() + (ANCHO_INTERFAZ / 2),(ALTO_INTERFAZ / 2)); // detalles para el full screen
		sign.z = -1;
	end
	
	// creamos el mapa en este proceso para obtener los puntos de control que necesitamos
	graph = 1;
	ctype = c_scroll;
	cnumber = c_0;
	x = resolution_offset_x();
	y = 0;
	
	
	
	// reposicionamiento del scroll
	scroll[0].y0 = 2000;
	//scroll[0].x0 = resolution_offset_x();
	
	
	// posicionamos selectores de pantallas
	while (i <  sizeof(stages) / sizeof(stages[0]))
		
		// si la pantalla no esta desbloqueada no creamos el boton
		if (stage_points[i].status == 0) 
			
			dummy = dummy_process(file,12,0,0);
			get_real_point( i+1 , &dummy.x , &dummy.y );
			dummy.ctype = c_scroll;
			dummy.cnumber = c_0;
			//dummy.flags = 16;
			dummy.alpha = 50;
		else
	
			// define el grafico de fondo del selector
			graphic = 1 + stage_points[i].status;  // jugable con o sin puntos
			
			// ultima fila de cada mundo
			if ( (i<51 or i == STAGE_COUNT-1) and (((i  + 1 )% 25 == 0) or ((i  + 2 )% 25 == 0) or ((i  + 3 )% 25 == 0) or ((i  + 4 )% 25 == 0) or ((i  + 5 )% 25 == 0)))
				graphic = 5 + stage_points[i].status;  // jugable con o sin puntos
			end
			
			stage_select[i] = button(graphic,graphic, 0, 0);
			stage_select[i].file = file;
			stage_select[i].ctype = c_scroll;
			stage_select[i].cnumber = c_0;
			
			//cambiamos grafico por el que tiene el numero
			// creamos el grafico para este boton
			new_map_id =  map_clone ( file , graphic );
			
			new_text_map = write_in_map ( stage_select_fnt , i+1 , 0 ); // creamos grafico con el numero del stage
			// pegamos el numero en el grafico
			map_put ( 0 , new_map_id , new_text_map , 25 - (graphic_info (0, new_text_map , G_WIDTH )/2) , (graphic_info (0, new_text_map , G_HEIGHT)/2));
			unload_map(0,new_text_map);
					
			stage_select[i].file = 0;
			stage_select[i].graph = new_map_id;
			stage_select[i].pressed_graph = new_map_id;
			stage_select[i].normal_graph = new_map_id;	
			
			// ubicamos el boton
			get_real_point( i+1 , &stage_select[i].x , &stage_select[i].y );
			
			if (current_stage == 0 or  i == current_stage)
				scroll_to = stage_select[i].y;
			end
			
			last_unbloqued = i;
		end		
		// avanzamos a la siguiente pantalla 
		i++;
	end
	
	
	scroll_anim.property = &scroll[0].y0; 
	scroll_anim.effectType = motion_effect.regularEaseOut;
	scroll_anim.fromValue = 2000;
	scroll_anim.toValue = scroll_to - 240;
	scroll_anim.duration = (2000 - scroll_to) / 12 ;
	
	current_effect = applyEffect(&scroll_anim);
	
	
	frame;
	
	fade_in_slow();
	
	// esperamos que termine la animacion de scroll
	mouse.left = false;
	while (exists(current_effect))
		// arrastra durante anim
		if (mouse.left)
			signal(current_effect,s_kill_tree);
			mouse.left = 0;
		end 
		
		// cancela anim
		if (control_(1,CONTROL_UP) or control_(1,CONTROL_DOWN) 
		or control_(1,CONTROL_RIGHT) or control_(1,CONTROL_LEFT)
		or control_(1,CONTROL_CANCEL) or control_(1,CONTROL_OK))
			signal(current_effect,s_kill_tree);
			scroll[0].y0 = scroll_to - 240;
		end
		frame; 
		// animamos fondo
		scroll[1].x0++;
		scroll[1].y0--;
	end
	
	
	// creamos el boton de volver	
	if (touchscreen())
		return_button = button(48,49,270,435);
	end
	fade_in_slow(); // mostramos todo con un fade
	
	// asignamos foco al boton que tiene que ser
	if (current_stage>0)
		button_set_focus(stage_select[current_stage]);
	else
		button_set_focus(stage_select[last_unbloqued]);
	end
	
	loop
	
		// checkeamos el estado del click de todos los botones
		for (i=0;i<sizeof(stages) / sizeof(stages[0]);i++)
			if (exists(stage_select[i]) and stage_select[i].clicked)
				// si no esta bloqueado empezamos esta pantalla
				if (stage_points[i].status>0)
					current_stage = i; // seteamos pantalla actual					
					
					return;
				end
			end
		end
		
		// accion del boton para volver a los titulos
		if ((touchscreen() and return_button.clicked) or control_(1,CONTROL_CANCEL))
			exit_to_title = true;
			return;
		end
		
		// checkea si se esta moviendo con los controles para seguir al boton que tiene el foco
		if (control_(1,CONTROL_UP) or control_(1,CONTROL_DOWN) or control_(1,CONTROL_RIGHT) or control_(1,CONTROL_LEFT))
			for (i=0;i<sizeof(stages) / sizeof(stages[0]);i++)
				if (exists(stage_select[i]) and stage_select[i].focus)
					if (exists(current_effect))
						signal( current_effect , s_kill_tree );	
					end
					scroll_anim.property = &scroll[0].y0; 
					scroll_anim.effectType = motion_effect.regularEaseOut;
					scroll_anim.fromValue = scroll[0].y0;
					scroll_anim.toValue = stage_select[i].y - 240;
					scroll_anim.duration = 5;
					
					current_effect = applyEffect(&scroll_anim);
					
				end
			end
		end
	
		// scroll con lo dedo
		if (mouse.left)
			// paramos anim si se toca la pantalla
			if (exists(current_effect))
				signal( current_effect , s_kill_tree );	
			end
			if (reference_point == 0)
				reference_point = mouse.y;
			else
				last_move = (mouse.y - reference_point);
				scroll[0].y0 -= last_move;
				reference_point = mouse.y;
			end
		else
			// scrolleamos la pantalla con el dedo
			if (last_move!=0)
				scroll_anim.property = &scroll[0].y0; 
				scroll_anim.effectType = motion_effect.regularEaseOut;
				scroll_anim.fromValue = scroll[0].y0;
				scroll_anim.toValue = scroll[0].y0 - (last_move*2);
				scroll_anim.duration = 30;
				
				current_effect = applyEffect(&scroll_anim);
			end
			last_move = 0;
			reference_point = 0;
		end
		frame;
		// animamos fondo
		scroll[1].x0++;
		scroll[1].y0--;
	end
	
onexit:
	
	unload_map(0,scroll_map);
	
	// descargamos graficos creados para los selectores de pantallas
	while (i <  sizeof(stages) / sizeof(stages[0]))
		if (exists(stage_select[i]))
			map_unload(0, stage_select[i].normal_graph);
		end
		i++;
	end
	
	signal( id , s_kill_tree );	
	stop_scroll(1);
	stop_scroll(0);
	unload_fpg(file);
end 



// proceso utilizado para mostrar un grafico en pantalla
process dummy_process(file,graph,x,y)
begin
	z=father.z-1;
	loop
		frame;
	end
end

// palos de la hondera con la que se dispara el coco
process palos_process(file,graph,x,y)
begin
	z=father.z-1;
	loop
		get_real_point(0,&palos_izquierda_x,&palos_izquierda_y);
		get_real_point(1,&palos_derecha_x,&palos_derecha_y);
		frame;
	end
end

// dialogo que se muestra al ganar una pantalla
process sign_clear()
private
type_effect anim;
int anim_running;
button next_button, play_again_button, goto_menu_button;
banana_holder[2];
bananas[2];
byte bananas_counter = 4;
byte i,e; // indices para bucles
clear_word;
byte clear_word_anim[6] = 5, 6, 7, 8, 9, 10 , 11;
byte bananas_assigned = 0;
int playing_channel;
begin
	file = ui_fpg;
	graph = 18;
	x = resolution_offset_x() + (ANCHO_PANTALLA / 2);
	y = -80;
	z = -50;
	
	shadows(3,3); // le ponemos sombra al dialogo
	
	// configuramos una animacion 
	anim.property = &y;
	anim.effectType = motion_effect.elasticEaseOut;
	anim.fromValue = y;
	anim.toValue = 95;
	anim.duration=30;
	
	// creamos los botones la puta que lo pario
	next_button = button(14, 15,resolution_offset_x() + 83,142);
	
	goto_menu_button = button(1,2, resolution_offset_x() + 115,140);
	play_again_button = button(16,17, resolution_offset_x() + 50,141);
	
	
	
	// creamos los holders de las bananas
	banana_holder[0] = dummy_process(ui_fpg,3,resolution_offset_x() + 55,85);
	banana_holder[1] = dummy_process(ui_fpg,3,resolution_offset_x() + 83,85);
	banana_holder[2] = dummy_process(ui_fpg,3,resolution_offset_x() + 111,85);
	
	// animamos
	anim_running  = applyEffect(&anim);
	
	// esperamos que termine la animacion
	while (exists(anim_running))
		next_button.y = y + 47;
		play_again_button.y = y + 46;
		goto_menu_button.y = y + 45;
		
		banana_holder[0].y = y - 10;
		banana_holder[1].y = y - 10;
		banana_holder[2].y = y - 10;
		
		// ya permitimos hacer las acciones de los botones mientras se ejecuta la anim
		// si cerramos el cartel el curso normal es seguir en la siguiente pantalla
		if (next_button.clicked)
			introshown = false;
			return; // dejamos todo como esta..
		end
		if (play_again_button.clicked)
			next_stage = current_stage;
			return; 
		end
		if (goto_menu_button.clicked or control_(1,CONTROL_CANCEL))
			exit_to_menu = true;
			return; // si cerramos el cartel el curso normal es seguir en la siguiente pantalla
		end
		
		frame;
	end
	// sonido de la victoria!
	
	if (sound_on)
		playing_channel = play_wav(mono_win_wav,0);
	end
	// cartelito CLEAR!
	clear_word = dummy_process(file,clear_word_anim[0],resolution_offset_x() + 79,47);
		
	bananas_assigned = bananas_counter-balls_used;
	
	//speed_used
	// crea las bananas	
	for (i=0;i<bananas_assigned;i++)
		
		switch (i)
			case 0: 
				bananas[i] = dummy_process(ui_fpg,4,resolution_offset_x() + 55,85);
			end
			case 1: 
				bananas[i] = dummy_process(ui_fpg,4,resolution_offset_x() + 83,85);
			end
			case 2: 
				bananas[i] = dummy_process(ui_fpg,4,resolution_offset_x() + 111,85);
			end
		end
		bananas[i].size = 0;
		bananas[i].z = banana_holder[i].z-1;
	end
	
	
	// configura animacion de la bananas
	anim.effectType = motion_effect.elasticEaseOut;
	anim.fromValue = 0;
	anim.toValue = 100;
	anim.duration=15;
	
	i = 0;
	e = 0;
	
	loop
	
		if (e<(sizeof(clear_word_anim)/sizeof(clear_word_anim[0])) - 1)
			e++;		
		end
		clear_word.graph = clear_word_anim[e];
	
		if (i<bananas_assigned and !exists(anim_running))
			anim.property = &bananas[i].size;
			anim_running  = applyEffect(&anim);		
			i++;
		end
		
		// si cerramos el cartel el curso normal es seguir en la siguiente pantalla
		if (next_button.clicked)
			return; // dejamos todo como esta..
		end
		if (play_again_button.clicked)
			next_stage = current_stage;
			return; 
		end
		if (goto_menu_button.clicked or control_(1,CONTROL_CANCEL))
			exit_to_menu = true;
			return; // si cerramos el cartel el curso normal es seguir en la siguiente pantalla
		end
		
		frame;
	end
onexit
	if (sound_on)
		stop_wav(playing_channel);
	end
	signal( id , s_kill_tree );
end

process sign_fail()
private
type_effect anim;
int anim_running;
button  play_again_button, goto_menu_button;
fail_word;
begin
	file = ui_fpg;
	graph = 28;
	x = resolution_offset_x() + (ANCHO_PANTALLA / 2);
	y = -80;
	z = -50;
	shadows(3,3);
	// configuramos una animacion 
	anim.property = &y;
	anim.effectType = motion_effect.elasticEaseOut;
	anim.fromValue = y;
	anim.toValue = 95; // hasta donde tiene que ir el cartel
	anim.duration=25;
	
	// creamos los botones la puta que lo pario
	play_again_button = button(16,17, resolution_offset_x() + 65,101);
	goto_menu_button = button(1,2, resolution_offset_x() + 98,100);
	
	// cartelito FAIL!
	fail_word = dummy_process(file,19,resolution_offset_x() + 83,81);
		
	// animamos
	anim_running  = applyEffect(&anim);
	
	loop
	
		play_again_button.y = y + 15;
		goto_menu_button.y = y + 15;
		fail_word.y = y - 14;
		
		if (play_again_button.clicked)			
			return; 
		end
		if (goto_menu_button.clicked or control_(1,CONTROL_CANCEL))
			exit_to_menu = true;
			return; // si cerramos el cartel el curso normal es seguir en la siguiente pantalla
		end
		
		frame;
	end
onexit
	signal( id , s_kill_tree );
end


process pause()
private
type_effect anim;
int anim_running;
button  continue_button, play_again_button, goto_menu_button;

begin
	// pausamos el juego
	signal(ALL_PROCESS,S_FREEZE);
	
	file = ui_fpg;
	graph = 28;
	x = resolution_offset_x() + (ANCHO_PANTALLA / 2);
	y = -80;
	z = -50;
	shadows(3,3);
	// configuramos una animacion 
	anim.property = &y;
	anim.effectType = motion_effect.elasticEaseOut;
	anim.fromValue = y;
	anim.toValue = 95; // hasta donde tiene que ir el cartel
	anim.duration=25;
	
	// creamos los botones la puta que lo pario
	play_again_button = button(31,32, resolution_offset_x() + 81,96);
	
	continue_button = button(25,26, resolution_offset_x() + 81,76);
	goto_menu_button = button(29,30, resolution_offset_x() + 81,117);	
	
	// animamos
	anim_running  = applyEffect(&anim);
		
	
	loop
	
		continue_button.y = y - 19;
		play_again_button.y = y + 1;	
		goto_menu_button.y = y +  22;
		
		if (continue_button.clicked)			
			return; 
		end
		
		if (play_again_button.clicked)			
			restart_stage = true;
			return; 
		end
		if (goto_menu_button.clicked or control_(1,CONTROL_CANCEL))
			exit_to_menu = true;
			return; // si cerramos el cartel el curso normal es seguir en la siguiente pantalla
		end
		
		frame;
	end
onexit	
	signal(ALL_PROCESS,S_WAKEUP);
	signal( id , s_kill_tree );
end
