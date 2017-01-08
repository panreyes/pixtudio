set(CMAKE_CONFIGURATION_TYPES "Release;Debug;MinSizeRel;RelWithDebInfo")
project(libvorbis C)
cmake_minimum_required(VERSION 3.4)

set(SOURCE_FILES
    lib/vorbisfile.c
    lib/mdct.c
    lib/smallft.c
    lib/block.c
    lib/envelope.c
    lib/window.c
    lib/lsp.c
    lib/lpc.c
    lib/analysis.c
    lib/synthesis.c
    lib/psy.c
    lib/info.c
    lib/floor1.c
    lib/floor0.c
    lib/res0.c
    lib/mapping0.c
    lib/registry.c
    lib/codebook.c
    lib/sharedbook.c
    lib/lookup.c
    lib/bitrate.c)
set(INCLUDE_FILES
    include/vorbis/codec.h
    include/vorbis/vorbisenc.h
    include/vorbis/vorbisfile.h)

if(MSVC)
    set(CMAKE_C_FLAGS "/wd4996 ${CMAKE_C_FLAGS}" CACHE STRING "" FORCE)
endif(MSVC)

include_directories(${libvorbis_SOURCE_DIR}/include ${LIBOGG_PATH}/include)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Define installation dirs for libs and headers (if not provided)
if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
	set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH "Installation directory for libs")
endif(NOT DEFINED CMAKE_INSTALL_LIBDIR)
if(NOT DEFINED CMAKE_INSTALL_INCDIR)
    set(CMAKE_INSTALL_INCDIR "${CMAKE_INSTALL_PREFIX}/include/vorbis" CACHE PATH "Installation directory for libtheora headers")
endif(NOT DEFINED CMAKE_INSTALL_INCDIR)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCDIR})
