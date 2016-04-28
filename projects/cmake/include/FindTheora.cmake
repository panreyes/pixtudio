# Locate Theora
# This module defines XXX_FOUND, XXX_INCLUDE_DIRS and XXX_LIBRARIES standard variables
#
# $THEORADIR is an environment variable that would
# correspond to the ./configure --prefix=$THEORADIR
# used in building theora.

SET(THEORA_SEARCH_PATHS
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

FIND_PATH(THEORA_INCLUDE_DIR
    NAMES theora/theora.h theora/theoradec.h
    HINTS
    $ENV{THEORADIR}
    $ENV{THEORA_PATH}
    PATH_SUFFIXES include
    PATHS ${THEORA_SEARCH_PATHS}
)

# Find libtheora
FIND_LIBRARY(THEORA_LIBRARY
    NAMES theora libtheora
    HINTS
    $ENV{THEORADIR}
    $ENV{THEORA_PATH}
    PATH_SUFFIXES lib lib64 lib/i386-linux-gnu win32/Theora_Dynamic_Release "Win32/${MSVC_YEAR_NAME}/x64/Release" "Win32/${MSVC_YEAR_NAME}/Win32/Release"
    PATHS ${THEORA_SEARCH_PATHS}
)

# First search for d-suffixed libs
FIND_LIBRARY(THEORA_LIBRARY_DEBUG
    NAMES theora theora_d libtheorad libtheora_d
    HINTS
    $ENV{THEORADIR}
    $ENV{THEORA_PATH}
    PATH_SUFFIXES lib lib64 lib/i386-linux-gnu win32/Theora_Dynamic_Debug "Win32/${MSVC_YEAR_NAME}/x64/Debug" "Win32/${MSVC_YEAR_NAME}/Win32/Debug"
    PATHS ${THEORA_SEARCH_PATHS}
)

IF(NOT THEORA_LIBRARY_DEBUG)
    # Then search for non suffixed libs if necessary, but only in debug dirs
    FIND_LIBRARY(THEORA_LIBRARY_DEBUG
        NAMES theora libtheora
        HINTS
        $ENV{THEORADIR}
        $ENV{THEORA_PATH}
        PATH_SUFFIXES win32/Theora_Dynamic_Debug "Win32/${MSVC_YEAR_NAME}/x64/Debug" "Win32/${MSVC_YEAR_NAME}/Win32/Debug"
        PATHS ${THEORA_SEARCH_PATHS}
    )
ENDIF()

# If libtheoradec is found, link against it, too
FIND_LIBRARY(THEORADEC_LIBRARY
    NAMES theoradec libtheoradec
    HINTS
    $ENV{THEORADIR}
    $ENV{THEORA_PATH}
    PATH_SUFFIXES lib lib64 lib/i386-linux-gnu win32/Theoradec_Dynamic_Release "Win32/${MSVC_YEAR_NAME}/x64/Release" "Win32/${MSVC_YEAR_NAME}/Win32/Release"
    PATHS ${THEORA_SEARCH_PATHS}
)

# First search for d-suffixed libs
FIND_LIBRARY(THEORADEC_LIBRARY_DEBUG
    NAMES theoradec theoradec_d libtheoradecd libtheoradec_d
    HINTS
    $ENV{THEORADIR}
    $ENV{THEORA_PATH}
    PATH_SUFFIXES lib lib64 lib/i386-linux-gnu win32/Theoradec_Dynamic_Debug "Win32/${MSVC_YEAR_NAME}/x64/Debug" "Win32/${MSVC_YEAR_NAME}/Win32/Debug"
    PATHS ${THEORA_SEARCH_PATHS}
)

IF(NOT THEORADEC_LIBRARY_DEBUG)
    # Then search for non suffixed libs if necessary, but only in debug dirs
    FIND_LIBRARY(THEORADEC_LIBRARY_DEBUG
        NAMES theoradec libtheoradec
        HINTS
        $ENV{THEORADIR}
        $ENV{THEORA_PATH}
        PATH_SUFFIXES win32/Theoradec_Dynamic_Debug "Win32/${MSVC_YEAR_NAME}/x64/Debug" "Win32/${MSVC_YEAR_NAME}/Win32/Debug"
        PATHS ${THEORA_SEARCH_PATHS}
    )
ENDIF()

IF(THEORA_LIBRARY)
    IF(THEORA_LIBRARY_DEBUG)
        SET(THEORA_LIBRARIES optimized "${THEORA_LIBRARY}" "${THEORADEC_LIBRARY}" debug "${THEORA_LIBRARY_DEBUG}" "${THEORADEC_LIBRARY_DEBUG}")
    ELSE()
        SET(THEORA_LIBRARIES "${THEORA_LIBRARY}" "${THEORADEC_LIBRARY}")       # Could add "general" keyword, but it is optional
    ENDIF()
ENDIF()

# handle the QUIETLY and REQUIRED arguments and set XXX_FOUND to TRUE if all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(THEORA DEFAULT_MSG THEORA_LIBRARIES THEORA_INCLUDE_DIR)
