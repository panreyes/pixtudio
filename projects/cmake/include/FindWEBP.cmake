# Locate webp
# This module defines XXX_FOUND, XXX_INCLUDE_DIRS and XXX_LIBRARIES standard variables
#
# $WEBPDIR is an environment variable that would
# correspond to the ./configure --prefix=$WEBPDIR
# used in building libwebp.

SET(WEBP_SEARCH_PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw # Fink
    /opt/local # DarwinPorts
    /opt/csw # Blastwave
    /opt
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

FIND_PATH(WEBP_INCLUDE_DIR
    NAMES webp/decode.h
    HINTS
    $ENV{WEBPDIR}
    $ENV{WEBP_PATH}
    PATH_SUFFIXES include
    PATHS ${WEBP_SEARCH_PATHS}
)

FIND_LIBRARY(WEBP_LIBRARY
    NAMES webp libwebp
    HINTS
    $ENV{WEBPDIR}
    $ENV{WEBP_PATH}
    PATH_SUFFIXES lib lib64 lib/i386-linux-gnu win32/Webp_Dynamic_Release "Win32/${MSVC_YEAR_NAME}/x64/Release" "Win32/${MSVC_YEAR_NAME}/Win32/Release"
    PATHS ${WEBP_SEARCH_PATHS}
)

# First search for d-suffixed libs
FIND_LIBRARY(WEBP_LIBRARY_DEBUG
    NAMES webpd webp_d libwebpd libwebp_d
    HINTS
    $ENV{WEBPDIR}
    $ENV{WEBP_PATH}
    PATH_SUFFIXES lib lib64 lib/i386-linux-gnu win32/Webp_Dynamic_Debug "Win32/${MSVC_YEAR_NAME}/x64/Debug" "Win32/${MSVC_YEAR_NAME}/Win32/Debug"
    PATHS ${WEBP_SEARCH_PATHS}
)

IF(NOT WEBP_LIBRARY_DEBUG)
    # Then search for non suffixed libs if necessary, but only in debug dirs
    FIND_LIBRARY(WEBP_LIBRARY_DEBUG
        NAMES webp libwebp
        HINTS
        $ENV{WEBPDIR}
        $ENV{WEBP_PATH}
        PATH_SUFFIXES win32/Webp_Dynamic_Debug "Win32/${MSVC_YEAR_NAME}/x64/Debug" "Win32/${MSVC_YEAR_NAME}/Win32/Debug"
        PATHS ${WEBP_SEARCH_PATHS}
    )
ENDIF()


IF(WEBP_LIBRARY)
    IF(WEBP_LIBRARY_DEBUG)
        SET(WEBP_LIBRARIES optimized "${WEBP_LIBRARY}" debug "${WEBP_LIBRARY_DEBUG}")
    ELSE()
        SET(WEBP_LIBRARIES "${WEBP_LIBRARY}")       # Could add "general" keyword, but it is optional
    ENDIF()
ENDIF()

# handle the QUIETLY and REQUIRED arguments and set XXX_FOUND to TRUE if all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(WEBP DEFAULT_MSG WEBP_LIBRARIES WEBP_INCLUDE_DIR)
