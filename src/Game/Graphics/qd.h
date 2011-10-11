/*	Ken Mazaika
	February 23, 2005
	Quantum Dynamics Header
	Copyright 2005
	http://home.comcast.net/~kjmaz
  */
  
#pragma once

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <GL/glew.h>
#ifdef WIN32
#include <GL/wglew.h>
#endif

#define QD_SUCCESS 1

//For The Particle Engine
namespace Graphics
{

class Qd3dPoint
{
public:
	float m_fX;
	float m_fY;
	float m_fZ;
};

class QdColor
{
public:
	float m_fR;
	float m_fG;
	float m_fB;
	float m_fA;
};
}
