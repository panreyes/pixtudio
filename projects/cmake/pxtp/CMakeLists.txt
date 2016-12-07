project(pxtp C)
cmake_minimum_required(VERSION 3.4)
# Require pxtrtm
add_subdirectory(pxtrtm)
# Required stuff
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${pxtp_SOURCE_DIR}/../include")
find_package(SDL2 2.0.4 REQUIRED)
find_package(SDL2_Mixer REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)
find_package(OGG REQUIRED)
find_package(Vorbis REQUIRED)
find_package(Theora REQUIRED)
find_package(Freetype REQUIRED)
find_package(OpenAL REQUIRED)
find_package(TRE REQUIRED)
find_package(CURL REQUIRED)
find_package(STEAMWORKS)
# Preprocessor macros
add_definitions(-D__PXTP__)
include(common_defs)
# Source files
set(SOURCE_FILES
  ${pxtp_SOURCE_DIR}/../../../core/pxtp/include/pxtp.h
  ${pxtp_SOURCE_DIR}/../../../core/pxtp/src/main.c)
# Include dirs
include_directories(${pxtp_SOURCE_DIR}/../../../core/pxtp/include
                    ${pxtp_SOURCE_DIR}/../../../core/include
                    ${pxtp_SOURCE_DIR}/../../../core/pxtrtm/include/)

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

# Steamworks libraries
if(STEAMWORKS_FOUND)
    set(STEAM_LIB ${STEAMWORKS_LIBRARY})
else()
    set(STEAM_LIB "")
endif()

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
                      ${OGG_LIBRARY}
                      ${VORBIS_LIBRARY}
                      ${THEORA_LIBRARIES}
                      ${FREETYPE_LIBRARIES}
                      ${OPENAL_LIBRARY}
                      ${TRE_LIBRARY}
                      ${CURL_LIBRARY}
                      ${EXTRA_LIBS}
                      ${STEAM_LIB})

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