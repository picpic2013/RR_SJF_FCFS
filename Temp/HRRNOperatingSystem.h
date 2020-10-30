#pragma once
#include "OperatingSystem.h"
#include <queue>
#include <vector>

class HRRNOperatingSystem : public OperatingSystem {
public:
	HRRNOperatingSystem();
	~HRRNOperatingSystem();

	virtual void interrupt(const DateTime& now);
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

HRRNOperatingSystem::HRRNOperatingSystem() : OperatingSystem() {
	this->currentJob = JCB::EMPTY_JOB;
}

HRRNOperatingSystem::~HRRNOperatingSystem() {
}

void HRRNOperatingSystem::interrupt(const DateTime& now) {
	std::vector<JCB> tempList;
	while (!this->jcbList.empty()) {
		JCB temp = this->jcbList.top();
		this->jcbList.pop();
		temp.update(now);
		tempList.push_back(temp);
	}
	for (auto i : tempList) {
		this->jcbList.push(i);
	}
	if (this->currentJob != JCB::EMPTY_JOB) {
		this->currentJob.update(now);
		this->jcbList.push(this->currentJob);
		this->currentJob = this->jcbList.top();
		this->jcbList.pop();
	}
}

void HRRNOperatingSystem::registJob(const JCB& j) {
	JobCmpByLength jc;
	if (this->currentJob == JCB::EMPTY_JOB) {
		this->currentJob = j;
	}
	else if (jc(this->currentJob, j)) {
		this->jcbList.push(this->currentJob);
		this->currentJob = j;
	}
	else {
		this->jcbList.push(j);
	}
}

JCB& HRRNOperatingSystem::getCurrentJob() {
	return this->currentJob;
}

void HRRNOperatingSystem::currentJobFinshCall() {
	if (!this->jcbList.empty()) {
		this->currentJob = this->jcbList.top();
		this->jcbList.pop();
	}
	else {
		this->currentJob = JCB::EMPTY_JOB;
	}
}

bool HRRNOperatingSystem::JobCmpByLength::operator()(const JCB& a, const JCB& b) {
	return (static_cast<long long>(a.getWaitTime()) + a.getTimeRequired()) * b.getTimeRequired() > 
		(static_cast<long long>(b.getWaitTime()) + b.getTimeRequired()) * a.getTimeRequired();
}