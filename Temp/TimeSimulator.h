#pragma once
#include <map>
#include "DateTime.h"
#include "OperatingSystem.h"

class TimeSimulator {
public:
	TimeSimulator(OperatingSystem& sys, 
		const DateTime timeInterval, 
		const DateTime interruptInterval);
	~TimeSimulator();

	void init(const DateTime& t = DateTime::UNKNOWN);
	void setTimeInterval(const DateTime& t);
	void setInterruptInterval(const DateTime& t);
	void update();
	void registerJob(const JCB& jcb);

private:
	DateTime now, nextInterrupt, interruptInterval, timeInterval;
	OperatingSystem& sys;
	
	std::map<DateTime, JCB> jcbList;
};

TimeSimulator::TimeSimulator(OperatingSystem& sys, 
	const DateTime timeInterval, const DateTime interruptInterval) :
	sys(sys), timeInterval(timeInterval), interruptInterval(timeInterval) {
	init();
}

TimeSimulator::~TimeSimulator() {
}

void TimeSimulator::init(const DateTime& t = DateTime::UNKNOWN) {
	if (t == DateTime::UNKNOWN) {
		this->now = DateTime();
	}
	else {
		this->now = t;
	}
	this->nextInterrupt = this->now + interruptInterval;
}

void TimeSimulator::setTimeInterval(const DateTime& t) {
	this->timeInterval = t;
}

void TimeSimulator::setInterruptInterval(const DateTime& t) {
	this->interruptInterval = t;
}

void TimeSimulator::update() {
	if (this->now > this->nextInterrupt) {
		this->sys.interrupt();
		this->nextInterrupt = this->nextInterrupt + this->interruptInterval;
	}
	if (this->jcbList.find(this->now) != this->jcbList.end()) {
		sys.registJob(this->jcbList[this->now]);
	}
	this->now = this->now + this->timeInterval;
}

void TimeSimulator::registerJob(const JCB& jcb) {
	this->jcbList.insert(std::make_pair(jcb.getBeginTime(), jcb));
}