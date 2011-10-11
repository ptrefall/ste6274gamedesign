#include "ParticleSystem.h"
#include <Game/Components/ParticleEmitter.h>
#include <Game/Graphics/Utils.h>
#include <SPK.h>
#include <SPK_GL.h>
#include <math.h>

using namespace Systems;

ParticleSystem::ParticleSystem()
	: BaseSystemID(SPK::NO_ID)
{
	SPK::randomSeed = 10;

	SPK::Model* model = SPK::Model::create
	(
		/*SPK::FLAG_RED | SPK::FLAG_GREEN | SPK::FLAG_BLUE | SPK::FLAG_ALPHA,
		SPK::FLAG_ALPHA,
		SPK::FLAG_RED | SPK::FLAG_GREEN | SPK::FLAG_BLUE*/
		SPK::FLAG_ALPHA | SPK::FLAG_SIZE | SPK::FLAG_ANGLE,
		SPK::FLAG_ALPHA | SPK::FLAG_SIZE | SPK::FLAG_ANGLE,
		SPK::FLAG_SIZE | SPK::FLAG_ANGLE
	);
	//model->setParam(SPK::PARAM_ALPHA,1.0f,0.0f);
	model->setLifeTime(1.6f,4.0f);
	model->setParam(SPK::PARAM_ALPHA,0.2f,0.0f);
	model->setParam(SPK::PARAM_SIZE,1.0f,1.0f,2.0f,8.0f);
	const float PI = 3.14159265358979323846f;
	model->setParam(SPK::PARAM_ANGLE,0.0f,4.0f * PI,0.0f,4.0f * PI);

	// Creates the zone
	SPK::Point* source = SPK::Point::create();
	// Creates the emitter
	SPK::StraightEmitter* emitter = SPK::StraightEmitter::create(SPK::Vector3D(-1.0f, 0.0f, 0.0f));
	emitter->setZone(source);
	emitter->setForce(0.1f,1.5f);
	emitter->setTank(500);
	emitter->setFlow(500);

	SPK::GL::GLQuadRenderer* renderer = SPK::GL::GLQuadRenderer::create();
	renderer->enableBuffersCreation(true);
	renderer->enableRenderingHint(SPK::ALPHA_TEST, true);
	//renderer->setType(SPK::POINT_SPRITE);
	//renderer->enableWorldSize(true);
	SPK::GL::GLPointRenderer::setPixelPerUnit(/*70.0f * 3.14159f / 180.f*/ 70.0f,600);
	//renderer->setSize(0.1f);
	renderer->setTexture(7);
	renderer->setTexturingMode(SPK::TEXTURE_2D);
	renderer->setScale(0.1f, 0.1f);

	renderer->setBlending(SPK::BLENDING_ALPHA);
	renderer->setTextureBlending(GL_MODULATE);
	renderer->enableRenderingHint(SPK::DEPTH_WRITE,false);

	SPK::Group* group = SPK::Group::create(model,20000);
	group->addEmitter(emitter);
	group->setRenderer(renderer);
	group->setGravity(SPK::Vector3D(0.0f,-1.0f,0.0f));
	group->setFriction(0.7f);

	SPK::System* system = SPK::System::create();
	system->addGroup(group);

	model->setShared(true);
	renderer->setShared(true);
	BaseSystemID = system->getID();
}

ParticleSystem::~ParticleSystem()
{
	SPK::SPKFactory::getInstance().destroyAll();
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
	SPK::System *system = createParticleSystem(SPK::Vector3D(pos.x, pos.y, pos.z), SPK::Vector3D(color.r, color.g, color.b));
	systems.push_back(system);
}

void ParticleSystem::removeParticleEmitter(Components::ParticleEmitter *emitter)
{
	const S32 &index = emitter->getIndex();
	if(index < 0)
		return;

	emitters[index] = emitters.back();
	emitters.pop_back();

	SPK_Destroy(systems[index]);
	systems[index] = systems.back();
	systems.pop_back();

	emitter->setIndex(-1);
}

void ParticleSystem::updateParticleEmitter(Components::ParticleEmitter *emitter, const F32 &deltaTime)
{
	const S32 &index = emitter->getIndex();
	if(index < 0)
		return;

	SPK::System *system = systems[index];
	
	const glm::vec3 &pos = emitter->getPos();
	SPK::Vector3D p = SPK::Vector3D(pos.x, pos.y, pos.z);
	SPK::Zone* zone = system->getGroup(0)->getEmitter(0)->getZone();
	zone->setPosition(p);

	if(!system->update(deltaTime))
		removeParticleEmitter(emitter);
}

void ParticleSystem::renderParticleEmitter(Components::ParticleEmitter *emitter)
{
	const S32 &index = emitter->getIndex();
	if(index < 0)
		return;

	SPK::System *system = systems[index];
	system->render();
}

SPK::System* ParticleSystem::createParticleSystem(const SPK::Vector3D& pos,const SPK::Vector3D& color)
{
	SPK::System* system = SPK_Copy(SPK::System,BaseSystemID);
	SPK::Model* model = system->getGroup(0)->getModel();
	model->setParam(SPK::PARAM_RED,		std::max(0.0f,color.x - 0.25f),	std::min(1.0f,color.x + 0.25f));
	model->setParam(SPK::PARAM_GREEN,	std::max(0.0f,color.y - 0.25f),	std::min(1.0f,color.y + 0.25f));
	model->setParam(SPK::PARAM_BLUE,	std::max(0.0f,color.z - 0.25f),	std::min(1.0f,color.z + 0.25f));
	SPK::Zone* zone = system->getGroup(0)->getEmitter(0)->getZone();
	zone->setPosition(pos);
	return system;
}
