project(pxtrtm CXX)
cmake_minimum_required(VERSION 3.4)
set(C_PXTRTM 1)

# Required stuff
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${pxtrtm_SOURCE_DIR}/../../include")
set(PXT_MODULES_PATH "${pxtrtm_SOURCE_DIR}/../../../../modules")
set(PXT_3RDPARTY "${pxtrtm_SOURCE_DIR}/../../../../3rdparty")
set(PXT_CORE_PATH "${pxtrtm_SOURCE_DIR}/../../../../core")
include(optional_modules)
include(do_find_libs)

# Preprocessor macros
add_definitions(-D__PXTRTM__)

# Common defines
include(common_defs)

# Source files
set(SOURCE_FILES
  ${PXT_CORE_PATH}/common/debug.c
  ${PXT_CORE_PATH}/common/files.c
  ${PXT_CORE_PATH}/common/xctype.c
  ${PXT_CORE_PATH}/include/commons_defs.h
  ${PXT_CORE_PATH}/include/dcb.h
  ${PXT_CORE_PATH}/include/loadlib.h
  ${PXT_CORE_PATH}/include/monolithic_includes.h
  ${PXT_CORE_PATH}/include/pxtcore.h
  ${PXT_CORE_PATH}/include/pxtdl.h
  ${PXT_CORE_PATH}/include/sysprocs.h
  ${PXT_CORE_PATH}/include/xctype.h
  ${PXT_CORE_PATH}/include/xctype_st.h
  ${PXT_CORE_PATH}/include/i_procdef.h
  ${PXT_CORE_PATH}/include/i_procdef_st.h
  ${PXT_CORE_PATH}/include/instance.h
  ${PXT_CORE_PATH}/include/instance_st.h
  ${PXT_CORE_PATH}/pxtrtm/include/pxtrtm.h
  ${PXT_CORE_PATH}/pxtrtm/include/sysprocs_p.h
  ${PXT_CORE_PATH}/pxtrtm/src/copy.c
  ${PXT_CORE_PATH}/pxtrtm/src/dcbr.c
  ${PXT_CORE_PATH}/pxtrtm/src/dirs.c
  ${PXT_CORE_PATH}/pxtrtm/src/fmath.c
  ${PXT_CORE_PATH}/pxtrtm/src/instance.c
  ${PXT_CORE_PATH}/pxtrtm/src/interpreter.c
  ${PXT_CORE_PATH}/pxtrtm/src/misc.c
  ${PXT_CORE_PATH}/pxtrtm/src/strings.c
  ${PXT_CORE_PATH}/pxtrtm/src/sysprocs.c
  ${PXT_CORE_PATH}/pxtrtm/src/varspace_file.c
  ${PXT_MODULES_PATH}/libbgload/bgload.c
  ${PXT_MODULES_PATH}/libbgload/bgload.h
  ${PXT_MODULES_PATH}/libblit/g_blit.c
  ${PXT_MODULES_PATH}/libblit/g_blit.h
  ${PXT_MODULES_PATH}/libblit/g_blitflags.h
  ${PXT_MODULES_PATH}/libblit/g_pixel.c
  ${PXT_MODULES_PATH}/libblit/g_pixel.h
  ${PXT_MODULES_PATH}/libblit/libblit.h
  ${PXT_MODULES_PATH}/libblit/libblit_symbols.h
  ${PXT_MODULES_PATH}/libdraw/libdraw.c
  ${PXT_MODULES_PATH}/libdraw/libdraw.h
  ${PXT_MODULES_PATH}/libfont/libfont.c
  ${PXT_MODULES_PATH}/libfont/libfont.h
  ${PXT_MODULES_PATH}/libfont/libfont_symbols.h
  ${PXT_MODULES_PATH}/libfont/systemfont.h
  ${PXT_MODULES_PATH}/libgrbase/g_bitmap.c
  ${PXT_MODULES_PATH}/libgrbase/g_bitmap.h
  ${PXT_MODULES_PATH}/libgrbase/g_blendop.c
  ${PXT_MODULES_PATH}/libgrbase/g_blendop.h
  ${PXT_MODULES_PATH}/libgrbase/g_clear.c
  ${PXT_MODULES_PATH}/libgrbase/g_clear.h
  ${PXT_MODULES_PATH}/libgrbase/g_conversion.c
  ${PXT_MODULES_PATH}/libgrbase/g_conversion.h
  ${PXT_MODULES_PATH}/libgrbase/g_grlib.c
  ${PXT_MODULES_PATH}/libgrbase/g_grlib.h
  ${PXT_MODULES_PATH}/libgrbase/g_pal.c
  ${PXT_MODULES_PATH}/libgrbase/g_pal.h
  ${PXT_MODULES_PATH}/libgrbase/g_region.h
  ${PXT_MODULES_PATH}/libgrbase/libgrbase.c
  ${PXT_MODULES_PATH}/libgrbase/libgrbase.h
  ${PXT_MODULES_PATH}/libgrbase/libgrbase_symbols.h
  ${PXT_MODULES_PATH}/libgrbase/resolution.h
  ${PXT_MODULES_PATH}/libjoy/libjoy.c
  ${PXT_MODULES_PATH}/libjoy/libjoy.h
  ${PXT_MODULES_PATH}/libjoy/libjoy_symbols.h
  ${PXT_MODULES_PATH}/libkey/libkey.c
  ${PXT_MODULES_PATH}/libmouse/libmouse.c
  ${PXT_MODULES_PATH}/librender/g_fade.c
  ${PXT_MODULES_PATH}/librender/g_fade.h
  ${PXT_MODULES_PATH}/librender/g_frame.c
  ${PXT_MODULES_PATH}/librender/g_frame.h
  ${PXT_MODULES_PATH}/librender/g_instance.c
  ${PXT_MODULES_PATH}/librender/g_instance.h
  ${PXT_MODULES_PATH}/librender/g_object.c
  ${PXT_MODULES_PATH}/librender/g_object.h
  ${PXT_MODULES_PATH}/librender/g_rects.c
  ${PXT_MODULES_PATH}/librender/g_rects.h
  ${PXT_MODULES_PATH}/librender/g_screen.c
  ${PXT_MODULES_PATH}/librender/g_screen.h
  ${PXT_MODULES_PATH}/librender/g_shaders.c
  ${PXT_MODULES_PATH}/librender/g_shaders.h
  ${PXT_MODULES_PATH}/librender/librender.c
  ${PXT_MODULES_PATH}/librender/librender.h
  ${PXT_MODULES_PATH}/librender/librender_constants.h
  ${PXT_MODULES_PATH}/librender/librender_symbols.h
  ${PXT_MODULES_PATH}/libscroll/libscroll.c
  ${PXT_MODULES_PATH}/libscroll/libscroll.h
  ${PXT_MODULES_PATH}/libscroll/libscroll.h
  ${PXT_MODULES_PATH}/libscroll/libscroll_constants.h
  ${PXT_MODULES_PATH}/libscroll/libscroll_constants.h
  ${PXT_MODULES_PATH}/libscroll/libscroll_symbols.h
  ${PXT_MODULES_PATH}/libscroll/libscroll_symbols.h
  ${PXT_MODULES_PATH}/libsdlhandler/libsdlhandler.c
  ${PXT_MODULES_PATH}/libsdlhandler/libsdlhandler_symbols.h
  ${PXT_MODULES_PATH}/libtext/libtext.c
  ${PXT_MODULES_PATH}/libtext/libtext.h
  ${PXT_MODULES_PATH}/libtext/libtext_symbols.h
  ${PXT_MODULES_PATH}/libvideo/g_regions.c
  ${PXT_MODULES_PATH}/libvideo/g_regions.h
  ${PXT_MODULES_PATH}/libvideo/g_video.c
  ${PXT_MODULES_PATH}/libvideo/g_video.h
  ${PXT_MODULES_PATH}/libvideo/g_video_constants.h
  ${PXT_MODULES_PATH}/libvideo/libvideo.h
  ${PXT_MODULES_PATH}/libvideo/libvideo_symbols.h
  ${PXT_MODULES_PATH}/libwm/libwm.c
  ${PXT_MODULES_PATH}/libwm/libwm_symbols.h
  ${PXT_MODULES_PATH}/mod_dir/mod_dir.c
  ${PXT_MODULES_PATH}/mod_dir/mod_dir_symbols.h
  ${PXT_MODULES_PATH}/mod_draw/mod_draw.c
  ${PXT_MODULES_PATH}/mod_draw/mod_draw_symbols.h
  ${PXT_MODULES_PATH}/mod_file/mod_file.c
  ${PXT_MODULES_PATH}/mod_file/mod_file_symbols.h
  ${PXT_MODULES_PATH}/mod_gamecontroller/mod_gamecontroller.c
  ${PXT_MODULES_PATH}/mod_gamecontroller/mod_gamecontroller.h
  ${PXT_MODULES_PATH}/mod_gamecontroller/mod_gamecontroller_symbols.h
  ${PXT_MODULES_PATH}/mod_grproc/mod_grproc.c
  ${PXT_MODULES_PATH}/mod_grproc/mod_grproc_symbols.h
  ${PXT_MODULES_PATH}/mod_joy/mod_joy.c
  ${PXT_MODULES_PATH}/mod_joy/mod_joy_symbols.h
  ${PXT_MODULES_PATH}/mod_key/mod_key.c
  ${PXT_MODULES_PATH}/mod_key/mod_key_symbols.h
  ${PXT_MODULES_PATH}/mod_map/file_fnt.c
  ${PXT_MODULES_PATH}/mod_map/file_fpg.c
  ${PXT_MODULES_PATH}/mod_map/file_map.c
  ${PXT_MODULES_PATH}/mod_map/file_pal.c
  ${PXT_MODULES_PATH}/mod_map/file_pcx.c
  ${PXT_MODULES_PATH}/mod_map/file_png.c
  ${PXT_MODULES_PATH}/mod_map/file_jpg.c
  ${PXT_MODULES_PATH}/mod_map/file_webp.c
  ${PXT_MODULES_PATH}/mod_map/mod_map.c
  ${PXT_MODULES_PATH}/mod_map/mod_map.h
  ${PXT_MODULES_PATH}/mod_map/mod_map_symbols.h
  ${PXT_MODULES_PATH}/mod_math/mod_math.c
  ${PXT_MODULES_PATH}/mod_math/mod_math_symbols.h
  ${PXT_MODULES_PATH}/mod_mouse/mod_mouse_symbols.h
  ${PXT_MODULES_PATH}/mod_path/mod_path.c
  ${PXT_MODULES_PATH}/mod_path/mod_path_symbols.h
  ${PXT_MODULES_PATH}/mod_proc/mod_proc.c
  ${PXT_MODULES_PATH}/mod_proc/mod_proc.h
  ${PXT_MODULES_PATH}/mod_proc/mod_proc_symbols.h
  ${PXT_MODULES_PATH}/mod_rand/mod_rand.c
  ${PXT_MODULES_PATH}/mod_rand/mod_rand_symbols.h
  ${PXT_MODULES_PATH}/mod_say/mod_say.c
  ${PXT_MODULES_PATH}/mod_say/mod_say_symbols.h
  ${PXT_MODULES_PATH}/mod_screen/mod_screen.c
  ${PXT_MODULES_PATH}/mod_screen/mod_screen_symbols.h
  ${PXT_MODULES_PATH}/mod_scroll/mod_scroll.c
  ${PXT_MODULES_PATH}/mod_scroll/mod_scroll_symbols.h
  ${PXT_MODULES_PATH}/mod_sort/mod_sort.c
  ${PXT_MODULES_PATH}/mod_sort/mod_sort_symbols.h
  ${PXT_MODULES_PATH}/mod_sound/mod_sound.c
  ${PXT_MODULES_PATH}/mod_sound/mod_sound.h
  ${PXT_MODULES_PATH}/mod_sound/mod_sound_symbols.h
  ${PXT_MODULES_PATH}/mod_string/mod_string.c
  ${PXT_MODULES_PATH}/mod_string/mod_string_symbols.h
  ${PXT_MODULES_PATH}/mod_sys/mod_sys.c
  ${PXT_MODULES_PATH}/mod_sys/mod_sys.h
  ${PXT_MODULES_PATH}/mod_sys/mod_sys_symbols.h
  ${PXT_MODULES_PATH}/mod_text/mod_text.c
  ${PXT_MODULES_PATH}/mod_text/mod_text_symbols.h
  ${PXT_MODULES_PATH}/mod_time/mod_time.c
  ${PXT_MODULES_PATH}/mod_time/mod_time_symbols.h
  ${PXT_MODULES_PATH}/mod_timers/mod_timers.c
  ${PXT_MODULES_PATH}/mod_timers/mod_timers_symbols.h
  ${PXT_MODULES_PATH}/mod_video/mod_video.c
  ${PXT_MODULES_PATH}/mod_video/mod_video_symbols.h
  ${PXT_MODULES_PATH}/mod_wm/locale/get_locale.h
  ${PXT_MODULES_PATH}/mod_wm/mod_wm.c
  ${PXT_MODULES_PATH}/mod_wm/mod_wm_symbols.h
  )

