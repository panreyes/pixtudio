set(CMAKE_CONFIGURATION_TYPES "Release;Debug;MinSizeRel;RelWithDebInfo")
project(libtre C)
cmake_minimum_required(VERSION 3.4)

set(SOURCE_FILES
    lib/tre-ast.c
    lib/tre-compile.c
    lib/tre-match-backtrack.c
    lib/tre-match-parallel.c
    lib/tre-mem.c
    lib/tre-parse.c
    lib/tre-stack.c
    lib/regcomp.c
    lib/regexec.c
    lib/regerror.c
    lib/tre-match-approx.c)

add_definitions(-DHAVE_CONFIG_H)

if (MSVC)
    message("MSVC")
    include_directories(${libtre_SOURCE_DIR}/win32 ${libtre_SOURCE_DIR}/lib ${libtre_SOURCE_DIR}/lib/tre)
else(MSVC)
    include_directories(${libtre_SOURCE_DIR} ${libtre_SOURCE_DIR}/lib ${libtre_SOURCE_DIR}/lib/tre)
endif(MSVC)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
    set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH "Installation directory for libs")
endif(NOT DEFINED CMAKE_INSTALL_LIBDIR)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})