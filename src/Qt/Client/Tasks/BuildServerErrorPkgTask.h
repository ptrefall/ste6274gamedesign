#pragma once

#include "BuildPkgTask.h"

#include <Protocol/gameprotocol.h>

class BuildServerErrorPkgTask : public BuildPkgTask
{
public:
	BuildServerErrorPkgTask() {}

    void load(const quint16 &err);
    void run();

private:
	quint16 err;
};
