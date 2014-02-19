import "mod_key"; 
import "mod_joy"; 
import "mod_mem"; 

type control_s_buttonmap
	int control = 0; // the control action we want to check
	int player = 0; // the player number (when multiplayer)
	int value = 0; // the key id in the device (keyboard key, joy button, etc)	
	int device_id = -1; // when more than one device conected (joysticks)
	int axisnumber = -1; // when joystick
	int hatnumber = -1; // when joystick
end

global
// controls_defaultjoymap[5] = 9,8,JOY_HAT_LEFT,JOY_HAT_RIGHT,JOY_HAT_UP,JOY_HAT_DOWN;
int controls_mappings_keyboard_count = 0;
control_s_buttonmap pointer controls_mappings_keyboard; // list of mapped buttons to the keyboard
int controls_mappings_joystick_count = 0;
control_s_buttonmap pointer controls_mappings_joystick; // list of mapped buttons to the joysticks
end

/**
 * Maps a keyboard scancode to a game control action.
 */
function controls_map_keyboard(int control,int player, int scancode)
private
int i;
control_s_buttonmap pointer mappedcontrol_;
int _size = 0;
begin
	// calcular el tamaño nuevo del puntero.
	if ((controls_mappings_keyboard) == NULL)
		_size = sizeof(control_s_buttonmap);
	else
		
		// buscar que no exista already
		for (i = 0; i < controls_mappings_keyboard_count;i++) 
			mappedcontrol_ = controls_mappings_keyboard[i];
			if (mappedcontrol_.control == control and 
				mappedcontrol_.player == player and 
				mappedcontrol_.value == scancode)			
				
				return; // duplicated
			end
		end		
		// calcula el nuevo tamaño
		_size = (controls_mappings_keyboard_count+1) *  sizeof(control_s_buttonmap);
	end
	
	// redimencionar tamaño del puntero
	controls_mappings_keyboard = realloc (controls_mappings_keyboard, _size);
	
	controls_mappings_keyboard_count++;
	
	// setear el nuevo elemento	
	controls_mappings_keyboard[i].control = control;
	controls_mappings_keyboard[i].player = player;
	controls_mappings_keyboard[i].value = scancode;
end
/**
 * Maps a joystick axis to an action
 */
function controls_map_joy_hat(int control, int player, int joystick_id, int hatnumber, int value)
private
int i;
control_s_buttonmap pointer mappedcontrol_;
int _size = 0;
begin
	// calcular el tamaño nuevo del puntero.
	if ((controls_mappings_joystick) == NULL)
		_size = sizeof(control_s_buttonmap);
	else
		
		// buscar que no exista already
		for (i = 0; i < controls_mappings_joystick_count;i++) 
			mappedcontrol_ = controls_mappings_joystick[i];
			if (mappedcontrol_.control == (control  - 10000)  and 
				mappedcontrol_.player == player and 
				mappedcontrol_.hatnumber == hatnumber and
				mappedcontrol_.value == value )
				
				return; // duplicated
			end
		end		
		// calcula el nuevo tamaño
		_size = (controls_mappings_joystick_count+1) *  sizeof(control_s_buttonmap);
	end
	
	// redimencionar tamaño del puntero
	controls_mappings_joystick = realloc (controls_mappings_joystick, _size);
	
	controls_mappings_joystick_count++;
	
	// setear el nuevo elemento	
	controls_mappings_joystick[i].control = (control  - 10000);
	controls_mappings_joystick[i].device_id = joystick_id;
	controls_mappings_joystick[i].player = player;
	controls_mappings_joystick[i].hatnumber = hatnumber;
	controls_mappings_joystick[i].value = value ;
end
/**
 * Maps a joystick axis to an action
 */
function controls_map_joy_axis(int control, int player, int joystick_id, int axisnumber, int value)
private
int i;
control_s_buttonmap pointer mappedcontrol_;
int _size = 0;
begin
	// calcular el tamaño nuevo del puntero.
	if ((controls_mappings_joystick) == NULL)
		_size = sizeof(control_s_buttonmap);
	else
		
		// buscar que no exista already
		for (i = 0; i < controls_mappings_joystick_count;i++) 
			mappedcontrol_ = controls_mappings_joystick[i];
			if (mappedcontrol_.control == (control  - 20000) and 
				mappedcontrol_.player == player and 
				mappedcontrol_.axisnumber == axisnumber and
				mappedcontrol_.value == value)
				
				return; // duplicated
			end
		end		
		// calcula el nuevo tamaño
		_size = (controls_mappings_joystick_count+1) *  sizeof(control_s_buttonmap);
	end
	
	// redimencionar tamaño del puntero
	controls_mappings_joystick = realloc (controls_mappings_joystick, _size);
	
	controls_mappings_joystick_count++;
	
	// setear el nuevo elemento	
	controls_mappings_joystick[i].control = (control  - 20000);
	controls_mappings_joystick[i].device_id = joystick_id;
	controls_mappings_joystick[i].player = player;
	controls_mappings_joystick[i].axisnumber = axisnumber;
	controls_mappings_joystick[i].value = value;