# OS-specific files
if(WIN32)
    list(APPEND SOURCE_FILES
         ${PXT_MODULES_PATH}/mod_wm/locale/win32.c)
elseif(APPLE)
    list(APPEND SOURCE_FILES
         ${PXT_MODULES_PATH}/mod_wm/locale/darwin.m)
else()
    list(APPEND SOURCE_FILES
         ${PXT_MODULES_PATH}/mod_wm/locale/env.c)
endif()

# Optional modules
include(optional_modules_includes)

# Include dirs
include_directories(${PXT_CORE_PATH}/pxtrtm/include
                    ${PXT_CORE_PATH}/include
                    ${PXT_MODULES_PATH}/libbgload/
                    ${PXT_MODULES_PATH}/mod_say/
                    ${PXT_MODULES_PATH}/mod_string/
                    ${PXT_MODULES_PATH}/mod_math/
                    ${PXT_MODULES_PATH}/mod_mem/
                    ${PXT_MODULES_PATH}/mod_time/
                    ${PXT_MODULES_PATH}/mod_file/
                    ${PXT_MODULES_PATH}/mod_sound/
                    ${PXT_MODULES_PATH}/libsdlhandler/
                    ${PXT_MODULES_PATH}/mod_gamecontroller/
                    ${PXT_MODULES_PATH}/mod_joy/
                    ${PXT_MODULES_PATH}/libjoy/
                    ${PXT_MODULES_PATH}/libkey/
                    ${PXT_MODULES_PATH}/mod_key/
                    ${PXT_MODULES_PATH}/mod_proc/
                    ${PXT_MODULES_PATH}/mod_sort/
                    ${PXT_MODULES_PATH}/mod_timers/
                    ${PXT_MODULES_PATH}/libgrbase/
                    ${PXT_MODULES_PATH}/libblit/
                    ${PXT_MODULES_PATH}/libvideo/
                    ${PXT_MODULES_PATH}/librender/
                    ${PXT_MODULES_PATH}/mod_video/
                    ${PXT_MODULES_PATH}/libmouse/
                    ${PXT_MODULES_PATH}/mod_mouse/
                    ${PXT_MODULES_PATH}/mod_map/
                    ${PXT_MODULES_PATH}/libfont/
                    ${PXT_MODULES_PATH}/mod_dir/
                    ${PXT_MODULES_PATH}/libtext/
                    ${PXT_MODULES_PATH}/mod_text/
                    ${PXT_MODULES_PATH}/mod_rand/
                    ${PXT_MODULES_PATH}/mod_grproc/
                    ${PXT_MODULES_PATH}/libscroll/
                    ${PXT_MODULES_PATH}/mod_scroll/
                    ${PXT_MODULES_PATH}/libdraw/
                    ${PXT_MODULES_PATH}/mod_draw/
                    ${PXT_MODULES_PATH}/mod_screen/
                    ${PXT_MODULES_PATH}/mod_path/
                    ${PXT_MODULES_PATH}/libwm/
                    ${PXT_MODULES_PATH}/mod_wm/
                    ${PXT_MODULES_PATH}/mod_sys/
                    ${PXT_MODULES_PATH}/mod_ttf/
                    ${PXT_3RDPARTY}/stb/
                    ${FREETYPE_INCLUDE_DIRS}
                    ${SDL2_INCLUDE_DIR}
                    ${SDL2_MIXER_INCLUDE_DIRS}
                    ${ZLIB_INCLUDE_DIRS}
                    ${VORBIS_INCLUDE_DIR}
                    ${OPENAL_INCLUDE_DIR}
                    ${PNG_INCLUDE_DIR}
                    ${JPEG_INCLUDE_DIR}
                    ${WEBP_INCLUDE_DIR}
                    ${OPENGLES2_INCLUDE_DIR}
                    ${CHIPMUNK_INCLUDE_DIR})

# Main executable
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Include the compiler flags from the external include file
include(compiler_flags)

