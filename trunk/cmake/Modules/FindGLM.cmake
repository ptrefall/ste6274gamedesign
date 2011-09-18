
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

FIND_PATH(GLM_DIR glm/glm.hpp
      D:/Development/3rdParty/GLM
	  C:/Paal/Development/3rdParties/glm-0.9.2.4
    )

FIND_PATH(GLM_INCLUDE_PATH glm/glm.hpp
      C:/Paal/Development/3rdParties/glm-0.9.2.4
    )
