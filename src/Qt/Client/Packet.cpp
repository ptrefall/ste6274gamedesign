#include "Packet.h"

Packet::Packet(const gp_default_server_query &request)
	: is_dsq_req(true), is_con_req(false), is_join_req(false), 
	  is_dsq_ans(false), is_con_ans(false), is_join_ans(false)
{
	data.r0 = request;
}
Packet::Packet(const gp_connect_request &request)
	: is_dsq_req(false), is_con_req(true), is_join_req(false), 
	  is_dsq_ans(false), is_con_ans(false), is_join_ans(false)
{
	data.r1 = request;
}
Packet::Packet(const gp_join_request &request)
	: is_dsq_req(false), is_con_req(false), is_join_req(true), 
	  is_dsq_ans(false), is_con_ans(false), is_join_ans(false)
{
	data.r2 = request;
}

Packet::Packet(const gp_default_server_query_answer &answer)
	: is_dsq_req(false), is_con_req(false), is_join_req(false), 
	  is_dsq_ans(true), is_con_ans(false), is_join_ans(false)
{
	data.a0 = answer;
}
Packet::Packet(const gp_connect_answer &answer)
	: is_dsq_req(false), is_con_req(false), is_join_req(false), 
	  is_dsq_ans(false), is_con_ans(true), is_join_ans(false)
{
	data.a1 = answer;
}
Packet::Packet(const gp_join_answer &answer)
	: is_dsq_req(false), is_con_req(false), is_join_req(false), 
	  is_dsq_ans(false), is_con_ans(false), is_join_ans(true)
{
	data.a2 = answer;
}