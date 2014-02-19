
process mono()
public 
	string status = "standing";
	byte anim_pos = 0;
private
	byte anim_standing[11] = 9,9,9,10,10,10,11,11,11,12,12,12;
	byte anim_running[15] = 1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8;
	byte anim_win[7] = 13,13,13,13,14,14,14,14;
	byte anim_loose[7] = 15,15,15,15,16,16,16,16;

	
	
	byte pointer anim_pointer;
	byte count;
	inc_x; //velocidad
begin
	//region = 1;
	file = monkey_fpg;
	y = ALTO_PANTALLA - 15 -2;
	x = resolution_offset_x() + (ANCHO_PANTALLA / 2);
	z = -2;
	loop	
		switch(status):
			case "running":
				if ((!mouse.left and !control(1,CONTROL_OK)) or mouse.x==x) // Open Pandora: Button A
					status = "standing";
					anim_pos = 0;
					
					anim_pointer = &anim_standing;
					count = sizeof(anim_standing)/sizeof(byte);
				else
				
					if (mouse.x<x)
						// cambia de direccion
						flags = 0;
						inc_x = -5;
						
						if ((mouse.x - x) > inc_x) inc_x = mouse.x - x; end
					end
					
					if (mouse.x>x)
						flags = 1;
						inc_x = 5;
						
						if ((mouse.x - x) < inc_x) inc_x = mouse.x - x; end
					end
					
					
					
					x += inc_x;				
				end
			end
			case "standing":
			
				// si termina la anim pasa al siguiente estado
				if ((mouse.left or control(1,CONTROL_OK)) and mouse.x!=x) // Open Pandora: Button A
					status = "running";
					anim_pos = 0;
					
					anim_pointer = &anim_running;
					count = sizeof(anim_running)/sizeof(byte);					
				else
					anim_pointer = &anim_standing;
					count = sizeof(anim_standing)/sizeof(byte);
				end
			end
			case "win":
				anim_pointer = &anim_win;
				count = sizeof(anim_win)/sizeof(byte);
			end
			case "loose":
				anim_pointer = &anim_loose;
				count = sizeof(anim_win)/sizeof(byte);
			end
		end
		
		// anima 
		anim_pos++;
		if (anim_pos >= count)
			anim_pos = 0;
		end
		graph = anim_pointer[anim_pos];	
		
		frame;
	end
end
