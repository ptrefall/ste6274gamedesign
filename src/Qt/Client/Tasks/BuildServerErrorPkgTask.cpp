#include "BuildServerErrorPkgTask.h"

#include "SendPkgTask.h"

void BuildServerErrorPkgTask::load(const quint16 &err)
{
  this->err = err;
  setLoadOK();
}

void BuildServerErrorPkgTask::run()
{
  // Check whether client and request id has been set
  if( !isValid() )
    return;

  // Init the pkg
  initReplyPkg(GP_REQUEST_TYPE_ERROR);

  // Compile body
  gp_client_error_response body;
  body.error = err;

  // Add body to the send package
  addToBlock<gp_client_error_response>( body );

  // Build send task and queue it for execution
  buildAndQueue();
}
