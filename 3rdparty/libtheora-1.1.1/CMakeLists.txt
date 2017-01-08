set(CMAKE_CONFIGURATION_TYPES "Release;Debug;MinSizeRel;RelWithDebInfo")
project(libtheora C)
cmake_minimum_required(VERSION 3.4)

# TODO: We should be properly checking for libogg

set(SOURCE_FILES
    lib/apiwrapper.c
    lib/bitpack.c
    lib/decapiwrapper.c
    lib/decinfo.c
    lib/decode.c
    lib/dequant.c
    lib/fragment.c
    lib/huffdec.c
    lib/idct.c
    lib/info.c
    lib/internal.c
    lib/quant.c
    lib/state.c
    lib/encoder_disabled.c)
set(INCLUDE_FILES
    include/theora/codec.h
    include/theora/theora.h
    include/theora/theoradec.h
    include/theora/theoraenc.h)

include_directories(${libtheora_SOURCE_DIR}/include ${LIBOGG_PATH}/include)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Define installation dirs for libs and headers (if not provided)
if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
	set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH "Installation directory for libs")
endif(NOT DEFINED CMAKE_INSTALL_LIBDIR)
if(NOT DEFINED CMAKE_INSTALL_INCDIR)
    set(CMAKE_INSTALL_INCDIR "${CMAKE_INSTALL_PREFIX}/include/theora" CACHE PATH "Installation directory for libtheora headers")
endif(NOT DEFINED CMAKE_INSTALL_INCDIR)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCDIR})