#pragma once
#include <GL/glew.h>
#include <GL/wglew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <exception>
#include <iostream>

typedef unsigned int U32;
typedef int S32;
typedef float F32;
typedef std::string T_String;


template< typename T >
struct T_Vector {
	typedef std::vector<T> Type;
};
template< typename K, typename V >
struct T_Map {
	typedef std::tr1::unordered_map<K,V> Type;
};
template< typename K, typename V >
struct T_Pair {
	typedef std::pair<K,V> Type;
};

typedef std::exception T_Exception;

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

#define ATTRIB_VERTEX	0
#define ATTRIB_NORMAL	1
#define ATTRIB_TEXCOORD	2
