#pragma once

#include <types_config.h>
#include <Game/Graphics/Particle.h>

namespace Components {class ParticleEmitter; }

namespace Systems
{

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void loadParticleEmitter(Components::ParticleEmitter *emitter);
	void removeParticleEmitter(Components::ParticleEmitter *emitter);
	void updateParticleEmitter(Components::ParticleEmitter *emitter, const F32 &deltaTime);
	void renderParticleEmitter(Components::ParticleEmitter *emitter);
private:
	T_Vector<Components::ParticleEmitter*>::Type emitters;
	T_Vector<Graphics::QdParticleEngine*>::Type engines;
};
}
