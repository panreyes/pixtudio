project(pxtrtm)
cmake_minimum_required(VERSION 3.4)
# Required stuff
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${pxtrtm_SOURCE_DIR}/../../include")
find_package(SDL2 2.0.4 REQUIRED)
find_package(SDL2_Mixer REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)
find_package(Vorbis REQUIRED)
find_package(Theora REQUIRED)
find_package(Freetype REQUIRED)
find_package(OpenAL REQUIRED)
find_package(TRE REQUIRED)
find_package(CURL)
find_package(STEAMWORKS)
# Preprocessor macros
add_definitions(-D__PXTRTM__)
if(NOT STEAMWORKS_FOUND)
  add_definitions(-DNO_MODSTEAM)
endif(NOT STEAMWORKS_FOUND)
if(NOT CURL_FOUND)
  add_definition(-DNO_MODCURL)
endif(NOT CURL_FOUND)
include(common_defs)
# Source files
set(SOURCE_FILES
  ${pxtrtm_SOURCE_DIR}/../../../../core/common/debug.c
  ${pxtrtm_SOURCE_DIR}/../../../../core/common/files.c
  ${pxtrtm_SOURCE_DIR}/../../../../core/common/xctype.c
  ${pxtrtm_SOURCE_DIR}/../../../../core/include/commons_defs.h
  ${pxtrtm_SOURCE_DIR}/../../../../core/include/dcb.h
  ${pxtrtm_SOURCE_DIR}/../../../../core/include/loadlib.h
  ${pxtrtm_SOURCE_DIR}/../../../../core/include/monolithic_includes.h
  ${pxtrtm_SOURCE_DIR}/../../../../core/include/pxtcore.h
  ${pxtrtm_SOURCE_DIR}/../../../../core/include/pxtdl.h
  ${pxtrtm_SOURCE_DIR}/../../../../core/include/sysprocs.h
  ${pxtrtm_SOURCE_DIR}/../../../../core/include/xctype.h
  ${pxtrtm_SOURCE_DIR}/../../../../core/include/xctype_st.h
  ${pxtrtm_SOURCE_DIR}/../../../../core/include/i_procdef.h
  ${pxtrtm_SOURCE_DIR}/../../../../core/include/i_procdef_st.h
  ${pxtrtm_SOURCE_DIR}/../../../../core/include/instance.h
  ${pxtrtm_SOURCE_DIR}/../../../../core/include/instance_st.h
  ${pxtrtm_SOURCE_DIR}/../../../../core/pxtrtm/include/pxtrtm.h
  ${pxtrtm_SOURCE_DIR}/../../../../core/pxtrtm/include/sysprocs_p.h
  ${pxtrtm_SOURCE_DIR}/../../../../core/pxtrtm/src/copy.c
  ${pxtrtm_SOURCE_DIR}/../../../../core/pxtrtm/src/dcbr.c
  ${pxtrtm_SOURCE_DIR}/../../../../core/pxtrtm/src/dirs.c
  ${pxtrtm_SOURCE_DIR}/../../../../core/pxtrtm/src/fmath.c
  ${pxtrtm_SOURCE_DIR}/../../../../core/pxtrtm/src/instance.c
  ${pxtrtm_SOURCE_DIR}/../../../../core/pxtrtm/src/interpreter.c
  ${pxtrtm_SOURCE_DIR}/../../../../core/pxtrtm/src/misc.c
  ${pxtrtm_SOURCE_DIR}/../../../../core/pxtrtm/src/strings.c
  ${pxtrtm_SOURCE_DIR}/../../../../core/pxtrtm/src/sysprocs.c
  ${pxtrtm_SOURCE_DIR}/../../../../core/pxtrtm/src/varspace_file.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libbgload/bgload.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libbgload/bgload.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libblit/g_blit.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libblit/g_blit.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libblit/g_blitflags.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libblit/g_pixel.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libblit/g_pixel.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libblit/libblit.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libblit/libblit_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libdraw/libdraw.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libdraw/libdraw.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libfont/libfont.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libfont/libfont.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libfont/libfont_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libfont/systemfont.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/g_bitmap.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/g_bitmap.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/g_blendop.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/g_blendop.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/g_clear.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/g_clear.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/g_conversion.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/g_conversion.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/g_grlib.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/g_grlib.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/g_pal.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/g_pal.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/g_region.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/libgrbase.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/libgrbase.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/libgrbase_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/resolution.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libjoy/libjoy.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libjoy/libjoy.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libjoy/libjoy_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libkey/libkey.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libmouse/libmouse.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/librender/g_fade.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/librender/g_fade.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/librender/g_frame.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/librender/g_frame.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/librender/g_instance.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/librender/g_instance.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/librender/g_object.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/librender/g_object.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/librender/g_rects.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/librender/g_rects.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/librender/g_screen.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/librender/g_screen.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/librender/librender.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/librender/librender.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/librender/librender_constants.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/librender/librender_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libscroll/libscroll.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libscroll/libscroll.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libscroll/libscroll.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libscroll/libscroll_constants.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libscroll/libscroll_constants.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libscroll/libscroll_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libscroll/libscroll_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libsdlhandler/libsdlhandler.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libsdlhandler/libsdlhandler_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libsocket/libsocket.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libsocket/libsocket.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libtext/libtext.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libtext/libtext.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libtext/libtext_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libvideo/g_regions.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libvideo/g_regions.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libvideo/g_video.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libvideo/g_video.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libvideo/g_video_constants.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libvideo/libvideo.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libvideo/libvideo_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libwm/libwm.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/libwm/libwm_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_chipmunk/agua.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_chipmunk/arbitros.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_chipmunk/Arreglos.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_chipmunk/automGenTerr.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_chipmunk/constantes.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_chipmunk/Constraints.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_chipmunk/convexHull.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_chipmunk/Cuerpo.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_chipmunk/Espacio.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_chipmunk/estructuras.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_chipmunk/globales.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_chipmunk/Handlers.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_chipmunk/inl.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_chipmunk/LL.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_chipmunk/locales.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_chipmunk/Miscelanea.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_chipmunk/mod_chipmunk_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_debug/mod_debug.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_debug/mod_debug_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_dir/mod_dir.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_dir/mod_dir_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_draw/mod_draw.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_draw/mod_draw_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_effects/mod_effects.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_effects/mod_effects.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_effects/mod_effects_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_file/mod_file.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_file/mod_file_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_fsock/mod_fsock.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_fsock/mod_fsock_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_gamecontroller/mod_gamecontroller.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_gamecontroller/mod_gamecontroller.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_gamecontroller/mod_gamecontroller_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_grproc/mod_grproc.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_grproc/mod_grproc_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_joy/mod_joy.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_joy/mod_joy_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_key/mod_key.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_key/mod_key_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_map/file_fnt.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_map/file_fpg.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_map/file_map.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_map/file_pal.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_map/file_pcx.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_map/file_png.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_map/file_jpg.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_map/mod_map.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_map/mod_map.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_map/mod_map_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_math/mod_math.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_math/mod_math_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_mem/mod_mem.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_mem/mod_mem_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_mouse/mod_mouse_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_multi/mod_multi.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_multi/mod_multi.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_multi/mod_multi_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_path/mod_path.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_path/mod_path_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_proc/mod_proc.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_proc/mod_proc.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_proc/mod_proc_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_rand/mod_rand.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_rand/mod_rand_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_regex/mod_regex.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_regex/mod_regex_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_say/mod_say.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_say/mod_say_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_screen/mod_screen.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_screen/mod_screen_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_scroll/mod_scroll.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_scroll/mod_scroll_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_sort/mod_sort.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_sort/mod_sort_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_sound/mod_sound.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_sound/mod_sound.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_sound/mod_sound_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_sqlite3/mod_sqlite3_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_string/mod_string.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_string/mod_string_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_sys/mod_sys.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_sys/mod_sys.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_sys/mod_sys_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_text/mod_text.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_text/mod_text_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_theora/mod_theora.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_theora/mod_theora_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../3rdparty/theoraplay/theoraplay.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_time/mod_time.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_time/mod_time_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_timers/mod_timers.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_timers/mod_timers_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_video/mod_video.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_video/mod_video_symbols.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_wm/locale/get_locale.h
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_wm/mod_wm.c
  ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_wm/mod_wm_symbols.h)

