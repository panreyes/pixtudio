# Base Io build system
# Written by Jeremy Tregunna <jeremy.tregunna@me.com>
#
# Find libtheora.

FIND_PATH(THEORA_INCLUDE_DIR theora/theora.h theora/theoradec.h)

SET(THEORA_NAMES ${THEORA_NAMES} theora libtheora theoradec libtheoradec)
FIND_LIBRARY(THEORA_LIBRARY NAMES ${THEORA_NAMES} PATH)

IF(THEORA_INCLUDE_DIR AND THEORA_LIBRARY)
    SET(THEORA_FOUND TRUE)
ENDIF(THEORA_INCLUDE_DIR AND THEORA_LIBRARY)

IF(THEORA_FOUND)
    IF(NOT Theora_FIND_QUIETLY)
        MESSAGE(STATUS "Found Theora: ${THEORA_LIBRARY}")
    ENDIF (NOT Theora_FIND_QUIETLY)
ELSE(THEORA_FOUND)
    IF(Theora_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find theora")
    ENDIF(Theora_FIND_REQUIRED)
ENDIF (THEORA_FOUND)
