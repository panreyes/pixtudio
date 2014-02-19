
// pauses the game when it losts the focus
process pause_on_background()
begin
	loop
		if (!focus_status)
			if(os_id == 1003 and joy_number()>0) 
				exit(); // para que se salga en ouya
			end
			_pause_on_background();
		end
		frame;
	end
end

function _pause_on_background()
private
	restore_full_scren = false;
begin
	//desvanecemos la música
	pause_song();
	
	//ahorramos cpu bajando los fps
	set_fps(1,0);
	
	// pausamos el juego
	signal(ALL_PROCESS,S_FREEZE);
	
	// en pc si sacamos el foco debemos restaurar la ventana para devolver el mouse al OS
	if (full_screen)
		restore_full_scren = true;
		set_mode(map_info(0,0,G_WIDTH),map_info(0,0,G_HEIGHT),16);
	end
	
	//mientras no se recupere el foco
	while(!focus_status) 
		frame;
	end
	
	if (restore_full_scren)
		full_screen = true;
		set_mode(map_info(0,0,G_WIDTH),map_info(0,0,G_HEIGHT),16);
	end
	
	// reanudamos el juego	
	signal(ALL_PROCESS,S_WAKEUP);

	//reponemos la música
	resume_song();


	//volvemos a colocar las fps originales
	set_fps(30,0);
end

function touchscreen()
begin	
	if (joy_number() > 0) return false; end // changes behavior if joy pressent
	return (os_id == 1003 OR os_id == OS_IOS);
end