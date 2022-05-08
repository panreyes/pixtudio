project(pxtb C)
cmake_minimum_required(VERSION 3.4)
set(C_PXTB 1)

# Required stuff
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${pxtb_SOURCE_DIR}/../include")
set(PXT_MODULES_PATH "${pxtb_SOURCE_DIR}/../../../modules")
set(PXT_3RDPARTY "${pxtb_SOURCE_DIR}/../../../3rdparty")
set(PXT_CORE_PATH "${pxtb_SOURCE_DIR}/../../../core")
include(optional_modules)
include(do_find_libs)

# Preprocessor macros
add_definitions(-D__PXTB__)

# Common defines
include(common_defs)

# Source files
file(GLOB SOURCE_FILES
  ${PXT_CORE_PATH}/pxtb/src/*.c
  ${PXT_CORE_PATH}/common/debug.c
  ${PXT_CORE_PATH}/common/files.c
  ${PXT_CORE_PATH}/common/xctype.c
  ${PXT_CORE_PATH}/common/commons_defs.h
  ${PXT_CORE_PATH}/common/dirs.h
  ${PXT_CORE_PATH}/pxtb/include/codeblock.h
  ${PXT_CORE_PATH}/pxtb/include/compiler.h
  ${PXT_CORE_PATH}/pxtb/include/constants.h
  ${PXT_CORE_PATH}/pxtb/include/errors.h
  ${PXT_CORE_PATH}/pxtb/include/errors_st.h
  ${PXT_CORE_PATH}/pxtb/include/identifiers.h
  ${PXT_CORE_PATH}/pxtb/include/messages.h
  ${PXT_CORE_PATH}/pxtb/include/procdef.h
  ${PXT_CORE_PATH}/pxtb/include/pxtb.h
  ${PXT_CORE_PATH}/pxtb/include/segment.h
  ${PXT_CORE_PATH}/pxtb/include/token.h
  ${PXT_CORE_PATH}/pxtb/include/varspace.h
  ${PXT_CORE_PATH}/pxtb/include/procdef.h
  ${PXT_CORE_PATH}/include/pxtdl.h
  ${PXT_CORE_PATH}/include/loadlib.h
  ${PXT_CORE_PATH}/include/files.h
  ${PXT_CORE_PATH}/include/monolithic_includes.h)
  
# Include dirs
include_directories(${PXT_CORE_PATH}/pxtb/include
                    ${PXT_CORE_PATH}/include
                    ${pxtb_SOURCE_DIR}/../../../modules/libbgload/
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
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_shader/
                    ${pxtb_SOURCE_DIR}/../../../modules/mod_chipmunk/
                    ${SDL2_INCLUDE_DIR}
                    ${ZLIB_INCLUDE_DIRS})

# Optional modules
include(optional_modules_includes)
    
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