# Locate STEAMWORKS
# This module defines XXX_FOUND, XXX_INCLUDE_DIRS and XXX_LIBRARIES standard variables
#
# $STEAMWORKSDIR is an environment variable that would
# correspond to the ./configure --prefix=$STEAMWORKSDIR
# used in building STEAMWORKS.

SET(STEAMWORKS_SEARCH_PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw # Fink
    /opt/local # DarwinPorts
    /opt/csw # Blastwave
    /opt
    ${STEAMWORKS_PATH}/public/steam
    $ENV{STEAMWORKSDIR}/public/steam
)

if(WIN32)
    list(APPEND STEAMWORKS_SEARCH_PATHS
         ${STEAMWORKS_PATH}/redistributable_bin
         $ENV{STEAMWORKSDIR}/redistributable_bin)
elseif(APPLE)
    list(APPEND STEAMWORKS_SEARCH_PATHS
         ${STEAMWORKS_PATH}/redistributable_bin/osx32
         $ENV{STEAMWORKSDIR}/redistributable_bin/osx32)
else()
    list(APPEND STEAMWORKS_SEARCH_PATHS
         ${STEAMWORKS_PATH}/redistributable_bin/linux32
         $ENV{STEAMWORKSDIR}/redistributable_bin/linux32)
endif()

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

FIND_PATH(STEAMWORKS_INCLUDE_DIR
    NAMES steam_api.h
    HINTS ENV STEAMWORKSDIR
    PATHS ${STEAMWORKS_SEARCH_PATHS}
)

FIND_LIBRARY(STEAMWORKS_LIBRARY
    NAMES steam_api
    HINTS ENV STEAMWORKSDIR
    PATHS ${STEAMWORKS_SEARCH_PATHS}
)

IF(STEAMWORKS_LIBRARY)
    SET(STEAMWORKS_LIBRARIES "${STEAMWORKS_LIBRARY}")     # Could add "general" keyword, but it is optional
ENDIF()

# handle the QUIETLY and REQUIRED arguments and set XXX_FOUND to TRUE if all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(STEAMWORKS DEFAULT_MSG STEAMWORKS_LIBRARIES STEAMWORKS_INCLUDE_DIR)
