#pragma once

#include "Particle.h"

namespace Graphics
{

class EngineFlameParticleEngine : public QdParticleEngine
{
public:

	EngineFlameParticleEngine(float fRed, float fGreen, float fBlue, float fAlpha);
	virtual int resetParticles();
	virtual int particleDead(int nParticle);
	int m_nParticlesDead;

protected:

	QdColor m_clrParticleColor;
};
}
