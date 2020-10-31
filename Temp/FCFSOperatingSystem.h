#pragma once
#include "OperatingSystem.h"
#include <queue>

class FCFSOperatingSystem : public OperatingSystem{
public:
	FCFSOperatingSystem();
	~FCFSOperatingSystem();

	virtual void registJob(const JCB& j, const DateTime& now);
	virtual JCB& getCurrentJob(const DateTime& now);
	virtual void currentJobFinshCall(const DateTime& now);

private:
	std::queue<JCB> jcbList;
};