#pragma once

#include "BuildPkgTask.h"

#include <Protocol/gameprotocol.h>

class Client;

class BuildDSQPkgTask : public BuildPkgTask
{
public:
	BuildDSQPkgTask() : client(0x0) {}

    void    load(Client *client, const gp_default_server_query &query);
    void    run();

private:
    gp_default_server_query query;
    Client *client;
};
