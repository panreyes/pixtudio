project(pxtb C)
cmake_minimum_required(VERSION 2.8)
# Required stuff
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${pxtb_SOURCE_DIR}/../cmake")
find_package(SDL2 REQUIRED)     # We need the SDL_gamecontroller symbols, but we don't link against SDL2
find_package(ZLIB REQUIRED)
# Preprocessor macros
add_definitions(-D__PXTB__)
add_definitions(-D__MONOLITHIC__)
add_definitions(-DNO_MODCHIPMUNK)
add_definitions(-DNO_MODICONV)
add_definitions(-DVERSION="1.0.0")
# Source files
file(GLOB SOURCE_FILES
  ${pxtb_SOURCE_DIR}/../../../core/pxtb/src/*.c
  ${pxtb_SOURCE_DIR}/../../../core/common/debug.c
  ${pxtb_SOURCE_DIR}/../../../core/common/files.c
  ${pxtb_SOURCE_DIR}/../../../core/common/xctype.c
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
  ${pxtb_SOURCE_DIR}/../../../core/include/bgddl.h
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
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_regex/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_fsock/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_effects/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_curl/
                    ${SDL2_INCLUDE_DIR}
                    ${ZLIB_INCLUDE_DIRS})
# Main executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
if(WIN32)
    set(EXTRA_LIBS "-lshlwapi")
else()
    set(EXTRA_LIBS)
endif()
# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_C_COMPILER_ID} STREQUAL "GNU" OR
    ${CMAKE_C_COMPILER_ID} STREQUAL "Clang" OR
    ${CMAKE_C_COMPILER_ID} STREQUAL "AppleClang")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wshadow")
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG} -g")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE} -O2")
elseif (${CMAKE_C_COMPILER_ID} STREQUAL "MSVC")
        if (CMAKE_C_FLAGS MATCHES "/W[0-4]")
                string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
        else()
                set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
        endif()
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES} ${EXTRA_LIBS})
