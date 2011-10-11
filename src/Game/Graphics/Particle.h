/*	Ken Mazaika
	February 23, 2005
	Quagmire Particle Engine
	Copyright 2005
	http://home.comcast.net/~kjmaz
  */

#pragma once

#include "qd.h"

namespace Graphics
{

class QdParticle
{
protected:
	Qd3dPoint m_ptUL;		//Upper Left corner to the square
	Qd3dPoint m_ptLR;		//Lower right corner of the square

	QdColor m_clrCurrent;	//Current color of the particle
	QdColor m_clrFade;		//What increment the color by

	Qd3dPoint m_ptDirection; //What to increment the object by
	Qd3dPoint m_ptGravity;	//What to increment the object by

	int m_nFrames;			//How many times has the particle been displayed
	float m_fAge;			//How many "seconds" elapsed (for gravity calculations)

	float m_fLife;			//Determine "life"
	float m_fGravityFactor;
	float m_fFadeLife;
	int m_nParticle;
public:
	QdParticle();
	void draw();
	void advance();

	friend class QdParticleEngine;
};

class QdParticleEngine
{
protected:
	bool m_bLimit;
	QdParticle *m_pParticles;
	bool m_bEngineActive;
	int m_nParticles;
	int m_nAge;

	float m_fLimitR;
	float m_fLimitL;
	float m_fLimitT;
	float m_fLimitB;

	//char *m_szImgPath;
	//char m_szImgPathA[128];
public:
	int setLimit(float fLimitL, float fLimitR, float fLimitT, float fLimitB);
	int setLimit(bool bLimit);
	int setCurrentColor(int nParticle, float fRed, float fGreen, float fBlue, float fAlpha);
	int setFadeColor(int nParticle, float fRed, float fGreen, float fBlue, float fAlpha);
	int setDirection(int nParticle, float fX, float fY, float fZ);
	int setGravity(int nParticle, float fX, float fY, float fZ);
	int setLR(int nParticle, float fX, float fY, float fZ);
	int setUL(int nParticle, float fX, float fY, float fZ);
	int setAge(int nParticle, float fAge);
	int setFrame(int nParticle, int nFrame);
	int setGravityFactor(int nParticle, float fGravityFactor);
	int setLife(int nParticle, float fLife);
	int setFadeLife(int nParticle, float fFadeLife);
	//int setImgPath(char *szImgPath);
	int draw();
	QdParticleEngine();
	~QdParticleEngine();
	int init(int nParticles);
	int virtual resetParticles();

	//reset a specific particle
	virtual int particleDead(int nParticle);
	int destroy();
};
}
