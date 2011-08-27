#include "RenderSystem.h"
#include "../Components/Renderable.h"

using namespace Systems;
using namespace Factotum;

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::addRenderable(Components::Renderable *renderable)
{
#if _DEBUG
	if(renderable == NULL_PTR)
		return; //BAD CODER!

	for(U32 i = 0; i < renderables.size(); i++)
	{
		if(renderables[i] == renderable)
			return; //Already excist! BAD, BAD CODER!
	}
#endif

	renderables.push_back(renderable);
}

void RenderSystem::compile()
{
	//TODO: Make renderables list into a new_pending list of renderables.
	//On compilation, renderables should be moved into it's render group list.
	for(U32 i = 0; i < renderables.size(); i++)
	{
		if(renderables[i]->isCompiled() == false)
			renderables[i]->compile();
	}
}

void RenderSystem::render()
{
	for(U32 i = 0; i < renderables.size(); i++)
		renderables[i]->render();
}
