#pragma once
#include "JCB.h"
#include <vector>
class OperatingSystem {
public:
	OperatingSystem();
	~OperatingSystem();

	virtual void interrupt(const DateTime& now);
	virtual void registJob(const JCB& j, const DateTime& now) = 0;
	virtual JCB& getCurrentJob(const DateTime& now) = 0;
	virtual void currentJobFinshCall(const DateTime& now) = 0;

private:
};