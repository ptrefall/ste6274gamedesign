#pragma once

#include <types_config.h>

namespace Components { class Renderable; }

namespace Systems
{

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	void addRenderable(Components::Renderable *renderable);
	bool hasGroup(const U32 &groupName) const;
	void addGroup(const U32 &groupName, const bool &instanced = false);
	void incrementGroup(const U32 &groupName);

	void compile();
	void render();

private:
	T_Vector<Components::Renderable*>::Type renderables;

	struct RenderGroup
	{
		U32 id;
		bool instanced;
		U32 instances;

		RenderGroup(const U32 &id, const bool &instanced, const U32 &instances = 1) 
			: id(id), instanced(instanced), instances(instances) {}
	};
	T_Vector<RenderGroup*>::Type groups;
};

}
