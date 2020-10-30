#pragma once
#include "OperatingSystem.h"
#include <queue>
#include <vector>

class SJFOperatingSystem : public OperatingSystem{
public:
	SJFOperatingSystem();
	~SJFOperatingSystem();

	virtual void registJob(const JCB& j);
	virtual JCB& getCurrentJob();
	virtual void currentJobFinshCall();
private:
	struct JobCmpByLength {
		bool operator()(const JCB& a, const JCB& b);
	};
	std::priority_queue<JCB, std::vector<JCB>, JobCmpByLength> jcbList;
	JCB currentJob;
};