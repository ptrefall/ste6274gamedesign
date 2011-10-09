#pragma once

#include <Protocol/gameprotocol.h>

class Packet
{
public:
	Packet(const gp_default_server_query &request);
	Packet(const gp_connect_request &request);
	Packet(const gp_join_request &request);
	Packet(const gp_game_request &request);
	Packet(const unsigned int &request);

	Packet(const gp_default_server_query_answer &answer);
	Packet(const gp_connect_answer &answer);
	Packet(const gp_join_answer &answer);
	Packet(const gp_client_verification_answer &answer);
	Packet(const gp_game_update &answer);

	const gp_default_server_query	&getDsqReq()  const { return data.r0; }
	const gp_connect_request		&getConReq()  const { return data.r1; }
	const gp_join_request			&getJoinReq() const { return data.r2; }
	const gp_game_request			&getGameReq() const { return data.r3; }
	const bool						 getVerReq()  const { return true; }

	const gp_default_server_query_answer	&getDsqAns()  const { return data.a0; }
	const gp_connect_answer					&getConAns()  const { return data.a1; }
	const gp_join_answer					&getJoinAns() const { return data.a2; }
	const gp_client_verification_answer		&getVerAns() const { return data.a3; }
	const gp_game_update					&getGameUpd() const { return data.a4; }

	bool isDsqReq()  const { return is_dsq_req; }
	bool isConReq()  const { return is_con_req; }
	bool isJoinReq() const { return is_join_req; }
	bool isVerReq() const { return is_ver_req; }
	bool isGameReq() const { return is_game_req; }
	bool isDsqAns()  const { return is_dsq_ans; }
	bool isConAns()  const { return is_con_ans; }
	bool isJoinAns() const { return is_join_ans; }
	bool isVerAns() const { return is_ver_ans; }
	bool isGameUpd() const { return is_game_upd; }

	bool isGamePacket() const { return game_packet; }

private:
	union
	{
		gp_default_server_query r0;
		gp_connect_request		r1;
		gp_join_request			r2;
		gp_game_request			r3;
		gp_default_server_query_answer	a0;
		gp_connect_answer				a1;
		gp_join_answer					a2;
		gp_client_verification_answer	a3;
		gp_game_update					a4;
	} data;

	bool is_dsq_req, is_con_req, is_join_req, is_ver_req, is_game_req,
		 is_dsq_ans, is_con_ans, is_join_ans, is_ver_ans, is_game_upd;
	bool game_packet;
};
