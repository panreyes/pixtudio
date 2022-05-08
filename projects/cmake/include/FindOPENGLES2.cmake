#-------------------------------------------------------------------
# This file is stolen from part of the CMake build system for OGRE (Object-oriented Graphics Rendering Engine) http://www.ogre3d.org/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# - Try to find OpenGLES
# Once done this will define
#
#  OPENGLES2_FOUND        - system has OpenGLES
#  OPENGLES2_INCLUDE_DIR  - the GL include directory
#  OPENGLES2_LIBRARIES    - Link these to use OpenGLES
#

# Win32, Apple, and Android are not tested!
# Linux tested and works

find_path(OPENGLES2_INCLUDE_DIR 
	NAMES GLES2/gl2.h
	PATH_SUFFIXES mesa
	PATHS /usr/openwin/share/include
		/opt/graphics/OpenGL/include
		/opt/vc/include
		/usr/X11R6/include
		/usr/include
)

find_library(OPENGLES2_LIBRARY
	NAMES GLESv2
	PATHS /opt/graphics/OpenGL/lib
		/usr/openwin/lib
		/usr/shlib /usr/X11R6/lib
		/opt/vc/lib
		/usr/lib/aarch64-linux-gnu
		/usr/lib/arm-linux-gnueabihf
		/usr/lib
		/mingw32/lib
)

if(OPENGLES2_LIBRARY AND OPENGLES2_INCLUDE_DIR)
	set(OPENGLES2_LIBRARIES ${OPENGLES2_LIBRARY} ${OPENGLES2_LIBRARIES})
	set(OPENGLES2_FOUND TRUE)
endif()

mark_as_advanced(
	OPENGLES2_INCLUDE_DIR
	OPENGLES2_LIBRARY
)

if(OPENGLES2_FOUND)
	message(STATUS "Found system OpenGL ES 2 library: ${OPENGLES2_LIBRARIES}")
	message(STATUS "Found system OpenGL ES 2 include dir: ${OPENGLES2_INCLUDE_DIR}")
else()
	message(STATUS "NOT Found system OpenGL ES 2 library: ${OPENGLES2_LIBRARIES}")
	set(OPENGLES2_LIBRARIES "")
	set(OPENGLES2_LIBRARY "")
endif()
