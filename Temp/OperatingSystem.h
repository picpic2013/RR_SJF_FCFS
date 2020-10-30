#pragma once
#include "JCB.h"
#include <vector>
class OperatingSystem {
public:
	OperatingSystem();
	~OperatingSystem();

	virtual void interrupt() = 0;
	virtual void registJob(const JCB& j) = 0;
	virtual JCB& getCurrentJob() = 0;
	virtual void currentJobFinshCall() = 0;

private:
};