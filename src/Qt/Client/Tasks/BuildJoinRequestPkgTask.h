#pragma once

#include "BuildPkgTask.h"

class BuildJoinRequestPkgTask : public BuildPkgTask
{
public:
	BuildJoinRequestPkgTask();

	void load(const quint8 &state, const quint32 &validation_code);
	void run();

private:
	quint8 state;
	quint32 validation_code;
};
