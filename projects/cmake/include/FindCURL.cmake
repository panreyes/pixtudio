# Locate CURL
# This module defines XXX_FOUND, XXX_INCLUDE_DIRS and XXX_LIBRARIES standard variables
#
# $CURLDIR is an environment variable that would
# correspond to the ./configure --prefix=$CURLDIR
# used in building CURL.

SET(CURL_SEARCH_PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw # Fink
    /opt/local # DarwinPorts
    /opt/csw # Blastwave
    /opt
    ${CURL_PATH}
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

FIND_PATH(CURL_INCLUDE_DIR
    NAMES curl/curl.h
    HINTS ENV CURLDIR
    PATH_SUFFIXES include
    PATHS ${CURL_SEARCH_PATHS}
)

FIND_LIBRARY(CURL_LIBRARY
    NAMES curl libcurl libcurl_imp.lib
    HINTS ENV CURLDIR
    PATH_SUFFIXES lib lib64 lib/i386-linux-gnu win32/Dynamic_Release "Win32/${MSVC_YEAR_NAME}/x64/Release" "Win32/${MSVC_YEAR_NAME}/Win32/Release"
    PATHS ${CURL_SEARCH_PATHS}
)

# First search for d-suffixed libs
FIND_LIBRARY(CURL_LIBRARY_DEBUG
    NAMES curld curl_d libcurld libcurl_d
    HINTS ENV CURLDIR
    PATH_SUFFIXES lib lib64 lib/i386-linux-gnu win32/Dynamic_Debug "Win32/${MSVC_YEAR_NAME}/x64/Debug" "Win32/${MSVC_YEAR_NAME}/Win32/Debug"
    PATHS ${CURL_SEARCH_PATHS}
)

IF(NOT CURL_LIBRARY_DEBUG)
    # Then search for non suffixed libs if necessary, but only in debug dirs
    FIND_LIBRARY(CURL_LIBRARY_DEBUG
        NAMES curl libcurl
        HINTS ENV CURLDIR
        PATH_SUFFIXES win32/Dynamic_Debug "Win32/${MSVC_YEAR_NAME}/x64/Debug" "Win32/${MSVC_YEAR_NAME}/Win32/Debug"
        PATHS ${CURL_SEARCH_PATHS}
    )
ENDIF()


IF(CURL_LIBRARY)
    IF(CURL_LIBRARY_DEBUG)
        SET(CURL_LIBRARIES optimized "${CURL_LIBRARY}" debug "${CURL_LIBRARY_DEBUG}")
    ELSE()
        SET(CURL_LIBRARIES "${CURL_LIBRARY}")     # Could add "general" keyword, but it is optional
    ENDIF()
ENDIF()

# handle the QUIETLY and REQUIRED arguments and set XXX_FOUND to TRUE if all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CURL DEFAULT_MSG CURL_LIBRARIES CURL_INCLUDE_DIR)
