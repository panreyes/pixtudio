# Locate EPICSDK
# This module defines XXX_FOUND, XXX_INCLUDE_DIRS and XXX_LIBRARIES standard variables
#
# $EPICSDKDIR is an environment variable that would
# correspond to the ./configure --prefix=$EPICSDKDIR
# used in building EPICSDK.

SET(EPICSDK_SEARCH_PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw # Fink
    /opt/local # DarwinPorts
    /opt/csw # Blastwave
    /opt
    ${EPICSDK_PATH}/Include
	${EPICSDK_PATH}/Lib
    $ENV{EPICSDKDIR}/Include
	$ENV{EPICSDKDIR}/Lib
)

SET(MSVC_YEAR_NAME)
IF (MSVC_VERSION GREATER 1599)      # >= 1600
    SET(MSVC_YEAR_NAME VS2010)
ELSEIF(MSVC_VERSION GREATER 1499)   # >= 1500
    SET(MSVC_YEAR_NAME VS2008)
ELSEIF(MSVC_VERSION GREATER 1399)   # >= 1400
    SET(MSVC_YEAR_NAME VS2005)
ELSEIF(MSVC_VERSION GREATER 1299)   # >= 1300
    SET(MSVC_YEAR_NAME VS2003)
ELSEIF(MSVC_VERSION GREATER 1199)   # >= 1200
    SET(MSVC_YEAR_NAME VS6)
ENDIF()

FIND_PATH(EPICSDK_INCLUDE_DIR
    NAMES eos_sdk.h
    HINTS ENV EPICSDKDIR
    PATHS ${EPICSDK_SEARCH_PATHS}
)

FIND_LIBRARY(EPICSDK_LIBRARY
    NAMES EOSSDK-Win32-Shipping
    HINTS ENV EPICSDKDIR
    PATHS ${EPICSDK_SEARCH_PATHS}
)

IF(EPICSDK_LIBRARY)
    SET(EPICSDK_LIBRARIES "${EPICSDK_LIBRARY}")     # Could add "general" keyword, but it is optional
ENDIF()

# handle the QUIETLY and REQUIRED arguments and set XXX_FOUND to TRUE if all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(EPICSDK DEFAULT_MSG EPICSDK_LIBRARIES EPICSDK_INCLUDE_DIR)
