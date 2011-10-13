#include "ParticleEmitter.h"
#include <Game/Systems/ParticleSystem.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace Components;
using namespace Totem;

ParticleEmitter::ParticleEmitter(Entity &owner, const T_String &name, Systems::ParticleSystem &particleSystem)
: Component(owner, name), particleSystem(particleSystem), index(-1), customRendererId("CUSTOM_RENDERER")
{
	position = owner.addProperty<glm::vec3>("Position", glm::vec3(0.0f));
	color = owner.addProperty<glm::vec3>("Color", glm::vec3(1.0f));
	particle_type = owner.addProperty<T_HashedStringType>("ParticleType", T_HashedString("ENGINE_FLAME").getId());
	particle_count = owner.addProperty<U32>("ParticleCount", 1000);

	owner.registerFunction1<const U32 &, T_Void>(customRendererId).bind(this, &ParticleEmitter::customRenderFunc);

	particleSystem.loadParticleEmitter(this);
}

ParticleEmitter::~ParticleEmitter()
{
	particleSystem.removeParticleEmitter(this);
}

void ParticleEmitter::update(const F32 &deltaTime)
{
	particleSystem.updateParticleEmitter(this, deltaTime);
}

T_Void ParticleEmitter::customRenderFunc(const U32 &program_id)
{
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);       
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, 7);
	particleSystem.renderParticleEmitter(this);
	glEnable(GL_DEPTH_TEST);       
	glDisable(GL_BLEND);
	return (T_Void)NULL_PTR;
}