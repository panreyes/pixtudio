project(pxtb C)
cmake_minimum_required(VERSION 3.4)
# Required stuff
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${pxtb_SOURCE_DIR}/../include")
find_package(SDL2 REQUIRED)     # We need the SDL_gamecontroller symbols, but we don't link against SDL2
find_package(ZLIB REQUIRED)
find_package(STEAMWORKS)
find_package(CURL)              # We need some symbols, but we don't link against libcurl
# Preprocessor macros
add_definitions(-D__PXTB__)

# Determine if optional libraries should be built in or not
if(NOT STEAMWORKS_FOUND)
  add_definitions(-DNO_MODSTEAM)
endif(NOT STEAMWORKS_FOUND)
if(NOT CURL_FOUND)
  add_definitions(-DNO_MODCURL)
endif(NOT CURL_FOUND)

# Common defines
include(common_defs)

# Source files
file(GLOB SOURCE_FILES
  ${pxtb_SOURCE_DIR}/../../../core/pxtb/src/*.c
  ${pxtb_SOURCE_DIR}/../../../core/common/debug.c
  ${pxtb_SOURCE_DIR}/../../../core/common/files.c
  ${pxtb_SOURCE_DIR}/../../../core/common/xctype.c
  ${pxtb_SOURCE_DIR}/../../../core/common/commons_defs.h
  ${pxtb_SOURCE_DIR}/../../../core/common/dirs.h
  ${pxtb_SOURCE_DIR}/../../../core/pxtb/include/codeblock.h
  ${pxtb_SOURCE_DIR}/../../../core/pxtb/include/compiler.h
  ${pxtb_SOURCE_DIR}/../../../core/pxtb/include/constants.h
  ${pxtb_SOURCE_DIR}/../../../core/pxtb/include/errors.h
  ${pxtb_SOURCE_DIR}/../../../core/pxtb/include/errors_st.h
  ${pxtb_SOURCE_DIR}/../../../core/pxtb/include/identifiers.h
  ${pxtb_SOURCE_DIR}/../../../core/pxtb/include/messages.h
  ${pxtb_SOURCE_DIR}/../../../core/pxtb/include/procdef.h
  ${pxtb_SOURCE_DIR}/../../../core/pxtb/include/pxtb.h
  ${pxtb_SOURCE_DIR}/../../../core/pxtb/include/segment.h
  ${pxtb_SOURCE_DIR}/../../../core/pxtb/include/token.h
  ${pxtb_SOURCE_DIR}/../../../core/pxtb/include/varspace.h
  ${pxtb_SOURCE_DIR}/../../../core/pxtb/include/procdef.h
  ${pxtb_SOURCE_DIR}/../../../core/include/pxtdl.h
  ${pxtb_SOURCE_DIR}/../../../core/include/loadlib.h
  ${pxtb_SOURCE_DIR}/../../../core/include/monolithic_includes.h)
# Include dirs
include_directories(${pxtb_SOURCE_DIR}/../../../core/pxtb/include
                    ${pxtb_SOURCE_DIR}/../../../core/include
                    ${pxtb_SOURCE_DIR}/../../../modules/libbgload/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_debug/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_say/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_string/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_math/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_mem/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_time/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_file/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_sound/
                    ${pxtb_SOURCE_DIR}/../../../modules/libsdlhandler/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_gamecontroller/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_joy/
                    ${pxtb_SOURCE_DIR}/../../../modules/libjoy/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_theora/
                    ${pxtb_SOURCE_DIR}/../../../modules/libkey/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_key/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_proc/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_sort/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_timers/
                    ${pxtb_SOURCE_DIR}/../../../modules/libgrbase/
                    ${pxtb_SOURCE_DIR}/../../../modules/libblit/
                    ${pxtb_SOURCE_DIR}/../../../modules/libvideo/
                    ${pxtb_SOURCE_DIR}/../../../modules/librender/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_video/
                    ${pxtb_SOURCE_DIR}/../../../modules/libmouse/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_mouse/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_multi/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_map/
                    ${pxtb_SOURCE_DIR}/../../../modules/libfont/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_dir/
                    ${pxtb_SOURCE_DIR}/../../../modules/libtext/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_text/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_rand/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_grproc/
                    ${pxtb_SOURCE_DIR}/../../../modules/libscroll/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_scroll/
                    ${pxtb_SOURCE_DIR}/../../../modules/libdraw/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_draw/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_screen/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_path/
                    ${pxtb_SOURCE_DIR}/../../../modules/libwm/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_wm/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_sys/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_steam/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_regex/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_fsock/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_effects/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_curl/
                    ${SDL2_INCLUDE_DIR}
                    ${ZLIB_INCLUDE_DIRS})

# Add CURL include dir, if mod_curl is to be built
if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
endif(CURL_FOUND)

# In windows? Add an icon and link agains shlwapi
if(WIN32)
	set(SOURCE_FILES
        ${SOURCE_FILES}
        ${pxtb_SOURCE_DIR}/pxtb.rc)
    set(EXTRA_LIBS "shlwapi")
else()
    set(EXTRA_LIBS)
endif()

# Main executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Include the compiler flags from the external include file
include(compiler_flags)

# Link the executable to the libraries
target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES} ${EXTRA_LIBS})

# Installation instructions
if(WIN32)
    set(INSTALL_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin/win32" CACHE PATH "Installation directory for executables")
elseif(APPLE)
    set(INSTALL_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin/osx32" CACHE PATH "Installation directory for executables")
else()
    set(INSTALL_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin/gnulinux32" CACHE PATH "Installation directory for executables")
endif()
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}")