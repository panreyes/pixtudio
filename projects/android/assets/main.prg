import "mod_time"
import "mod_grproc"
import "mod_key"
import "mod_say"
import "mod_scroll"
import "mod_proc"
import "mod_rand"
import "mod_math"
import "mod_timers"
import "mod_sort"
import "mod_text"
import "mod_file"
import "mod_screen"
import "mod_draw"
import "mod_video"
import "mod_sound"
import "mod_mouse"
import "mod_map"
import "mod_wm"
//import "mod_debug"
import "mod_multi" // NO COMENTEN ESTO; INSTALEN LOS MODULOS VAGOS DE MIERDA, despues las cosas andan mal en los otros OS y no sabemos porque
import "mod_iap" // NO COMENTEN ESTO; INSTALEN LOS MODULOS VAGOS DE MIERDA
import "mod_dir"
import "mod_sys"



include "includes/credits.inc"


const
	ALTO_PANTALLA = 240;
	ANCHO_PANTALLA = 160;
	
	ALTO_INTERFAZ = 480;
	ANCHO_INTERFAZ = 320;
	
	COLOR_DEPTH = 16;
end
global
	
	// configuraciones 
	music_on = true;
	sound_on = true;
	
	// flags globales 
	exit_to_menu; // flag que indica que al terminar una pantalla debe retornar al menu principal
	exit_to_title; // flag que indica que al salir del menu debe retornar a la pantalla de titulos
	restart_game = false; // esto comienza el loop principal de vuelta. como para reiniciar lo juego
	
	restart_stage; // otro flag con un proposito muy parecido
	byte introshown = false;
	byte how_to_play_shown = false;

	// punteros a fpg's
	ui_fpg = false;
	ui_start_fpg = false;
	cocofpg=0;
	enemies_fpg;
	stage_fpg ;
	t_fpg ;
	effects_fpg;
	fader;
	monkey_fpg;
	boss_fpg;
	
	// punteros a fuentes
	//plus_points_fnt; // fuente usada para mostrar puntos en pantalla durante el juego - 16px
	//minus_points_fnt; // fuente usada para mostrar puntos en pantalla durante el juego - 16px
	stage_select_fnt; // fuente usada en los selectores de pantalla
	
	// punteros a sonidos
	disparo_wav;
	coco_roto_wav;
	golpe_robot_wav;
	explosion_wav;
	golpe_pared_wav;
	boton_click_wav;
	mono_win_wav;
	pinball_wav;
	ball8_wav;
	
	// punteros a la musica
	game_music_1;
	game_music_2;
	game_music_3;
	game_music_4;
	intro_music;
	game_intro_music;
	music_playing=0;
	
	// variables del juego
	byte next_stage = 0; 
	byte current_stage = 0; // setea la pantalla actual
	byte speed_used = 0; // usado para darle puntaje al final del stage
	byte balls_used = 0; // contador de cuantas pelotas va usando en una pantalla
	
	int ballesta;
	int palos;
	int palos_izquierda_x, palos_derecha_x, palos_izquierda_y, palos_derecha_y;

	string savefilepath = "score.sav"; //IOS path
end
local
	int energy = 1; // the enemy energy
end

// codigo reutilizable para otros juegos
include "libraries/motion_tween.inc"
include "libraries/mouse_events.inc"
include "libraries/controls.inc"


// configuracion de controles
include "includes/controls.inc"
// codigo propio del juego
include "includes/effects.inc"
// definicion de las pantallas jugables y todo el codigo referido a ellas.
include "includes/stages.inc"
// aca estan programados todos los procesos de los bloques que se deben romper, y todo lo relacionado a ellos.
include "includes/blocks.inc"
// aca el proceso bola y su logica, ademas, la linea punteada y la logica del disparo.
include "includes/ball.inc"
// el mono
include "includes/monkey.inc"
// elementos de la interfz (menues, carteles, etc)
include "includes/ui.inc"
// logica principal del juego
include "includes/the_game.inc"
// codigo referido a las diferentes plataformas donde corre el juego
include "includes/platforms.inc"
// proceso que controla los keys para cambiar la config de pantalla
include "includes/screen.inc"
// code with the function to know if we're on demo mode
include "includes/demo.inc" 



