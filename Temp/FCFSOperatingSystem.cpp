#include "FCFSOperatingSystem.h"
#include <iostream>

FCFSOperatingSystem::FCFSOperatingSystem() : OperatingSystem() {
}

FCFSOperatingSystem::~FCFSOperatingSystem() {
}

void FCFSOperatingSystem::registJob(const JCB& j, const DateTime& now) {
	this->jcbList.push(j);
}

JCB& FCFSOperatingSystem::getCurrentJob(const DateTime& now) {
	if (this->jcbList.empty()) {
		return JCB::EMPTY_JOB;
	}
	return this->jcbList.front();
}

void FCFSOperatingSystem::currentJobFinshCall(const DateTime& now) {
	if (!this->jcbList.empty()) {
		this->jcbList.pop();
	}
}