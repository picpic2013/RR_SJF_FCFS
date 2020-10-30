#include "SJFOperatingSystem.h"

SJFOperatingSystem::SJFOperatingSystem() : OperatingSystem() {
	this->currentJob = JCB::EMPTY_JOB;
}

SJFOperatingSystem::~SJFOperatingSystem() {
}

void SJFOperatingSystem::registJob(const JCB& j) {
	this->jcbList.push(j);
}

JCB& SJFOperatingSystem::getCurrentJob() {
	if (this->jcbList.empty()) {
		this->currentJob = JCB::EMPTY_JOB;
		return this->currentJob;
	}
	if (this->currentJob != this->jcbList.top()) {
		if (this->currentJob != JCB::EMPTY_JOB) {
			this->jcbList.push(this->currentJob);
		}
		this->currentJob = this->jcbList.top();
	}
	return this->currentJob;
}

void SJFOperatingSystem::currentJobFinshCall() {
	if (!this->jcbList.empty()) {
		this->jcbList.pop();
	}
}

bool SJFOperatingSystem::JobCmpByLength::operator()(const JCB& a, const JCB& b) {
	return a.getTimeRequired() > b.getTimeRequired();
}