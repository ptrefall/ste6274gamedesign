#pragma once

#include <Component.h>
#include <Game/Graphics/Utils.h>
#include <SPK.h>
#include <SPK_GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Systems { class ParticleSystem; }

namespace Components
{
	class ParticleEmitter : public Totem::Component
	{
	public:
		COMPONENT_1(ParticleEmitter, Systems::ParticleSystem);
		ParticleEmitter(Totem::Entity &owner, const T_String &name, Systems::ParticleSystem &particleSystem);
		virtual ~ParticleEmitter();

		virtual void update(const F32 &deltaTime);

		const glm::vec3 &getPos() const { return position.get(); }
		const glm::vec3 &getColor() const { return color.get(); }

		void setIndex(const S32 &index) { this->index = index; }
		const S32 &getIndex() const { return index; }

	private:
		Systems::ParticleSystem &particleSystem;
		S32 index;

		Totem::Property<glm::vec3> position;
		Totem::Property<glm::vec3> color;

		//Delegates
		T_HashedString customRendererId;
		T_Void customRenderFunc(const U32 &program_id);
	};
}
