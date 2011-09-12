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
	class Renderable : public Factotum::Component
	{
	public:
		COMPONENT_1(Renderable, Systems::RenderSystem)
		Renderable(Factotum::Entity &owner, const T_String &name, Systems::RenderSystem &renderSystem);
		virtual ~Renderable();

		void compile();
		void prepare();
		void render();

		const bool &isCompiled() const { return compiled.get(); }

	private:
		Systems::RenderSystem &renderSystem;

		Factotum::PropertyList<unsigned int> indices;
		Factotum::PropertyList<glm::vec3> vertices;
		Factotum::PropertyList<glm::vec3> normals;
		Factotum::PropertyList<glm::vec3> tangents;
		Factotum::PropertyList<glm::vec3> colors;
		Factotum::PropertyList<glm::vec2> texCoords;

		Factotum::Property<glm::mat4> modelMatrix;
		Factotum::Property<glm::gtc::quaternion::quat> qRotation;
		Factotum::Property<glm::vec3> position;

		Factotum::Property<bool> compiled;

		U32 vao;
		Graphics::VertexBufferObject *vbo;
		Graphics::Shader *program;

		Graphics::Uniform *mvp;
		glm::mat4 mvpMat;
	};
}
