#include "RROperatingSystem.h"

RROperatingSystem::RROperatingSystem() : OperatingSystem() {
}

RROperatingSystem::~RROperatingSystem() {
}

void RROperatingSystem::interrupt(const DateTime& now) {
	if (!this->jcbList.empty()) {
		this->jcbList.push_back(this->jcbList.front());
		this->jcbList.pop_front();
	}
}

void RROperatingSystem::registJob(const JCB& j, const DateTime& now) {
	if (!this->jcbList.empty()) {
		JCB temp = this->jcbList.front();
		this->jcbList.pop_front();
		this->jcbList.push_front(j);
		this->jcbList.push_front(temp);
	}
	else {
		this->jcbList.push_front(j);
	}
}

JCB& RROperatingSystem::getCurrentJob(const DateTime& now) {
	if (!this->jcbList.size()) {
		return JCB::EMPTY_JOB;
	}
	return this->jcbList.front();
}
void RROperatingSystem::currentJobFinshCall(const DateTime& now) {
	this->jcbList.pop_front();
}