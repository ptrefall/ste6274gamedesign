#pragma once

#include <Protocol/gameprotocol.h>

class Packet
{
public:
	Packet(const gp_default_server_query &request);
	Packet(const gp_connect_request &request);
	Packet(const gp_join_request &request);

	Packet(const gp_default_server_query_answer &answer);
	Packet(const gp_connect_answer &answer);
	Packet(const gp_join_answer &answer);

	const gp_default_server_query	&getDsqReq()  const { return data.r0; }
	const gp_connect_request		&getConReq()  const { return data.r1; }
	const gp_join_request			&getJoinReq() const { return data.r2; }

	const gp_default_server_query_answer	&getDsqAns()  const { return data.a0; }
	const gp_connect_answer					&getConAns()  const { return data.a1; }
	const gp_join_answer					&getJoinAns() const { return data.a2; }

	bool isDsqReq()  const { return is_dsq_req; }
	bool isConReq()  const { return is_con_req; }
	bool isJoinReq() const { return is_join_req; }
	bool isDsqAns()  const { return is_dsq_ans; }
	bool isConAns()  const { return is_con_ans; }
	bool isJoinAns() const { return is_join_ans; }

private:
	union
	{
		gp_default_server_query r0;
		gp_connect_request		r1;
		gp_join_request			r2;
		gp_default_server_query_answer	a0;
		gp_connect_answer				a1;
		gp_join_answer					a2;
	} data;

	bool is_dsq_req, is_con_req, is_join_req,
		 is_dsq_ans, is_con_ans, is_join_ans;
};
