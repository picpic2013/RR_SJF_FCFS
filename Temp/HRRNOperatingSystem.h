#pragma once
#include "OperatingSystem.h"
#include <queue>
#include <vector>

class HRRNOperatingSystem : public OperatingSystem {
public:
	HRRNOperatingSystem();
	~HRRNOperatingSystem();

	virtual void interrupt(const DateTime& now);
	virtual void registJob(const JCB& j, const DateTime& now);
	virtual JCB& getCurrentJob(const DateTime& now);
	virtual void currentJobFinshCall(const DateTime& now);
private:
	struct JobCmpByLength {
		bool operator()(const JCB& a, const JCB& b);
	};
	std::priority_queue<JCB, std::vector<JCB>, JobCmpByLength> jcbList;
	JCB currentJob;
	void update(const DateTime& now);
};