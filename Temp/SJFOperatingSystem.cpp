#include "SJFOperatingSystem.h"

SJFOperatingSystem::SJFOperatingSystem() : OperatingSystem() {
	this->currentJob = JCB::EMPTY_JOB;
}

SJFOperatingSystem::~SJFOperatingSystem() {
}

void SJFOperatingSystem::registJob(const JCB& j) {
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

JCB& SJFOperatingSystem::getCurrentJob() {
	return this->currentJob;
}

void SJFOperatingSystem::currentJobFinshCall() {
	if (!this->jcbList.empty()) {
		this->currentJob = this->jcbList.top();
		this->jcbList.pop();
	}
	else {
		this->currentJob = JCB::EMPTY_JOB;
	}
}

bool SJFOperatingSystem::JobCmpByLength::operator()(const JCB& a, const JCB& b) {
	return (a.getTimeRequired() - a.getRunningTime()) > 
		(b.getTimeRequired() - b.getRunningTime());
}