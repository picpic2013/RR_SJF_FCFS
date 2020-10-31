#pragma once
#include "OperatingSystem.h"
#include <deque>

class RROperatingSystem : public OperatingSystem {
public:
	RROperatingSystem();
	~RROperatingSystem();

	virtual void interrupt(const DateTime& now);
	virtual void registJob(const JCB& j, const DateTime& now);
	virtual JCB& getCurrentJob(const DateTime& now);
	virtual void currentJobFinshCall(const DateTime& now);
private:
	std::deque<JCB> jcbList;
};