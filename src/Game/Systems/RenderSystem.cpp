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

void RenderSystem::render()
{
	for(U32 i = 0; i < renderables.size(); i++)
		renderables[i]->render();
}
