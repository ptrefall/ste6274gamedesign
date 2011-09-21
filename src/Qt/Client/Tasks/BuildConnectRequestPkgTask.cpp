#include "BuildConnectRequestPkgTask.h"

void BuildConnectRequestPkgTask::load(const quint8 &state)
{
	this->state = state;
	setLoadOK();
}

void BuildConnectRequestPkgTask::run()
{
	if( !isValid() )
		return;

	// Init the pkg
	initRequestPkg(GP_REQUEST_TYPE_CONNECT);

	// Compile body
	gp_connect_request body;
	body.connect_flag = state;
	//body.state = state;

	// Add body to send package
	addToBlock<gp_connect_request>( body );

	// Build send task and queue it for execution
	buildAndQueue();
}
