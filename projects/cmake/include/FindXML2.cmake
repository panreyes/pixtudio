# Locate XML2
# This module defines XXX_FOUND, XXX_INCLUDE_DIRS and XXX_LIBRARIES standard variables
#
# $XML2DIR is an environment variable that would
# correspond to the ./configure --prefix=$XML2DIR
# used in building XML2.

SET(XML2_SEARCH_PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw # Fink
    /opt/local # DarwinPorts
    /opt/csw # Blastwave
    /opt
	${XML2_PATH}
	${XML2_PATH}/src
    $ENV{XML2DIR}
)

FIND_PATH(XML2_INCLUDE_DIR
    NAMES xml2.h
	HINT include
    PATHS ${XML2_SEARCH_PATHS}
)

FIND_LIBRARY(XML2_LIBRARY
    NAMES libxml2
    PATHS ${XML2_SEARCH_PATHS}
)

IF(XML2_LIBRARY)
    SET(XML2_LIBRARIES "${XML2_LIBRARY}")     # Could add "general" keyword, but it is optional
ENDIF()

# handle the QUIETLY and REQUIRED arguments and set XXX_FOUND to TRUE if all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(XML2 DEFAULT_MSG XML2_LIBRARIES XML2_INCLUDE_DIR)
