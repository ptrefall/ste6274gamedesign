#pragma once

#include <Component.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Systems { class RenderSystem; }
namespace Graphics { class VertexBufferObject; class Shader; class Uniform; }
namespace Components
{
	class Renderable : public Totem::Component
	{
	public:
		COMPONENT_1(Renderable, Systems::RenderSystem)
		Renderable(Totem::Entity &owner, const T_String &name, Systems::RenderSystem &renderSystem);
		virtual ~Renderable();

		void compile();
		void prepare();
		void render();

		const bool &isCompiled() const { return compiled.get(); }

	private:
		Systems::RenderSystem &renderSystem;

		Totem::PropertyList<unsigned int> indices;
		Totem::PropertyList<glm::vec3> vertices;
		Totem::PropertyList<glm::vec3> normals;
		Totem::PropertyList<glm::vec3> tangents;
		Totem::PropertyList<glm::vec3> colors;
		Totem::PropertyList<glm::vec2> texCoords;

		Totem::Property<glm::mat4> modelMatrix;
		Totem::Property<glm::gtc::quaternion::quat> qRotation;
		Totem::Property<glm::vec3> position;
		Totem::Property<glm::vec3> scale;

		Totem::Property<bool> compiled;

		U32 vao;
		Graphics::VertexBufferObject *vbo;
		Graphics::Shader *program;

		Graphics::Uniform *mvp;
		glm::mat4 mvpMat;
	};
}
