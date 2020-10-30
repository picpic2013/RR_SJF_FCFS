#pragma once
#include "OperatingSystem.h"
#include <deque>

class RROperatingSystem : public OperatingSystem {
public:
	RROperatingSystem();
	~RROperatingSystem();

	virtual void interrupt(const DateTime& now);
	virtual void registJob(const JCB& j);
	virtual JCB& getCurrentJob();
	virtual void currentJobFinshCall();
private:
	std::deque<JCB> jcbList;
};

RROperatingSystem::RROperatingSystem() : OperatingSystem() {
}

RROperatingSystem::~RROperatingSystem() {
}

void RROperatingSystem::interrupt(const DateTime& now) {
	this->jcbList.push_back(this->jcbList.front());
	this->jcbList.pop_front();
}

void RROperatingSystem::registJob(const JCB& j) {
	this->jcbList.push_back(j);
}

JCB& RROperatingSystem::getCurrentJob() {
	if (!this->jcbList.size()) {
		return JCB::EMPTY_JOB;
	}
	return this->jcbList.front();
}
void RROperatingSystem::currentJobFinshCall() {
	this->jcbList.pop_front();
}