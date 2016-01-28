project(pxtp C)
cmake_minimum_required(VERSION 2.8)
# Require bgdrtm
add_subdirectory(bgdrtm)
# Required stuff
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${pxtp_SOURCE_DIR}/../include")
find_package(SDL2 2.0.4 REQUIRED)
find_package(SDL2_Mixer REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
find_package(OGG REQUIRED)
find_package(Vorbis REQUIRED)
find_package(Theora REQUIRED)
find_package(Freetype REQUIRED)
find_package(OpenAL REQUIRED)
# Preprocessor macros
add_definitions(-D__PXTP__)
include(common_defs)
# Source files
set(SOURCE_FILES
  ${pxtp_SOURCE_DIR}/../../../core/pxtp/src/main.c)
# Include dirs
include_directories(${pxtp_SOURCE_DIR}/../../../core/pxtp/include
                    ${pxtp_SOURCE_DIR}/../../../core/include
                    ${pxtp_SOURCE_DIR}/../../../core/bgdrtm/include/)
# Main executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
if(WIN32)
    set(EXTRA_LIBS "-lshlwapi -lwsock32 -lm")
else()
    set(EXTRA_LIBS "-lm")
endif()

# Include the compiler flags from the external include file
include(compiler_flags)

# Link the executable to the libraries
target_link_libraries(${PROJECT_NAME}
                      bgdrtm
                      ${SDL2_LIBRARY}
                      ${SDL2_MIXER_LIBRARIES}
                      ${ZLIB_LIBRARIES}
                      ${PNG_LIBRARIES}
                      ${OGG_LIBRARY}
                      ${VORBIS_LIBRARY}
                      ${THEORA_LIBRARY}
                      ${FREETYPE_LIBRARIES}
                      ${OPENAL_LIBRARY}
                      ${EXTRA_LIBS})

