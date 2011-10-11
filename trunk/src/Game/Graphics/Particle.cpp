/*	Ken Mazaika
	February 23, 2005
	Quagmire Particle Engine
	Copyright 2005
	http://home.comcast.net/~kjmaz
  */

#include "Particle.h"
#include <fstream>

using namespace Graphics;

/*  The Particle Object */
QdParticle::QdParticle()
{
	//Assumed values if none are initiated
	m_fAge = 0;
	m_nFrames = 0;
	m_fLife = 1.0f;
	m_fGravityFactor=.025f;
	
}

//Draws the particle to the screen
void QdParticle::draw()
{
	//Set color
	glColor4f(m_clrCurrent.m_fR, m_clrCurrent.m_fG, m_clrCurrent.m_fB, m_clrCurrent.m_fA);

	//Dont display particle on first frame of it's life
	if(m_fLife ==1.0f)
	{
		glColor4f(0,0,0,0);
	}




	//draw the square
	//g.SelectTexture();
	glBegin(GL_QUADS);
	//Texture coordinates make the texture pointed upwards without being twisted
		glTexCoord2f(1,1); glVertex3f(m_ptUL.m_fX, m_ptUL.m_fY, m_ptUL.m_fZ);
		glTexCoord2f(0,1); glVertex3f(m_ptLR.m_fX, m_ptUL.m_fY, m_ptUL.m_fZ);
		glTexCoord2f(0,0); glVertex3f(m_ptLR.m_fX, m_ptLR.m_fY, m_ptUL.m_fZ);
		glTexCoord2f(1,0); glVertex3f(m_ptUL.m_fX, m_ptLR.m_fY, m_ptUL.m_fZ);
	glEnd();
}

void QdParticle::advance()
{

	//Move the quad in the direction it should be headed
	m_ptUL.m_fX  += m_ptDirection.m_fX;
	m_ptUL.m_fY  += m_ptDirection.m_fY;
	m_ptUL.m_fZ  += m_ptDirection.m_fZ;

	m_ptLR.m_fX  += m_ptDirection.m_fX;
	m_ptLR.m_fY  += m_ptDirection.m_fY;
	m_ptLR.m_fZ  += m_ptDirection.m_fZ;

	//Add the force of gravity
	//The formula for the force of gravity (without factoring friction from
	//the air) is something like:  h = vit + 1/2 a t^2
	m_ptUL.m_fX += m_ptGravity.m_fX * m_fAge *m_fAge;
	m_ptUL.m_fY += m_ptGravity.m_fY* m_fAge *m_fAge;
	m_ptUL.m_fZ += m_ptGravity.m_fZ* m_fAge *m_fAge;

	m_ptLR.m_fX += m_ptGravity.m_fX* m_fAge *m_fAge;
	m_ptLR.m_fY += m_ptGravity.m_fY* m_fAge *m_fAge;
	m_ptLR.m_fZ += m_ptGravity.m_fZ* m_fAge *m_fAge;

	//Slowly fade the color
	m_clrCurrent.m_fR+= m_clrFade.m_fR;
	m_clrCurrent.m_fG+= m_clrFade.m_fG;
	m_clrCurrent.m_fB+= m_clrFade.m_fB;
	m_clrCurrent.m_fA+= m_clrFade.m_fA;
	
	m_fLife+= m_fFadeLife;

	m_nFrames++;
	m_fAge = m_nFrames * m_fGravityFactor;

}


/* The Particle Engine */

QdParticleEngine::QdParticleEngine()
{
	m_bLimit = 0;
	m_bEngineActive = 0;
	m_nAge = 0;
	//m_szImgPath = &m_szImgPathA[0];
	//strcpy(m_szImgPath, "particle.bmp");
}

QdParticleEngine::~QdParticleEngine()
{
	if(m_bEngineActive)
	{
		destroy();
	}
	m_bEngineActive = 0;
}

int QdParticleEngine::init(int nParticles)
{
	//g.SetMode(QD_NO_AUTO_TEXTURE);


	//g.LoadFromBitmap(m_szImgPath);

	m_bEngineActive=1;
	m_pParticles = new QdParticle[nParticles];
	m_nParticles= nParticles;


	int nCount =0;
	while(nCount<nParticles)
	{
		m_pParticles[nCount].m_nParticle=nCount;
		nCount++;
	}
	resetParticles();
	return nParticles;
}


