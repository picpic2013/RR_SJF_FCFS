#pragma once
#include "OperatingSystem.h"
#include <queue>

class FCFSOperatingSystem : public OperatingSystem{
public:
	FCFSOperatingSystem();
	~FCFSOperatingSystem();

	virtual void interrupt();
	virtual void registJob(const JCB& j);
	virtual JCB& getCurrentJob();
	virtual void currentJobFinshCall();

private:
	std::queue<JCB> jcbList;
};