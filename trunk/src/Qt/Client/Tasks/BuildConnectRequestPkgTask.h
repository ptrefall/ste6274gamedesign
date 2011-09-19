#pragma once

#include "BuildPkgTask.h"

class BuildConnectRequestPkgTask : public BuildPkgTask
{
public:
	BuildConnectRequestPkgTask() {}

    void load(const quint8 &state);
    void run();

private:
    quint8 state;
};
