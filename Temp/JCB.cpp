#include "JCB.h"

JCB JCB::EMPTY_JOB = JCB(-10086, "__EMPTY_JOB__", 0, 0);

JCB::JCB() : JCB(-1, "Unnamed", DateTime::UNKNOWN, -1) {
}

JCB::JCB(const JCB& j) : id(j.id), name(j.name), submitTime(j.submitTime),
	timeRequired(j.timeRequired), waitTime(j.waitTime), totalTime(j.totalTime),
	beginTime(j.beginTime), endTime(j.endTime),
	rightTotal(j.rightTotal), runningTime(0) {
}

JCB::JCB(int id, const std::string& name,
	const DateTime& submitTime, int timeRequired) : 
	id(id), name(name), submitTime(submitTime), 
	timeRequired(timeRequired), waitTime(-1), totalTime(-1), 
	beginTime(DateTime::UNKNOWN), endTime(DateTime::UNKNOWN), 
	rightTotal(-1), runningTime(0){
}

JCB::~JCB() {
}

void JCB::update(const DateTime& now) {
	this->waitTime = now - this->submitTime;
}

bool JCB::hasBegin() const {
	return this->beginTime != DateTime::UNKNOWN;
}

bool JCB::hasEnd() const {
	return this->endTime != DateTime::UNKNOWN;
}

void JCB::taskBegin(const DateTime& now) {
	if (this->beginTime != DateTime::UNKNOWN) {
		return;
	}
	this->beginTime = now;
	this->waitTime = now - this->submitTime;
}

void JCB::taskFinish(const DateTime& now) {
	if (this->endTime != DateTime::UNKNOWN) {
		return;
	}
	this->endTime = now;
	this->totalTime = now - this->submitTime;
	this->rightTotal = static_cast<double>(this->totalTime) / this->timeRequired;
}

int JCB::getID() const {
	return this->id;
}

std::string JCB::getName() const {
	return this->name;
}

int JCB::getTimeRequired() const {
	return this->timeRequired;
}

int JCB::getWaitTime() const {
	return this->waitTime;
}

int JCB::getTotalTime() const {
	return this->totalTime;
}

int JCB::getRunningTime() const {
	return this->runningTime;
}

bool JCB::hasFinished() const {
	return this->runningTime >= this->timeRequired;
}

void JCB::runJob(int runTime) {
	this->runningTime += runTime;
}

DateTime JCB::getSubmitTime() const {
	return this->submitTime;
}

DateTime JCB::getBeginTime() const {
	return this->beginTime;
}

DateTime JCB::getEndTime() const {
	return this->endTime;
}

double JCB::getRightTotal() const {
	return this->rightTotal;
}

void JCB::setTimeRequired(const int t) {
	this->timeRequired = t;
}

bool JCB::operator ==(const JCB& j) {
	return this->id == j.id;
}

bool JCB::operator !=(const JCB& j) {
	return this->id != j.id;
}