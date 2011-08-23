
#=============================================================================
# Copyright 2001-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

# Use of this file is deprecated, and is here for backwards compatibility with CMake 1.4
# GLU library is now found by FindOpenGL.cmake
#

FIND_PATH(GLEW_DIR include/GL/glew.h
      D:/Development/3rdParty/GLEW/
    )

FIND_PATH(GLEW_INCLUDE_PATH GL/glew.h
      D:/Development/3rdParty/GLEW/include
    )

FIND_LIBRARY(GLEW_LIBRARY_DEBUG
  NAMES glew32sd
  PATHS D:/Development/3rdParty/GLEW/lib
    )
	
FIND_LIBRARY(GLEW_LIBRARY_RELEASE
  NAMES glew32s
  PATHS D:/Development/3rdParty/GLEW/lib
    )