# OS-specific files
if(WIN32)
    list(APPEND SOURCE_FILES
         ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_wm/locale/win32.c)
elseif(APPLE)
    list(APPEND SOURCE_FILES
         ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_wm/locale/darwin.m)
else()
    list(APPEND SOURCE_FILES
         ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_wm/locale/env.c)
endif()

# Optional modules
if(CURL_FOUND)
  list(APPEND SOURCE_FILES
       ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_curl/mod_curl_symbols.h
       ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_curl/mod_curl.c)
  include_directories(${pxtrtm_SOURCE_DIR}/../../../../modules/mod_curl/
                      ${CURL_INCLUDE_DIR})
endif(CURL_FOUND)

if(STEAMWORKS_FOUND)
  list(APPEND SOURCE_FILES
       ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_steam/mod_steam.cpp
       ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_steam/mod_steam.h
       ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_steam/mod_steam_symbols.h)
  include_directories(${pxtrtm_SOURCE_DIR}/../../../../modules/mod_steam/
                      ${STEAMWORKS_INCLUDE_DIR})
endif(STEAMWORKS_FOUND)

# Include dirs
include_directories(${pxtrtm_SOURCE_DIR}/../../../../core/pxtrtm/include
                    ${pxtrtm_SOURCE_DIR}/../../../../core/include
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/libbgload/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_debug/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_say/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_string/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_math/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_mem/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_time/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_file/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_sound/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/libsdlhandler/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_gamecontroller/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_joy/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/libjoy/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_theora/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/libkey/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_key/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_proc/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_sort/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_timers/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/libgrbase/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/libblit/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/libvideo/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/librender/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_video/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/libmouse/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_mouse/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_multi/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_map/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/libfont/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_dir/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/libtext/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_text/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_rand/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_grproc/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/libscroll/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_scroll/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/libdraw/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_draw/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_screen/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_path/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/libwm/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_wm/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_sys/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_regex/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_fsock/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_effects/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/libsocket/
                    ${pxtrtm_SOURCE_DIR}/../../../../modules/mod_ttf/
                    ${pxtrtm_SOURCE_DIR}/../../../../3rdparty/stb/
                    ${pxtrtm_SOURCE_DIR}/../../../../3rdparty/theoraplay/
                    ${SDL2_INCLUDE_DIR}
                    ${SDL2_MIXER_INCLUDE_DIRS}
                    ${ZLIB_INCLUDE_DIRS}
                    ${VORBIS_INCLUDE_DIR}
                    ${THEORA_INCLUDE_DIR}
                    ${FREETYPE_INCLUDE_DIRS}
                    ${OPENAL_INCLUDE_DIR}
                    ${TRE_INCLUDE_DIR}
                    ${PNG_INCLUDE_DIR}
                    ${JPEG_INCLUDE_DIR})
# Main executable
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Include the compiler flags from the external include file
include(compiler_flags)

