#include "GameOptions.h"

GameOptions::GameOptions()
	: player_name("Visitor"), player_race("Human"), player_class("Pilot"),
	  ip_addr("127.0.0.1"), port(1234), 
	  use_bloom_effect(false),
	  resolution_width(800), resolution_height(600), resolution_depth(16)
{
	//Should load initial values from xml if available
}

GameOptions::~GameOptions()
{
}
