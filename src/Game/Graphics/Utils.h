#pragma once

#include <iostream>
#include <GL/glew.h>
#ifdef WIN32
#include <GL/wglew.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef BUFFER_OFFSET
	/// BUFFER_OFFSET is used with some OpenGL functions to offset indexing correctly into the buffer.
	#define BUFFER_OFFSET(bytes) ((GLubyte*) NULL + bytes)
#endif

#ifdef _DEBUG
#define GL_DEBUG 1
#else
#define GL_DEBUG 0
#endif

#define CHECK_GL_ERROR()												\
{																		\
	GLenum glError;														\
	if ((glError = glGetError()) != GL_NO_ERROR) {						\
		std::cerr << "OpenGL error code at line" << __LINE__ << ": " << glError << std::endl;		\
	}																	\
}

#define GL(func)														\
{																		\
	func																\
	if(GL_DEBUG) {														\
	GLenum glError;														\
	if ((glError = glGetError()) != GL_NO_ERROR) {						\
		std::cerr << "OpenGL error code at line" << __LINE__ << ": " << glError << std::endl;		\
	}}}

#define ATTRIB_VERTEX	 0
#define ATTRIB_NORMAL	 1
#define ATTRIB_TANGENT	 2
#define ATTRIB_COLOR	 3
#define ATTRIB_TEXCOORD	 4
