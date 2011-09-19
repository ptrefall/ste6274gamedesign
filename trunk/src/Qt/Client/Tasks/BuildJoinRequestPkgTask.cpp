#include "BuildJoinRequestPkgTask.h"

BuildJoinRequestPkgTask::BuildJoinRequestPkgTask()
{
}

void BuildJoinRequestPkgTask::load(const quint8 &state, const quint32 &validation_code)
{
	this->state = state;
	this->validation_code = validation_code;
	setLoadOK();
}

void BuildJoinRequestPkgTask::run()
{
	if( !isValid() )
		return;

	initRequestPkg(GP_REQUEST_TYPE_JOIN);

	gp_join_request body;
	//body.state = _state;
	//body.validation_code = _validation_code;
	/*gp_uint32               client_id;
    gp_join_request_flags   flags;
    char                    player_name[64];
    gp_uint32               team_id;
    char                    race[32];
    char                    class_[32];*/

	// Add body to send package
	addToBlock<gp_join_request>( body );

	// Build send task and queue it for execution
	buildAndQueue();
}
