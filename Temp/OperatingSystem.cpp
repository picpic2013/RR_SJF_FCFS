#include "OperatingSystem.h"
OperatingSystem::OperatingSystem() {
}

OperatingSystem::~OperatingSystem() {
}

void OperatingSystem::registJob(const JCB& j) {
	this->jcbList.push_back(j);
}