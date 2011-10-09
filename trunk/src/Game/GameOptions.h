#pragma once

#include <types_config.h>

class GameOptions
{
public:
	GameOptions();
	~GameOptions();

	//Player
	T_String player_name;
	T_String player_race;
	T_String player_class;
	int player_team_id;

	//Client
	T_String ip_addr;
	unsigned short port;

	//Effects
	bool use_bloom_effect;

	//Resolution
	F32 resolution_width;
	F32 resolution_height;
	F32 resolution_depth;
};
