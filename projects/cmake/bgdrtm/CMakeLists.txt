project(bgdrtm C)
cmake_minimum_required(VERSION 2.8)
# Required stuff
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${bgdrtm_SOURCE_DIR}/../include")
find_package(SDL2 2.0.4 REQUIRED)
find_package(SDL2_Mixer REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
find_package(Vorbis REQUIRED)
find_package(Freetype REQUIRED)
# Preprocessor macros
add_definitions(-D__BGDRTM__)
include(common_defs)
# Source files
set(SOURCE_FILES
  ${bgdrtm_SOURCE_DIR}/../../../core/bgdrtm/src/copy.c
  ${bgdrtm_SOURCE_DIR}/../../../core/bgdrtm/src/dcbr.c
  ${bgdrtm_SOURCE_DIR}/../../../core/bgdrtm/src/dirs.c
  ${bgdrtm_SOURCE_DIR}/../../../core/bgdrtm/src/instance.c
  ${bgdrtm_SOURCE_DIR}/../../../core/bgdrtm/src/interpreter.c
  ${bgdrtm_SOURCE_DIR}/../../../core/bgdrtm/src/misc.c
  ${bgdrtm_SOURCE_DIR}/../../../core/bgdrtm/src/strings.c
  ${bgdrtm_SOURCE_DIR}/../../../core/bgdrtm/src/sysprocs.c
  ${bgdrtm_SOURCE_DIR}/../../../core/bgdrtm/src/varspace_file.c
  ${bgdrtm_SOURCE_DIR}/../../../core/bgdrtm/src/fmath.c
  ${bgdrtm_SOURCE_DIR}/../../../core/common/debug.c
  ${bgdrtm_SOURCE_DIR}/../../../core/common/files.c
  ${bgdrtm_SOURCE_DIR}/../../../core/common/xctype.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libbgload/bgload.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_debug/mod_debug.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_say/mod_say.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_string/mod_string.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_math/mod_math.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_mem/mod_mem.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_time/mod_time.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_file/mod_file.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_sound/mod_sound.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libsdlhandler/libsdlhandler.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_gamecontroller/mod_gamecontroller.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_joy/mod_joy.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libjoy/libjoy.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_theora/mod_theora.c
  ${bgdrtm_SOURCE_DIR}/../../../3rdparty/theoraplay/theoraplay.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libkey/libkey.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_key/mod_key.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_proc/mod_proc.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_sort/mod_sort.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_timers/mod_timers.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libgrbase/g_bitmap.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libgrbase/g_clear.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libgrbase/g_grlib.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libgrbase/g_pal.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libgrbase/g_blendop.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libgrbase/g_conversion.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libgrbase/libgrbase.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libblit/g_blit.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libblit/g_pixel.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libvideo/g_regions.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libvideo/g_video.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/librender/g_fade.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/librender/g_frame.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/librender/g_instance.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/librender/g_object.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/librender/g_rects.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/librender/g_screen.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/librender/librender.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_video/mod_video.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libmouse/libmouse.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_multi/mod_multi.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_map/file_fnt.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_map/file_fpg.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_map/file_map.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_map/file_pal.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_map/file_pcx.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_map/file_png.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_map/mod_map.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libfont/libfont.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_dir/mod_dir.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libtext/libtext.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_text/mod_text.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_rand/mod_rand.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_grproc/mod_grproc.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libscroll/libscroll.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_scroll/mod_scroll.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libdraw/libdraw.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_draw/mod_draw.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_screen/mod_screen.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_path/mod_path.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libwm/libwm.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_wm/mod_wm.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_sys/mod_sys.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_regex/mod_regex.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/libsocket/libsocket.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_fsock/mod_fsock.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_effects/mod_effects.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_curl/mod_curl.c
  ${bgdrtm_SOURCE_DIR}/../../../modules/mod_ttf/mod_ttf.c)

# OS-specific files
if(WIN32)
    list(APPEND SOURCE_FILES
         ${bgdrtm_SOURCE_DIR}/../../../modules/mod_wm/locale/win32.c)
elseif(DARWIN)
    list(APPEND SOURCE_FILES
         ${bgdrtm_SOURCE_DIR}/../../../modules/mod_wm/locale/darwin.m)
else()
    list(APPEND SOURCE_FILES
         ${bgdrtm_SOURCE_DIR}/../../../modules/mod_wm/locale/env.c)
endif()

# Include dirs
include_directories(${bgdrtm_SOURCE_DIR}/../../../core/bgdrtm/include
                    ${bgdrtm_SOURCE_DIR}/../../../core/include
                    ${bgdrtm_SOURCE_DIR}/../../../modules/libbgload/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_debug/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_say/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_string/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_math/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_mem/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_time/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_file/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_sound/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/libsdlhandler/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_gamecontroller/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_joy/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/libjoy/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_theora/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/libkey/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_key/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_proc/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_sort/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_timers/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/libgrbase/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/libblit/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/libvideo/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/librender/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_video/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/libmouse/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_mouse/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_multi/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_map/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/libfont/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_dir/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/libtext/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_text/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_rand/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_grproc/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/libscroll/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_scroll/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/libdraw/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_draw/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_screen/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_path/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/libwm/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_wm/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_sys/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_regex/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_fsock/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_effects/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_curl/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/libsocket/
                    ${bgdrtm_SOURCE_DIR}/../../../modules/mod_ttf/
                    ${bgdrtm_SOURCE_DIR}/../../../3rdparty/stb/
                    ${bgdrtm_SOURCE_DIR}/../../../3rdparty/theoraplay/
                    ${SDL2_INCLUDE_DIR}
                    ${SDL2_MIXER_INCLUDE_DIRS}
                    ${ZLIB_INCLUDE_DIRS}
                    ${VORBIS_INCLUDE_DIR}
                    ${FREETYPE_INCLUDE_DIRS})
# Main executable
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Include the compiler flags from the external include file
include(compiler_flags)
