
/**
 * auto detects the best mode for the current device's screen size
 */
 
global
	int _autodetect_original_width;
	int _autodetect_original_height;	
end 

function resolution_offset_x()
begin
	return (map_info(0,0,G_WIDTH) - _autodetect_original_width) / 2;
end

function resolution_offset_y()
begin
	return (map_info(0,0,G_HEIGHT) - _autodetect_original_height) / 2;
end
 
function autodetect_mode(width,height,bpp)
private
	dsx, dsy;
	new_width,new_height;
end
begin
	// obtiene resolution del dispositivo
	
	_autodetect_original_width = width;
	_autodetect_original_height = height;
	
	get_desktop_size(&dsx, &dsy);
	
	if (full_screen == true)
		scale_resolution = dsx * 10000 + dsy ;
		scale_resolution_aspectratio = SRA_PRESERVE;
		
		if (width > height)
			new_width = width; // se mantiene el lado mas grande de la resolucion original
			new_height = dsy * (float) ((((float) width)/ ((float) dsx))); // el lado mas chico se adapta a la resolucion del dispositivo
		else
			new_height = height; // se mantiene el lado mas grande de la resolucion original
			new_width = dsx * (float) (((float) height/ ((float) dsy))); // el lado mas chico se adapta a la resolucion del dispositivo
		end
	else
		new_width = width;
		new_height = height;
	end
	
	// si no se puede agrandar la pantalla dejamos la res original
	if (new_width < width or new_height < height)
		new_width = width;
		new_height = height;
	end
	
	set_mode(new_width,new_height,bpp);
end

process screen_configcontrol_()
private
restored_scale;
int dsx, dsy;
int RotateMode; // Open Pandora --> 0: Normal screen, 1: Rotate screen Left, 2: Rotate screen Down, 3: Rotate screen Right
int AspectRatio;
end
begin
	// The current process ignores the signals from now on
	signal_action(S_KILL,S_IGN);
	signal_action(S_SLEEP,S_IGN);
	signal_action(S_FREEZE,S_IGN);
	
	restored_scale = scale_resolution;
	
	loop
	    if (os_id == 1010) // Open Pandora (Always Fullscreen)

		    if (key(_1)) // Screen Rotation
			    while(key(_1)) frame; end
				
				// 4 screen rotations with original resolution + 4 screen rotations with Pandora stretch fullscreen
				RotateMode++;
				AspectRatio++;
				
				if (RotateMode > 3) RotateMode = 0; end
				if (AspectRatio > 7) AspectRatio = 0; end

				if (AspectRatio > 3)
					if (AspectRatio == 4 or AspectRatio == 6)
					    scale_resolution = 08000480;
					else
					    //scale_resolution = 04800800; // Inverse Pandora resolution
						scale_resolution = 04790799; // Fix crash Pandora Bug!
					end
				    scale_resolution_aspectratio = 0; // 0 - Fullscreen Stretch, 1 - Original aspect ratio
				else
				    scale_resolution = 03200480; // map_info(0,0,G_WIDTH) + map_info(0,0,G_HEIGHT)
				    scale_resolution_aspectratio = 1;
				end
				
				scale_resolution_orientation = RotateMode;

			    set_mode(map_info(0,0,G_WIDTH), map_info(0,0,G_HEIGHT));
			    continue;
		    end

		    // Disabled on this version, BennuGD bug ?: scale_resolution_orientation don't affect screen using "scale_mode = SCALE_HQ2X"
		    /*if (key(_2)) // Filter
			    while(key(_2)) frame; end
				
			    if (scale_mode == SCALE_NONE) 
				    scale_mode = SCALE_HQ2X;
				    scale_resolution = null;			
			    else
				    scale_mode = SCALE_NONE;
				    scale_resolution = 08000480;
					scale_resolution_aspectratio = SRA_PRESERVE;
			    end		
			
			    set_mode(map_info(0,0,G_WIDTH),map_info(0,0,G_HEIGHT));
			    continue;
			
		    end*/
		
		else
		
		    if (key(_ENTER) and key(_ALT))
			    while(key(_ENTER) AND key(_ALT)) frame; end
			    full_screen = !full_screen;
			
			    if (!full_screen)
				    scale_resolution = restored_scale;
				    scale_mode = SCALE_NONE;
			    else
				    scale_mode = SCALE_NONE;
				    get_desktop_size(&dsx, &dsy);
				    scale_resolution = dsx * 10000 + dsy ;
				    scale_resolution_aspectratio = SRA_PRESERVE;
			    end
			
			    set_mode(map_info(0,0,G_WIDTH),map_info(0,0,G_HEIGHT));
			    continue;
		    end
		
		    if (key(_F2))
			    while(key(_F2)) frame; end
				
			    if (scale_mode == SCALE_NONE) 
				    scale_mode = SCALE_HQ2X;
				    scale_resolution = null;			
			    else
				    scale_mode = SCALE_NONE;
				
				    if (!full_screen)
					    scale_resolution = restored_scale;
				    else				
					    get_desktop_size(&dsx, &dsy);
					    scale_resolution = dsx * 10000 + dsy ;
					    scale_resolution_aspectratio = SRA_PRESERVE;
				    end
			    end		
			
			    set_mode(map_info(0,0,G_WIDTH),map_info(0,0,G_HEIGHT));
			    continue;
			
		    end
		
		end
		
		frame;		
	end
end