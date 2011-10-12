#include "ParticleSystem.h"
#include <Game/Components/ParticleEmitter.h>
#include <Game/Graphics/EngineFlameParticleEngine.h>
#include <Game/Graphics/Utils.h>
#include <math.h>

using namespace Systems;

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::loadParticleEmitter(Components::ParticleEmitter *emitter)
{
	if(emitter->getIndex() >= 0)
		removeParticleEmitter(emitter);

	S32 index = emitters.size();
	emitter->setIndex(index);
	emitters.push_back(emitter);
	
	const glm::vec3 &pos = emitter->getPos();
	const glm::vec3 &color = emitter->getColor();
	const T_HashedStringType &type = emitter->getParticleType();

	if(type == T_HashedString("ENGINE_FLAME").getId())
	{
		Graphics::EngineFlameParticleEngine *engine = new Graphics::EngineFlameParticleEngine(1.0f, 0.2f, 0.0f, 1.0f);
		engine->init((int)emitter->getParticleCount());
		engines.push_back(engine);
	}
}

void ParticleSystem::removeParticleEmitter(Components::ParticleEmitter *emitter)
{
	/*const S32 &index = emitter->getIndex();
	if(index < 0)
		return;

	emitters[index] = emitters.back();
	emitters.pop_back();

	Graphics::QdParticleEngine *engine = engines[index];
	engines[index] = engines.back();
	engines.pop_back();
	delete engine;

	emitter->setIndex(-1);*/
}

void ParticleSystem::updateParticleEmitter(Components::ParticleEmitter *emitter, const F32 &deltaTime)
{
	const S32 &index = emitter->getIndex();
	if(index < 0)
		return;

	Graphics::QdParticleEngine *engine = engines[index];
}

void ParticleSystem::renderParticleEmitter(Components::ParticleEmitter *emitter)
{
	const S32 &index = emitter->getIndex();
	if(index < 0)
		return;

	Graphics::QdParticleEngine *engine = engines[index];
	/*if(*/engine->draw();/* == 0)
		removeParticleEmitter(emitter);*/
}
