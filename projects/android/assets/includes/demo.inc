const
	ouya_product_code = "mvr-fullgame";
end

global
	demo_mode = -1;
end

function buy_full_version()
private
	int purchase_status=-2;
begin
	if(iap_isouya())
		if(iap_purchased(ouya_product_code))
			// You've already purchased the full version of the game
			demo_mode = false;
		else
			// matamos el manager de segundo plano
			signal( type pause_on_background, s_kill_tree );
            frame(0);
			
			// You haven't yet purchased the full version of the game, starting purchase
			iap_purchase(ouya_product_code, &purchase_status);
			while (purchase_status < 0)
				frame;
			end
			demo_mode = -1;
			
			// restarteamos el manager de segundo plano
			pause_on_background();
		end
	end
	// restarteamos el juego
	restart_game = true;	
end

function is_demo()
begin
	
	if (demo_mode == -1)
		if(iap_isouya())
			// en OUYA chequeamos por la ODK si se hizo el pago
			demo_mode = true;
			
			while (!iap_receipts_ready()) // esperamos que termine la comprobacion
				frame;
			end
			
			if(iap_purchased(ouya_product_code))
				// You've already purchased the full version of the game
				demo_mode = false;			
			end
			
		else
			// por compilador
			#ifdef DEMO
				demo_mode = true;
			#else
				demo_mode = false;
			#endif
		end
	end
	
	return demo_mode;
end

process demo_over()
begin	
	autodetect_mode(ANCHO_INTERFAZ,ALTO_INTERFAZ,COLOR_DEPTH); frame; // cambia resolucion
	screen_clear();
	if (music_on and sound_on)
		stop_song ();
	end
	intro_music = load_song("res/music/kastenfrosch_gewonnen2.ogg");
	// musica
	if (music_on and sound_on)
		play_song ( intro_music , 0);
	end
	
	// mostramos fondo	
	if(iap_isouya())
		screen_put ( ui_fpg , 43 );
	else
		screen_put ( ui_fpg , 40 );
	end
	
	repeat 		
		frame; 
	until(mouse.left or control_(1,CONTROL_OK)) // Open Pandora: Button A
	
onexit:	
	exit_to_title = true;
	screen_clear();	
	mouse.left = false;
	if (music_on and sound_on)
		stop_song ();
		play_song ( game_music_1 , -1);
	end
	unload_song(intro_music);
	signal( id , s_kill_tree );	
end
