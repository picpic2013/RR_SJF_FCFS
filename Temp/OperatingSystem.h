#pragma once
#include "JCB.h"
#include <vector>
class OperatingSystem {
public:
	OperatingSystem();
	~OperatingSystem();

	virtual void interrupt() = 0;
	void registJob(const JCB& j);

private:
	std::vector<JCB> jcbList;
	virtual bool jobCompairFunction(const JCB& a, const JCB& b) = 0;
};