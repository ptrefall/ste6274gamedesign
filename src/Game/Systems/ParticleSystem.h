#pragma once

#include <types_config.h>
#include <SPK.h>

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
	SPK::System* createParticleSystem(const SPK::Vector3D& pos,const SPK::Vector3D& color);
	SPK::SPK_ID BaseSystemID;
	T_Vector<Components::ParticleEmitter*>::Type emitters;
	T_Vector<SPK::System*>::Type systems;
};
}