end

/**
 * Maps a joystick button to a game control action.
 */
function controls_map_joystick(int control, int player, int joystick_id, int button)
private
int i;
control_s_buttonmap pointer mappedcontrol_;
int _size = 0;
begin
	// calcular el tamaño nuevo del puntero.
	if ((controls_mappings_joystick) == NULL)
		_size = sizeof(control_s_buttonmap);
	else
		
		// buscar que no exista already
		for (i = 0; i < controls_mappings_joystick_count;i++) 
			mappedcontrol_ = controls_mappings_joystick[i];
			if (mappedcontrol_.control == control and 
				mappedcontrol_.player == player and 
				mappedcontrol_.device_id == joystick_id and 
				mappedcontrol_.value == button)
				
				return; // duplicated
			end
		end		
		// calcula el nuevo tamaño
		_size = (controls_mappings_joystick_count+1) *  sizeof(control_s_buttonmap);
	end
	
	// redimencionar tamaño del puntero
	controls_mappings_joystick = realloc (controls_mappings_joystick, _size);
	
	controls_mappings_joystick_count++;
	
	// setear el nuevo elemento	
	controls_mappings_joystick[i].control = control;
	controls_mappings_joystick[i].device_id = joystick_id;
	controls_mappings_joystick[i].player = player;
	controls_mappings_joystick[i].value = button;
end

/**
 * Check if a button is pressed via the keyboard handler
 */
function controls_button_checkkeyb(player, button)
private
int i;
control_s_buttonmap pointer mappedcontrol_;
begin
	// busca una tecla configurada para el control
	for (i = 0; i < controls_mappings_keyboard_count;i++) 
		mappedcontrol_ = controls_mappings_keyboard[i];
		if (mappedcontrol_.control == button and 
			mappedcontrol_.player == player)			
			
			if (key(mappedcontrol_.value))
				return true;
			end
		end
	end
	
	return false;
end

/**
 * returns true if a button on any device binded to an action is pressed. 
 * if the device button is an axis it will return the value of the axis
 */
function controls_button_checkjoy(player, button)
private
int i;
control_s_buttonmap pointer mappedcontrol_;
value;
begin
	// busca una tecla configurada para el control
	for (i = 0; i < controls_mappings_joystick_count;i++) 
		mappedcontrol_ = controls_mappings_joystick[i];
		
		if ((mappedcontrol_.control == button 
			or mappedcontrol_.control == (button  - 10000)
			or mappedcontrol_.control == (button  - 20000)) and 
			mappedcontrol_.player == player and mappedcontrol_.device_id > -1)
			
			// check joystick
			
			
			if(mappedcontrol_.axisnumber > -1 and mappedcontrol_.control == (button  - 20000) )
				if (mappedcontrol_.value > 0)
					if((value = joy_getaxis(mappedcontrol_.device_id,mappedcontrol_.axisnumber)) > mappedcontrol_.value)
						return value;
					end
				else
					if((value = joy_getaxis(mappedcontrol_.device_id,mappedcontrol_.axisnumber)) < mappedcontrol_.value)
						return value;
					end
				end
			end
			if(mappedcontrol_.hatnumber > -1 and mappedcontrol_.control == (button  - 10000))
				// HAT check
				if (joy_gethat(mappedcontrol_.device_id ,0) == mappedcontrol_.value)
					return true;
				end
			end
			if (joy_getbutton(mappedcontrol_.device_id ,mappedcontrol_.value) and mappedcontrol_.control == button)
				return true;
			end
			
			// •  •  •  •  •  •  •  • 
			
		end
	end
	
	return false;
end

/**
 * Check for if a control button is pressed in any controller device
 */
function control(player, button)
private
	value;
begin
	// check keyboard
	if (controls_button_checkkeyb(player, button))
		return true;
	end
	// check joystick
    if ((value = controls_button_checkjoy(player, button)) != false )
		return value;
	end
	return false;
end

/**
 * Check the button is pressed and then released
 */ 
function control_(player, button)
private
    value, return_value = false;	
begin
    while((value = control(player, button)) != false)		
		return_value = value;
        frame; // limpiamos buffer de teclas 
    end

    return return_value;
end