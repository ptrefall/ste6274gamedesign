#pragma once

#include <types_config.h>
#include <TemplateEventHandler.h>

class Game : public Factotum::EventHandler
{
public:
	Game();
	~Game();

	void advanceFrame(const F32 &delta);
};