/* proceso principal del juego, seteo de configuraciones, etc */
process Main()
private	
	int current_game;
	int i;
	int linemap;
	
	byte how_to_play_shown = false;
	string new_feature_description[2];
	int dsx, dsy;
	string platform;
	byte animar = false;
begin
	
	set_fps(30,0);

	// configuracion segun plataforma
	switch(os_id)
		case OS_IOS:	// iphone
            sound_freq = 22050;
			//dsx = graphic_info(0, 0, G_WIDTH);
			//dsy = graphic_info(0, 0, G_HEIGHT);
			// resolucion del iphone.
			//scale_resolution = dsx * 10000 + dsy ;
			//scale_resolution_aspectratio = SRA_PRESERVE;
			
			savefilepath = cd()+"/../Library/Preferences/mvr_score.sav"; // Absolute path
			platform = "IOS";
		end
		case 1003: //android
			
			if(iap_isouya() == 1)
				iap_init("1952f3ca-cd04-4108-ac17-39d095426d49");
			end
			
			// detecta resolucion del dispositivo
			dsx = graphic_info(0, 0, G_WIDTH);
			dsy = graphic_info(0, 0, G_HEIGHT);
			scale_resolution = dsx * 10000 + dsy ;
			scale_resolution_aspectratio = SRA_PRESERVE;
			full_screen = true;
			
			savefilepath = "/data/data/com.pixelatom.monkeyvsrobotsfull/mvr_score.sav";
			platform = "Android";
		end
		case 1010: // Open Pandora
			scale_resolution = 03200480;
			full_screen = true;			
			platform = "OpenPandora";
			savefilepath = "score.sav";
		end
        case OS_MACOS:
			dsx = graphic_info(0, 0, G_WIDTH);
			dsy = graphic_info(0, 0, G_HEIGHT);
			scale_resolution = dsx * 10000 + dsy ;
			scale_resolution_aspectratio = SRA_PRESERVE;
			platform = "PC";
			savefilepath = getenv("HOME")+"/Library/Preferences/monkeyvsrobots/mvr_score.sav";
            full_screen = true;
        end
		default:
			scale_resolution = 03200480;			
			platform = "PC";
			savefilepath = "monkey_vs_robots.sav";
			full_screen = true;
		end
	end
	
	// setea la pantalla
	autodetect_mode(ANCHO_INTERFAZ,ALTO_INTERFAZ,COLOR_DEPTH);
	
	frame;
	write(0,resolution_offset_x()+(ANCHO_INTERFAZ/2),resolution_offset_y()+(ALTO_INTERFAZ/2),4,"Loading... "/*+ platform*/);
	frame;
	
	// cargamos los graficos
	ui_fpg = load_fpg('res/fpg/ui.fpg');
	ui_start_fpg = load_fpg('res/fpg/uistart.fpg');
	cocofpg = load_fpg('res/fpg/coco.fpg');
	stage_fpg = load_fpg("res/fpg/stage1.fpg");
	enemies_fpg = load_fpg("res/fpg/enemies.fpg");
	t_fpg = load_fpg("res/fpg/trinchera.fpg");
	effects_fpg = load_fpg("res/fpg/effects.fpg");
	monkey_fpg = load_fpg("res/fpg/monkey.fpg");
	boss_fpg = load_fpg("res/fpg/boss.fpg");
	
	// cargamos las fuentes
	//plus_points_fnt = load_fnt("res/fnt/plus_points.fnt");
	//minus_points_fnt = load_fnt("res/fnt/minus_points.fnt");
	stage_select_fnt = load_fnt("res/fnt/cool_dog.fnt");
	
	// cargamos sonidos
	disparo_wav = load_wav("res/wav/swosh.wav");
	pinball_wav = load_wav("res/wav/pinball.wav");
	ball8_wav = load_wav("res/wav/bola8.wav");
	coco_roto_wav = load_wav("res/wav/wood-breaking.wav");
	golpe_robot_wav = load_wav("res/wav/quintoro2.wav");
	golpe_pared_wav = load_wav("res/wav/ball-hit.wav");
	explosion_wav = load_wav("res/wav/explosion.wav");
	boton_click_wav = load_wav("res/wav/klack1.wav");
	mono_win_wav = load_wav("res/wav/fanfare.wav");
	
	// cargamos la musica
	
	
	
	
	// mostramos u ocultamos el mouse dependiendo de si contamos con pantalla tactil
	mouse.z = -2000;
	if(touchscreen() or joy_number()>0)
		mouse.file = 0;
		mouse.graph = 0;
	else
		mouse.file = ui_fpg;
		mouse.graph = 34;
	end
	
	mouse_events_init(); // checkeos de eventos del mouse
	configurecontrols(); // configura controles 
	
	if (stage_points[0].status == 0)
		stage_points[0].status = 1; // desbloqueamos la primera pantalla por las dudas
	end	
	
	// cargamos avance guardado	
	if (fexists(savefilepath))
		load(savefilepath,stage_points); // guardamos el avance
	else
		save(savefilepath,stage_points); // guardamos un score en blanco
	end
	
	// creamos el mapa de los creditos
	about_map = new_map(ANCHO_INTERFAZ,ALTO_INTERFAZ,16);
	center_set (0,about_map,0,0);
	From i=0 To ABOUT_LINES;
		linemap = write_in_map ( 0 , about_text[i] , 0);
		map_put ( 0 , about_map , linemap , 0 , i*10 );
		unload_map(0,linemap);
  	End
	
	
	delete_text(ALL_TEXT);
	frame;
	
	// llamamos el proceso que checkea el switch a full screen
	//screen_configcontrol_();
	
	// Pantalla "pixelatom"
	current_game = pixelatom_sign();
	repeat
		if (exit_status) 
			exit();  // cierra app
		end 
		frame; 
	until(!exists(current_game));

	// Pantalla "Made with Bennu"
	current_game = bennu_sign();
	repeat 
		if (exit_status) 
			exit();  // cierra app
		end 
		frame; 
	until(!exists(current_game));
	
	//descargamos la uistart
	fpg_del(ui_start_fpg);

	// controlador de foco de la aplicacion	
	pause_on_background();
	
	current_stage = 0;
	next_stage = 0;

	loop // section: title
		current_game = start_sign();
		repeat
			if (exit_status) 
				exit();  // cierra app
			end 
			if (control_(1,CONTROL_CANCEL) and joy_number()==0)
				exit();  // cierra app
			end
			frame;
		until(!exists(current_game));
		
		if (restart_game)
			restart_game = false;
			continue;
		end
		
		repeat // section: menu
			exit_to_menu = false; 
			exit_to_title = false;
			introshown = false;
		
			if (music_on and sound_on)
				game_music_2 = load_song("res/music/tafi_maradi_no_voice_lr.ogg");
				play_song ( game_music_2 , -1);
				music_playing = 2;
			end
			// main menu			
			current_game = stage_select_screen();
			repeat
				if (exit_status) 
					exit();  // cierra app
				end
				frame;
			until(!exists(current_game))
			
			animar = false; // evitamos ejecutar transicion a menos que pasemos de una pantalla directamente a otra
			
			
			// start game
			while(!exit_to_menu and !exit_to_title) // este while va avanzando de pantalla
				// si el estado de esta variable cambia durante el juego en el proximo loop sale al menu
				exit_to_menu = false; 
				
				// antes de empezar el juego checkeamos si estamos en la demo y salimos
				if (current_stage>19 and is_demo())
					current_game = demo_over();
					repeat frame; until(!exists(current_game))
					exit_to_menu = true;
					break;
				end
				
				switch (current_stage)
					
					case 5: //pantalla 5
						if (!introshown)
							new_feature_description[0] = "A harder coconut!";
							new_feature_description[1] = "It can bounce once";
							new_feature_description[2] = "on the walls!";
							current_game = new_feature(cocofpg, 11, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							introshown = true;
						end
					end
					
					case 6: //pantalla 6
						if (!introshown)
							new_feature_description[0] = "A harder robot!";
							new_feature_description[1] = "you need 2 hits";
							new_feature_description[2] = "to take it down";
							current_game = new_feature(enemies_fpg, 9, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							introshown = true;
						end
					end
					
					case 9: //pantalla 9
						if (!introshown)
							new_feature_description[0] = "The hardest coconut!";
							new_feature_description[1] = "It can bounce twice";
							new_feature_description[2] = "on walls!";
							current_game = new_feature(cocofpg, 1, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							introshown = true;
						end
					end
					
					case 10: //pantalla 10
						if (!introshown)
							new_feature_description[0] = "Moving robots?";
							new_feature_description[1] = "This is getting";
							new_feature_description[2] = "interesting";
							current_game = new_feature(enemies_fpg, 48, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							introshown = true;
						end
					end
					
					case 15: //pantalla 15
						if (!introshown)
							new_feature_description[0] = "Stealthy robots!";
							new_feature_description[1] = "Please spread";
							new_feature_description[2] = "this message!";
							current_game = new_feature(enemies_fpg, 56, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							introshown = true;
						end
					end
					case 30: //pantalla 30
						if (!introshown)
							new_feature_description[0] = "Bowling ball";
							new_feature_description[1] = "don't bounce on robots";
							new_feature_description[2] = "it just pass through";
							current_game = new_feature(cocofpg, 27, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							introshown = true;
						end
					end
					case 31: //pantalla 31
						if (!introshown)
							new_feature_description[0] = "Oh oh! Robot Saw";
							new_feature_description[1] = "it breakes everything";
							new_feature_description[2] = "Even bowling ball";
							current_game = new_feature(enemies_fpg, 81, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							introshown = true;
						end
					end
					
					case 36: //pantalla 36
						if (!introshown)
							new_feature_description[0] = "What?! A spiderbot?!";
							new_feature_description[1] = "Just what I needed";
							new_feature_description[2] = "I hate spiders";
							current_game = new_feature(enemies_fpg, 73, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							introshown = true;
						end
					end
					case 37: //pantalla 37
						if (!introshown)
							new_feature_description[0] = "A pinball ball!";
							new_feature_description[1] = "That'll be fun";
							new_feature_description[2] = "Hope won't tilt";
							current_game = new_feature(cocofpg, 35, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							introshown = true;
						end
					end
					case 40: //pantalla 40
						if (!introshown)
							new_feature_description[0] = "Looks like a bomb!";
							new_feature_description[1] = "I must use it";
							new_feature_description[2] = "against them";
							current_game = new_feature(enemies_fpg, 91, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							introshown = true;
						end
					end
					case 49: //pantalla 49
						if (!introshown)
							new_feature_description[0] = "YAY! a bowling ball!";
							new_feature_description[1] = "don't bounce on robots";
							new_feature_description[2] = "it pass through";
							current_game = new_feature(cocofpg, 27, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							introshown = true;
						end
					end
					case 50: //pantalla 50
						if (!introshown)							
							current_game = the_intro(current_stage);
							introshown = true;
							repeat						
								frame;			
							until(!exists(current_game))										
						
					
							new_feature_description[0] = "ALMOST invencible!";
							new_feature_description[1] = "Only dies if you hit it ";
							new_feature_description[2] = "right on the eye";
							current_game = new_feature(enemies_fpg, 105, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							introshown = true;
						end
					end
					case 53: //pantalla 53
						if (!introshown)
							new_feature_description[0] = "Another type of saw?!";
							new_feature_description[1] = "These guys must";
							new_feature_description[2] = "love saws...";
							current_game = new_feature(enemies_fpg, 117, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							introshown = true;
						end
					end
					case 54: //pantalla 54
						if (!introshown)
							new_feature_description[0] = "Yeah! A ball 8!";
							new_feature_description[1] = "Time to cannon pool!";
							new_feature_description[2] = "watch rebound angle";
							current_game = new_feature(cocofpg, 34, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							introshown = true;
						end
					end
					case 59: //pantalla 59
						if (!introshown)
							new_feature_description[0] = "A coconut bomb!";
							new_feature_description[1] = "It explodes when";
							new_feature_description[2] = "it breaks. Eat This!";
							current_game = new_feature(cocofpg, 36, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							introshown = true;
						end
					end
					case 68: //pantalla 68
						if (!introshown)
							new_feature_description[0] = "Oh no! A prism bot!";
							new_feature_description[1] = "It changes the path";
							new_feature_description[2] = "of the coconut";
							current_game = new_feature(enemies_fpg, 129, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							introshown = true;
						end
					end
					case 72: //pantalla 72
						if (!introshown)
							new_feature_description[0] = "A smoker?!";
							new_feature_description[1] = "You just can't smoke";
							new_feature_description[2] = "in a national park!";
							current_game = new_feature(enemies_fpg, 134, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							introshown = true;
						end
					end
					case 0:
						if (!introshown)							
							current_game = the_intro(current_stage);
							introshown = true;
							repeat						
								frame;			
							until(!exists(current_game))
							animar=false;
						end
					end
					case 25:
						if (!introshown)							
							current_game = the_intro(current_stage);
							introshown = true;
							repeat						
								frame;			
							until(!exists(current_game))
							
							animar=false;
							
							new_feature_description[0] = "Shooting Bots!";
							new_feature_description[1] = "Be careful! they can";
							new_feature_description[2] = "break your coconut";
							current_game = new_feature(enemies_fpg, 69, &new_feature_description);
							repeat frame; until(!exists(current_game))
							animar=false;
							
						end
					end					
				end
				
				// pone la musica del juego
				if (music_on and sound_on)
					//si es una de las primeras pantallas hasta la 25 incluida (arranca de 0)
					if(current_stage <25)
						//descargo cualquiera de las músicas pre-cargadas
						if(music_playing!=1)
							fade_music_off ( 1);
							if(music_playing == 4)
								unload_song(game_music_4);
							elseif(music_playing==3)
								unload_song(game_music_3);
							elseif(music_playing==2)
								unload_song(game_music_2);
							elseif(music_playing==1)
								unload_song(game_music_1);
							end	
							//cargo y reproduzco la musica que va en estas pantallas
							game_music_1 = load_song("res/music/hackbeat_low.ogg");						
							play_song ( game_music_1 , -1); // musica del juego
							music_playing = 1;
						end
					elseif(current_stage >24 && current_stage < 50)
						//descargo cualquiera de las músicas pre-cargadas
						if(music_playing!=4)
							fade_music_off ( 1);
							if(music_playing == 4)
								unload_song(game_music_4);
							elseif(music_playing==3)
								unload_song(game_music_3);
							elseif(music_playing==2)
								unload_song(game_music_2);
							elseif(music_playing==1)
								unload_song(game_music_1);
							end						
							game_music_4 = load_song("res/music/chee_zee_jungle_loop.ogg");						
							play_song ( game_music_4 , -1); // musica del juego
							music_playing = 4;
						end
					elseif(current_stage > 49)
							
						//descargo cualquiera de las músicas pre-cargadas
						if(music_playing!=3)
							fade_music_off ( 1);
							if(music_playing == 4)
								unload_song(game_music_4);
							elseif(music_playing==3)
								unload_song(game_music_3);
							elseif(music_playing==2)
								unload_song(game_music_2);
							elseif(music_playing==1)
								unload_song(game_music_1);
							end
							game_music_3 = load_song("res/music/2013_07_cut_01_slow_lr.ogg");
							play_song ( game_music_3 , -1); // musica del juego
							music_playing = 3;
						end
					end
				end
				
				next_stage = current_stage;
				
				if (animar)
					transicion(1); // muy lento en iphone
				end
				
				// empieza el juego
				current_game = the_game();	 // juega una pantalla				
				repeat
					if (exit_status) 
						exit();  // cierra app
					end 
					frame;			
				until(!exists(current_game))			
				
				
				animar=true;
				
				//checkea por acciones que se deben ejecutar cuando se pasa de pantalla
				if (!exit_to_menu and !exit_to_title and (current_stage<next_stage)) 					
					switch (current_stage)					
						case STAGE_COUNT - 1:
							if (next_stage == STAGE_COUNT) // si pasamos la ultima pantalla								
								fade_in_slow();
								current_game = the_intro(current_stage);								
								repeat frame; until(!exists(current_game))								
								next_stage = current_stage = 0;
								exit_to_menu = true; // sale al menu								
							end
						end						
					end
				end
				
				// si la proxima pantalla no esta desbloqueada salimos al mapa
				if (stage_points[next_stage].status == 0)
					exit_to_menu = true; // sale al menu					
				else				
					current_stage = next_stage; // avanzamos a la proxima pantalla
				end
			end // sale del juego
			
			if (music_on and sound_on)
				// para la musica del juego
				stop_song();
			end
		until(exit_to_title);
	end
end
