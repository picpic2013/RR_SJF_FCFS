#include "FCFSOperatingSystem.h"
#include <iostream>

FCFSOperatingSystem::FCFSOperatingSystem() : OperatingSystem() {
}

FCFSOperatingSystem::~FCFSOperatingSystem() {
}

void FCFSOperatingSystem::interrupt() {
}

void FCFSOperatingSystem::registJob(const JCB& j) {
	this->jcbList.push(j);
}

JCB& FCFSOperatingSystem::getCurrentJob() {
	if (this->jcbList.empty()) {
		return JCB::EMPTY_JOB;
	}
	return this->jcbList.front();
}

void FCFSOperatingSystem::currentJobFinshCall() {
	this->jcbList.pop();
}