int QdParticleEngine::draw()
{
	int nCount=0;
	while(nCount != m_nParticles)
	{
		m_pParticles[nCount].draw();
		m_pParticles[nCount].advance();
		if(m_pParticles[nCount].m_fLife<0.0f)
		{
			particleDead(nCount);
		}

		nCount++;
	}

	if(m_bLimit)
	{
		nCount =0;
		while(nCount!=m_nParticles)
		{
			if(m_pParticles[nCount].m_ptUL.m_fX<m_fLimitL)
			{
				particleDead(nCount);
			}
			else if(m_pParticles[nCount].m_ptLR.m_fX>m_fLimitR)
			{
				particleDead(nCount);
			}
			else if(m_pParticles[nCount].m_ptLR.m_fY<m_fLimitB)
			{
				particleDead(nCount);
			}
			else if(m_pParticles[nCount].m_ptUL.m_fY>m_fLimitT)
			{
				particleDead(nCount);
			}

			nCount++;
		}

	}
	m_nAge++;

nCount = 0;


	return nCount;
}
int QdParticleEngine::destroy()
{
	m_nAge = 0;
	delete[] m_pParticles;
	return 4;

}


int QdParticleEngine::resetParticles()
{
	return 0;
}
int QdParticleEngine::particleDead(int nParticle)
{
	return 0;
}


int QdParticleEngine::setCurrentColor(int nParticle, float fRed, float fGreen, float fBlue, float fAlpha)
{
	m_pParticles[nParticle].m_clrCurrent.m_fR=fRed;
	m_pParticles[nParticle].m_clrCurrent.m_fG=fGreen;
	m_pParticles[nParticle].m_clrCurrent.m_fB=fBlue;
	m_pParticles[nParticle].m_clrCurrent.m_fA=fAlpha;

	return QD_SUCCESS;
}


/*int QdParticleEngine::setImgPath(char *szImgPath)
{
	strcpy(m_szImgPath,szImgPath);
	return QD_SUCCESS;

}*/

int QdParticleEngine::setFadeColor(int nParticle, float fRed, float fGreen, float fBlue, float fAlpha)
{
	m_pParticles[nParticle].m_clrFade.m_fR=fRed;
	m_pParticles[nParticle].m_clrFade.m_fG=fGreen;
	m_pParticles[nParticle].m_clrFade.m_fB=fBlue;
	m_pParticles[nParticle].m_clrFade.m_fA=fAlpha;

	return QD_SUCCESS;
}


int QdParticleEngine::setDirection(int nParticle, float fX, float fY, float fZ)
{
	m_pParticles[nParticle].m_ptDirection.m_fX=fX;
	m_pParticles[nParticle].m_ptDirection.m_fY=fY;
	m_pParticles[nParticle].m_ptDirection.m_fZ=fZ;
	return QD_SUCCESS;

}

int QdParticleEngine::setGravity(int nParticle, float fX, float fY, float fZ)
{
	m_pParticles[nParticle].m_ptGravity.m_fX=fX;
	m_pParticles[nParticle].m_ptGravity.m_fY=fY;
	m_pParticles[nParticle].m_ptGravity.m_fZ=fZ;
	return QD_SUCCESS;
}

int QdParticleEngine::setLR(int nParticle, float fX, float fY, float fZ)
{
	m_pParticles[nParticle].m_ptLR.m_fX=fX;
	m_pParticles[nParticle].m_ptLR.m_fY=fY;
	m_pParticles[nParticle].m_ptLR.m_fZ=fZ;
	return QD_SUCCESS;
}

int QdParticleEngine::setUL(int nParticle, float fX, float fY, float fZ)
{
	m_pParticles[nParticle].m_ptUL.m_fX=fX;
	m_pParticles[nParticle].m_ptUL.m_fY=fY;
	m_pParticles[nParticle].m_ptUL.m_fZ=fZ;
	return QD_SUCCESS;
}

int QdParticleEngine::setAge(int nParticle, float fAge)
{
	m_pParticles[nParticle].m_fAge=fAge;
	return QD_SUCCESS;
}

int QdParticleEngine::setFrame(int nParticle, int nFrame)
{
	m_pParticles[nParticle].m_nFrames=nFrame;
	return QD_SUCCESS;
}

int QdParticleEngine::setGravityFactor(int nParticle, float fGravityFactor)
{
	m_pParticles[nParticle].m_fGravityFactor=fGravityFactor;
	return QD_SUCCESS;
}

int QdParticleEngine::setLife(int nParticle, float fLife)
{
	m_pParticles[nParticle].m_fLife=fLife;
	return QD_SUCCESS;
}


int QdParticleEngine::setFadeLife(int nParticle, float fFadeLife)
{
	m_pParticles[nParticle].m_fFadeLife=fFadeLife;
	return QD_SUCCESS;
}


//Set Limit Function used to disable limits after the boundaries are set
int QdParticleEngine::setLimit(bool bLimit)
{
	m_bLimit = bLimit;
	return QD_SUCCESS;
}

int QdParticleEngine::setLimit(float fLimitL, float fLimitR, float fLimitB, float fLimitT)
{
	//Enable limit
	m_bLimit = 1;

	m_fLimitL = fLimitL;
	m_fLimitR = fLimitR;
	m_fLimitT = fLimitT;
	m_fLimitB = fLimitB;

	return QD_SUCCESS;
}