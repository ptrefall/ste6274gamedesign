#include "Packet.h"

Packet::Packet(const gp_default_server_query &request)
	: is_dsq_req(true), is_con_req(false), is_join_req(false), is_ver_req(false), is_game_req(false),
	  is_dsq_ans(false), is_con_ans(false), is_join_ans(false), is_ver_ans(false), is_game_upd(false), is_error(false),
	  game_packet(false)
{
	data.r0 = request;
}
Packet::Packet(const gp_connect_request &request)
	: is_dsq_req(false), is_con_req(true), is_join_req(false), is_ver_req(false), is_game_req(false),
	  is_dsq_ans(false), is_con_ans(false), is_join_ans(false), is_ver_ans(false), is_game_upd(false), is_error(false),
	  game_packet(false)
{
	data.r1 = request;
}
Packet::Packet(const gp_join_request &request)
	: is_dsq_req(false), is_con_req(false), is_join_req(true), is_ver_req(false), is_game_req(false),
	  is_dsq_ans(false), is_con_ans(false), is_join_ans(false), is_ver_ans(false), is_game_upd(false), is_error(false),
	  game_packet(false)
{
	data.r2 = request;
}

Packet::Packet(const gp_game_request &request)
	: is_dsq_req(false), is_con_req(false), is_join_req(false), is_ver_req(false), is_game_req(true),
	  is_dsq_ans(false), is_con_ans(false), is_join_ans(false), is_ver_ans(false), is_game_upd(false), is_error(false),
	  game_packet(false)
{
	data.r3 = request;
}

Packet::Packet(const unsigned int &request)
	: is_dsq_req(false), is_con_req(false), is_join_req(false), is_ver_req(false), is_game_req(false),
	  is_dsq_ans(false), is_con_ans(false), is_join_ans(false), is_ver_ans(false), is_game_upd(false), is_error(false),
	  game_packet(false)
{
	if(request == (unsigned int)GP_REQUEST_TYPE_CLIENT_VERIFICATION)
	{
		is_ver_req = true;
		game_packet = true;
	}
}

Packet::Packet(const gp_default_server_query_answer &answer)
	: is_dsq_req(false), is_con_req(false), is_join_req(false), is_ver_req(false), is_game_req(false),
	  is_dsq_ans(true), is_con_ans(false), is_join_ans(false), is_ver_ans(false), is_game_upd(false), is_error(false),
	  game_packet(false)
{
	data.a0 = answer;
}
Packet::Packet(const gp_connect_answer &answer)
	: is_dsq_req(false), is_con_req(false), is_join_req(false), is_ver_req(false), is_game_req(false),
	  is_dsq_ans(false), is_con_ans(true), is_join_ans(false), is_ver_ans(false), is_game_upd(false), is_error(false),
	  game_packet(false)
{
	data.a1 = answer;
}
Packet::Packet(const gp_join_answer &answer)
	: is_dsq_req(false), is_con_req(false), is_join_req(false), is_ver_req(false), is_game_req(false),
	  is_dsq_ans(false), is_con_ans(false), is_join_ans(true), is_ver_ans(false), is_game_upd(false), is_error(false),
	  game_packet(false)
{
	data.a2 = answer;
}

Packet::Packet(const gp_client_verification_answer &answer)
	: is_dsq_req(false), is_con_req(false), is_join_req(false), is_ver_req(false), is_game_req(false),
	  is_dsq_ans(false), is_con_ans(false), is_join_ans(false), is_ver_ans(true), is_game_upd(false), is_error(false),
	  game_packet(true)
{
	data.a3 = answer;
}

Packet::Packet(const gp_game_update &answer)
	: is_dsq_req(false), is_con_req(false), is_join_req(false), is_ver_req(false), is_game_req(false),
	  is_dsq_ans(false), is_con_ans(false), is_join_ans(false), is_ver_ans(false), is_game_upd(true), is_error(false),
	  game_packet(true)
{
	data.a4 = answer;
}

Packet::Packet(const gp_client_error_response &answer)
	: is_dsq_req(false), is_con_req(false), is_join_req(false), is_ver_req(false), is_game_req(false),
	  is_dsq_ans(false), is_con_ans(false), is_join_ans(false), is_ver_ans(false), is_game_upd(false), is_error(true),
	  game_packet(false)
{
	data.a5 = answer;
}
