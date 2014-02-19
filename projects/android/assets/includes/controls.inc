// default control constants
const
CONTROL_OK = 1;
CONTROL_CANCEL = 2;
CONTROL_LEFT = 3;
CONTROL_RIGHT = 4;
CONTROL_UP = 5;
CONTROL_DOWN = 6;
end

function configurecontrols()
begin
	// configuramos keyboard
	controls_map_keyboard(CONTROL_UP,1, _up);
	controls_map_keyboard(CONTROL_DOWN,1, _down);
	controls_map_keyboard(CONTROL_LEFT,1, _left);
	controls_map_keyboard(CONTROL_RIGHT,1, _right);
	controls_map_keyboard(CONTROL_OK,1, _enter);
	controls_map_keyboard(CONTROL_CANCEL,1, _esc);
		
	if(os_id == 1003) // Android
		controls_map_keyboard(CONTROL_CANCEL,1, 102); // boton fisico volver
	end
	
	if (os_id == 1010) // Open Pandora
	    controls_map_keyboard(CONTROL_OK,1, _alt); // Button 'Start'
		controls_map_keyboard(CONTROL_OK,1,_home); // Open Pandora: Button A
	end
	
	
	// y mapeamos el joystick tambien
	if (joy_number())
		switch(os_id)
			case 1003: // OUYA (android)
			
				// asigna controles al joystick 0
				controls_map_joystick(CONTROL_UP, 1, 0, 0);
				controls_map_joystick(CONTROL_DOWN, 1, 0, 1);
				controls_map_joystick(CONTROL_LEFT, 1, 0, 2);
				controls_map_joystick(CONTROL_RIGHT, 1, 0, 3);
				
				controls_map_joy_axis(CONTROL_UP, 1, 0, 1, -10000);
				controls_map_joy_axis(CONTROL_DOWN, 1, 0, 1, 10000);
				controls_map_joy_axis(CONTROL_LEFT, 1, 0, 0, -10000);
				controls_map_joy_axis(CONTROL_RIGHT, 1, 0, 0, 10000);
				
				controls_map_joystick(CONTROL_OK,1, 0, 5); // boton O en ouya
				controls_map_joystick(CONTROL_CANCEL,1, 0, 6); // boton A en ouya
			end
            case OS_MACOS: // OSX
				// asigna controles al joystick 0
				controls_map_joy_hat(CONTROL_UP, 1, 0, 0,JOY_HAT_UP);
				controls_map_joy_hat(CONTROL_DOWN, 1, 0, 0,JOY_HAT_DOWN);
				controls_map_joy_hat(CONTROL_LEFT, 1, 0, 0,JOY_HAT_LEFT);
				controls_map_joy_hat(CONTROL_RIGHT, 1, 0, 0,JOY_HAT_RIGHT);
				
				controls_map_joy_axis(CONTROL_UP, 1, 0, 1, -10000);
				controls_map_joy_axis(CONTROL_DOWN, 1, 0, 1, 10000);
				controls_map_joy_axis(CONTROL_LEFT, 1, 0, 0, -10000);
				controls_map_joy_axis(CONTROL_RIGHT, 1, 0, 0, 10000);
                
                controls_map_joystick(CONTROL_UP,1, 0, 0); // DPAD
				controls_map_joystick(CONTROL_DOWN,1, 0, 1); 
                controls_map_joystick(CONTROL_LEFT,1, 0, 2);
				controls_map_joystick(CONTROL_RIGHT,1, 0, 3); 

                controls_map_joystick(CONTROL_OK,1, 0, 11); // boton A xbox gamepad
				controls_map_joystick(CONTROL_CANCEL,1, 0, 12); // boton B xbox gamepad   
            end
			default: // PC
				// asigna controles al joystick 0
				controls_map_joy_hat(CONTROL_UP, 1, 0, 0,JOY_HAT_UP);
				controls_map_joy_hat(CONTROL_DOWN, 1, 0, 0,JOY_HAT_DOWN);
				controls_map_joy_hat(CONTROL_LEFT, 1, 0, 0,JOY_HAT_LEFT);
				controls_map_joy_hat(CONTROL_RIGHT, 1, 0, 0,JOY_HAT_RIGHT);
				
				controls_map_joy_axis(CONTROL_UP, 1, 0, 1, -10000);
				controls_map_joy_axis(CONTROL_DOWN, 1, 0, 1, 10000);
				controls_map_joy_axis(CONTROL_LEFT, 1, 0, 0, -10000);
				controls_map_joy_axis(CONTROL_RIGHT, 1, 0, 0, 10000);
				
				controls_map_joystick(CONTROL_OK,1, 0, 0); // boton A xbox gamepad
				controls_map_joystick(CONTROL_CANCEL,1, 0, 1); // boton B xbox gamepad
				
			end
		end
	end
end
