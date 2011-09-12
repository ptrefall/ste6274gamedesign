#include "Renderable.h"
#include <Game/Systems/RenderSystem.h>
#include <Game/Graphics/Utils.h>
#include <Game/Graphics/VertexBufferObject.h>
#include <Game/Graphics/Attribute.h>
#include <Game/Graphics/Uniform.h>
#include <Game/Graphics/Shader.h>

using namespace Components;
using namespace Factotum;

Renderable::Renderable(Entity &owner, const T_String &name, Systems::RenderSystem &renderSystem)
: Component(owner, name), renderSystem(renderSystem), mvp(0x0)
{
	renderSystem.addRenderable(this);

	indices = owner.addPropertyList<unsigned int>("Indices");
	vertices = owner.addPropertyList<glm::vec3>("Vertices");
	colors = owner.addPropertyList<glm::vec3>("Colors");

	modelMatrix = owner.addProperty<glm::mat4>("ModelMatrix", glm::mat4(1.0f));
	qRotation = owner.addProperty<glm::gtc::quaternion::quat>("Rotation", glm::gtc::quaternion::quat());
	position = owner.addProperty<glm::vec3>("Position", glm::vec3(0.0f));

	compiled = owner.addProperty<bool>("Compiled", false);
}

Renderable::~Renderable()
{
	if(mvp) delete mvp;

	GL( glDeleteVertexArrays(1, &vao); );
}

void Renderable::compile()
{
	program = renderSystem.getShaderSystem().create(GL_VERTEX_SHADER, "../../resources/Shaders/minimal.vs", GL_FRAGMENT_SHADER, "../../resources/Shaders/minimal.fs");
	GL( glBindAttribLocation(program->id, ATTRIB_VERTEX, "Vertex"); );
	GL( glBindAttribLocation(program->id, ATTRIB_COLOR, "Color"); );
	program->link();

	//GL( glGenVertexArrays(1, &vao); );
	//GL( glBindVertexArray(vao); );

	vbo = new Graphics::VBO(sizeof(glm::vec3)*(vertices.size() + colors.size()), indices.size(), &indices.get()[0], GL_STATIC_DRAW);
	vbo->bind(0);
	vbo->buffer(GL_FLOAT, 3*vertices.size(), &vertices.get());
	vbo->buffer(GL_FLOAT, 3*colors.size(), &colors.get());
	//Graphics::Attribute(ATTRIB_VERTEX,	3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	//Graphics::Attribute(ATTRIB_COLOR,	3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(glm::vec3)*vertices.size()));
	vbo->unbind();

	//GL( glBindVertexArray(0); );

	mvpMat = glm::mat4(1.0f);
	mvp = new Graphics::Uniform(GL_FLOAT_MAT4, "mvp", glm::value_ptr(mvpMat));
	mvp->findLocation(program->id);

	compiled = true;
}

void Renderable::prepare()
{
	// Calculate the translation matrix using the local position vector
	glm::mat4 translate = glm::mat4(1.0f);
	translate[3][0] = position.get().x;
	translate[3][1] = position.get().y;
	translate[3][2] = position.get().z;

	glm::mat4 rotation = glm::gtc::quaternion::mat4_cast(qRotation.get());

	// Then, we calculate the local transformation matrix
	modelMatrix = glm::mat4(1.0f);
	//modelMatrix *= scale;
	modelMatrix *= rotation;
	modelMatrix *= translate;

	GLdouble p[16];
	GLdouble v[16]; 
	glGetDoublev(GL_PROJECTION_MATRIX, p);
	glGetDoublev(GL_MODELVIEW_MATRIX, v);
	glm::mat4 pMat = glm::mat4(p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],p[9],p[10],p[11],p[12],p[13],p[14],p[15]);
	glm::mat4 vMat = glm::mat4(v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7],v[8],v[9],v[10],v[11],v[12],v[13],v[14],v[15]);

	mvpMat = pMat * vMat * modelMatrix.get();
	mvp->setData(glm::value_ptr(mvpMat));
}

void Renderable::render()
{
	if(vertices.empty() || vertices.size() != colors.size())
		return;

	program->bind();
	mvp->bind();
	glBegin(GL_TRIANGLES);
	for(U32 i = 0; i < indices.size(); i++)
	{
		const glm::vec3 &vertex = vertices[indices[i].get()].get();
		const glm::vec3 &color = colors[indices[i].get()].get();
		glColor4f(color.r, color.g, color.b, 1.0f);
		glVertex3f(vertex.x, vertex.y, vertex.z);
	}
	glEnd();
	program->unbind();

	/*program->bind();
	mvp->bind();
	//GL( glBindVertexArray(vao); );

	vbo->bind(0);
	//Graphics::Attribute(ATTRIB_VERTEX,	3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	//Graphics::Attribute(ATTRIB_COLOR,	3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(glm::vec3)*vertices.size()));
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(sizeof(glm::vec3)*vertices.size()));

	vbo->bindIndices();

	GL( glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, BUFFER_OFFSET(0)); );

	vbo->unbindIndices();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	//GL( glDisableVertexAttribArray(ATTRIB_VERTEX); );
	//GL( glDisableVertexAttribArray(ATTRIB_COLOR); );
	vbo->unbind();
	//GL( glBindVertexArray(0); );
	program->unbind();*/
}
