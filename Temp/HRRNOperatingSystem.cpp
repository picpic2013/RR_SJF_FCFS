#include "HRRNOperatingSystem.h"

HRRNOperatingSystem::HRRNOperatingSystem() : OperatingSystem() {
	this->currentJob = JCB::EMPTY_JOB;
}

HRRNOperatingSystem::~HRRNOperatingSystem() {
}

void HRRNOperatingSystem::interrupt(const DateTime& now) {
	std::vector<JCB> tempList;
	while (!this->jcbList.empty()) {
		tempList.push_back(jcbList.top());
		this->jcbList.pop();
	}
	for (auto i : tempList) {
		i.update(now);
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
	if (this->currentJob == JCB::EMPTY_JOB) {
		currentJob = j;
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