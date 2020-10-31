#include "HRRNOperatingSystem.h"

HRRNOperatingSystem::HRRNOperatingSystem() : OperatingSystem() {
	this->currentJob = JCB::EMPTY_JOB;
}

HRRNOperatingSystem::~HRRNOperatingSystem() {
}

void HRRNOperatingSystem::interrupt(const DateTime& now) {
	this->update(now);
}

void HRRNOperatingSystem::registJob(const JCB& j, const DateTime& now) {
	if (this->currentJob == JCB::EMPTY_JOB) {
		currentJob = j;
	}
	else {
		this->jcbList.push(j);
		this->update(now);
	}
}

JCB& HRRNOperatingSystem::getCurrentJob(const DateTime& now) {
	return this->currentJob;
}

void HRRNOperatingSystem::currentJobFinshCall(const DateTime& now) {
	if (!this->jcbList.empty()) {
		this->update(now);
		this->currentJob = this->jcbList.top();
		this->jcbList.pop();
	}
	else {
		this->currentJob = JCB::EMPTY_JOB;
	}
}

void HRRNOperatingSystem::update(const DateTime& now) {
	std::vector<JCB> temp;
	while (!this->jcbList.empty()) {
		temp.push_back(this->jcbList.top());
		this->jcbList.pop();
	}
	for (auto i : temp) {
		i.update(now);
		this->jcbList.push(i);
	}
}

bool HRRNOperatingSystem::JobCmpByLength::operator()(const JCB& a, const JCB& b) {
	return (static_cast<long long>(a.getWaitTime()) + a.getTimeRequired()) * b.getTimeRequired() <
		(static_cast<long long>(b.getWaitTime()) + b.getTimeRequired()) * a.getTimeRequired();
}