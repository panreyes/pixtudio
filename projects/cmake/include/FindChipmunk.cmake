# Locate CHIPMUNK
# This module defines XXX_FOUND, XXX_INCLUDE_DIRS and XXX_LIBRARIES standard variables
#
# $CHIPMUNKDIR is an environment variable that would
# correspond to the ./configure --prefix=$CHIPMUNKDIR
# used in building libCHIPMUNK.

SET(CHIPMUNK_SEARCH_PATHS
    ${PXT_3RDPARTY}/Chipmunk-6.1.3
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw # Fink
    /opt/local # DarwinPorts
    /opt/csw # Blastwave
    /opt
)

FIND_PATH(CHIPMUNK_INCLUDE_DIR
    NAMES chipmunk.h
    HINTS
	${PXT_3RDPARTY}/Chipmunk-6.1.3/include/chipmunk
    $ENV{CHIPMUNKDIR}
    $ENV{CHIPMUNK_PATH}
    PATH_SUFFIXES include chipmunk 
    PATHS ${CHIPMUNK_SEARCH_PATHS}
)

FIND_LIBRARY(CHIPMUNK_LIBRARY
    NAMES CHIPMUNK chipmunk
    HINTS
	${PXT_3RDPARTY}/Chipmunk-6.1.3/build/win32
    $ENV{CHIPMUNKDIR}
    $ENV{CHIPMUNK_PATH}
    PATH_SUFFIXES lib lib64 lib/i386-linux-gnu win32/CHIPMUNK_Dynamic_Release "Win32/${MSVC_YEAR_NAME}/x64/Release" "Win32/${MSVC_YEAR_NAME}/Win32/Release"
    PATHS ${CHIPMUNK_SEARCH_PATHS}
)

IF(CHIPMUNK_LIBRARY)
    SET(CHIPMUNK_LIBRARIES "${CHIPMUNK_LIBRARY}")       # Could add "general" keyword, but it is optional
ENDIF()

# handle the QUIETLY and REQUIRED arguments and set XXX_FOUND to TRUE if all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CHIPMUNK DEFAULT_MSG CHIPMUNK_LIBRARIES CHIPMUNK_INCLUDE_DIR)
