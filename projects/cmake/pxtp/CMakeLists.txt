project(pxtp C)
cmake_minimum_required(VERSION 3.4)
set(C_PXTP 1)

# Require pxtrtm
add_subdirectory(pxtrtm)

# Required stuff
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${pxtp_SOURCE_DIR}/../include")
set(PXT_MODULES_PATH "${pxtp_SOURCE_DIR}/../../../modules")
set(PXT_3RDPARTY "${pxtp_SOURCE_DIR}/../../../3rdparty")
set(PXT_CORE_PATH "${pxtp_SOURCE_DIR}/../../../core")
include(optional_modules)
include(do_find_libs)

# Preprocessor macros
add_definitions(-D__PXTP__)

# Common defines
include(common_defs)

# Source files
set(SOURCE_FILES
  ${PXT_CORE_PATH}/pxtp/include/pxtp.h
  ${PXT_CORE_PATH}/pxtp/src/main.c)
  
# Include dirs
include_directories(${PXT_CORE_PATH}/pxtp/include
                    ${PXT_CORE_PATH}/include
                    ${PXT_CORE_PATH}/pxtrtm/include/)

if(WIN32)
    set(EXTRA_LIBS "-lshlwapi -lwsock32 -lm")
	set(SOURCE_FILES
      ${SOURCE_FILES}
      ${pxtp_SOURCE_DIR}/pxtp.rc)
else()
    set(EXTRA_LIBS "-lm")
endif()

# Main executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Optional libraries
if(NOT NO_MODCURL)
    set(CURL_LIBRARY ${CURL_LIBRARY})
else()
    set(CURL_LIBRARY "")
endif()
if(NOT NO_MODSTEAM)
    set(STEAM_LIB ${STEAMWORKS_LIBRARY})
else()
    set(STEAM_LIB "")
endif()
if(NO_MODTHEORA)
    set(THEORA_LIBRARIES "")
	set(OPENAL_LIBRARY "")
endif(NO_MODTHEORA)
if(NO_MODREGEX)
    set(TRE_LIBRARY "")
endif(NO_MODREGEX)

# Include the compiler flags from the external include file
include(compiler_flags)

# Link the executable to the libraries
target_link_libraries(${PROJECT_NAME}
                      pxtrtm
                      ${SDL2_LIBRARY}
                      ${SDL2_MIXER_LIBRARIES}
                      ${ZLIB_LIBRARIES}
                      ${PNG_LIBRARIES}
                      ${JPEG_LIBRARIES}
                      ${WEBP_LIBRARY}
                      ${OGG_LIBRARY}
                      ${VORBIS_LIBRARY}
                      ${FREETYPE_LIBRARIES}
                      ${EXTRA_LIBS}
                      ${OPENAL_LIBRARY}
					  ${TRE_LIBRARY}
					  ${CURL_LIBRARY}
					  ${STEAM_LIB}
					  ${THEORA_LIBRARIES})

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