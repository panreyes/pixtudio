set(CMAKE_CONFIGURATION_TYPES "Release;Debug;MinSizeRel;RelWithDebInfo")
project(libogg C)
cmake_minimum_required(VERSION 3.4)

set(SOURCE_FILES
    src/framing.c
    src/bitwise.c)
set(INCLUDE_FILES
    include/ogg/config_types.h
    include/ogg/ogg.h
    include/ogg/os_types.h)

include_directories(${libogg_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Define installation dirs for libs and headers (if not provided)
if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
	set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH "Installation directory for libs")
endif(NOT DEFINED CMAKE_INSTALL_LIBDIR)
if(NOT DEFINED CMAKE_INSTALL_INCDIR)
    set(CMAKE_INSTALL_INCDIR "${CMAKE_INSTALL_PREFIX}/include/ogg" CACHE PATH "Installation directory for libtheora headers")
endif(NOT DEFINED CMAKE_INSTALL_INCDIR)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCDIR})