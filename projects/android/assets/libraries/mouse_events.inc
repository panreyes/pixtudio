/**
 * checkeo de evento Drag & Drop
 */
const
	// mouse event names
	MOUSE_DOWN = 1;
	MOUSE_UP = 2;
	MOUSE_DRAG = 4;
	MOUSE_DROP = 8;
	MOUSE_MOVE = 16;
end 
global
	unsigned byte mouse_event = 0; // global var holding current mouse event.
	unsigned byte prev_mouse_event = 0; 
	prev_mouse_x = 0; 
	prev_mouse_y = 0; 
end

function mouse_event(event)
begin
	return ((mouse_event & event) == event);
end

process mouse_events_init()
private
dist;
begin
	prev_mouse_x = mouse.x; 
	prev_mouse_y = mouse.y;
	
	//	ignoramos señales
	signal_action(S_FREEZE,S_IGN);
	signal_action(S_SLEEP,S_IGN);
	signal_action(S_KILL,S_IGN);
	
	loop
		mouse_event = 0;
		
		// check mouse move
		if (prev_mouse_x != mouse.x OR 	prev_mouse_y != mouse.y)
			mouse_event |= MOUSE_MOVE;
		end 
		
		// check mouse down
		if (mouse.left or (os_id == 1010 and key(_home))) // Open Pandora: Button A
			mouse_event |= MOUSE_DOWN;
		end
				
		// check mouse up
		if (((prev_mouse_event & MOUSE_DOWN) == MOUSE_DOWN) AND !mouse.left AND !(os_id == 1010 and key(_home))) // Open Pandora: Button A
			mouse_event |= MOUSE_UP;			
		end
		
		// check mouse DRAG
		if ((((prev_mouse_event & MOUSE_DOWN) == MOUSE_DOWN) AND (mouse_event & MOUSE_DOWN) == MOUSE_DOWN)
			AND ((prev_mouse_event & MOUSE_MOVE) == MOUSE_MOVE))
			
			// calculates mouse distance from previous frame
			dist = sqrt(pow(mouse.x - prev_mouse_x,2) + pow(mouse.y - prev_mouse_y,2));
			if (dist > 3)
				mouse_event |= MOUSE_DRAG;
			end			
			
		end		
		// check mouse DRAG
		if (((prev_mouse_event & MOUSE_DRAG) == MOUSE_DRAG) AND (mouse_event & MOUSE_DOWN) == MOUSE_DOWN)						
			mouse_event |= MOUSE_DRAG;
		end
				
		// check mouse DROP
		if (((prev_mouse_event & MOUSE_DRAG) == MOUSE_DRAG) and ((mouse_event & MOUSE_UP) == MOUSE_UP))
			mouse_event |= MOUSE_DROP;			
		end
		
		prev_mouse_x = mouse.x; 
		prev_mouse_y = mouse.y; 
		frame;
		prev_mouse_event = mouse_event;
		
	end
end