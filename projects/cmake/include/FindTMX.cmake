# Locate TMX
# This module defines XXX_FOUND, XXX_INCLUDE_DIRS and XXX_LIBRARIES standard variables
#
# $TMXDIR is an environment variable that would
# correspond to the ./configure --prefix=$TMXDIR
# used in building TMX.

SET(TMX_SEARCH_PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw # Fink
    /opt/local # DarwinPorts
    /opt/csw # Blastwave
    /opt
	${TMX_PATH}
	${TMX_PATH}/src
    $ENV{TMXDIR}
)

FIND_PATH(TMX_INCLUDE_DIR
    NAMES tmx.h
    PATHS ${TMX_SEARCH_PATHS}
)

FIND_LIBRARY(TMX_LIBRARY
    NAMES libtmx
    PATHS ${TMX_SEARCH_PATHS}
)

IF(TMX_LIBRARY)
    SET(TMX_LIBRARIES "${TMX_LIBRARY}")     # Could add "general" keyword, but it is optional
ENDIF()

# handle the QUIETLY and REQUIRED arguments and set XXX_FOUND to TRUE if all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TMX DEFAULT_MSG TMX_LIBRARIES TMX_INCLUDE_DIR)
