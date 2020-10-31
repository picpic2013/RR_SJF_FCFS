#include "TimeSimulator.h"

TimeSimulator::TimeSimulator(OperatingSystem& sys,
	const DateTime timeInterval, const DateTime interruptInterval, 
	const OutputLevel outputLevel) :
	sys(sys), timeInterval(timeInterval), 
	interruptInterval(interruptInterval), 
	outputLevel(outputLevel) {
	init();
}

TimeSimulator::~TimeSimulator() {
}

void TimeSimulator::init(const DateTime& t) {
	if (t == DateTime::UNKNOWN) {
		this->now = DateTime();
	}
	else {
		this->now = t;
	}
	this->nextInterrupt = this->now;
}

void TimeSimulator::setTimeInterval(const DateTime& t) {
	this->timeInterval = t;
}

void TimeSimulator::setInterruptInterval(const DateTime& t) {
	this->interruptInterval = t;
}

bool TimeSimulator::update() {
	bool hasEvent = this->outputLevel == EVERY_TIME_INTERVAL ||
		(!this->jcbList.empty() && this->jcbList.top().getSubmitTime() <= this->now) ||
		this->now >= this->nextInterrupt ||
		(this->sys.getCurrentJob(this->now) != JCB::EMPTY_JOB && this->sys.getCurrentJob(this->now).hasFinished());
	if (this->outputLevel == SILENT) {
		hasEvent = false;
	}
	// output current time
	if (hasEvent) {
		std::cout << "now: " << this->now << std::endl;
	}
	// register job
	while (!this->jcbList.empty() && this->jcbList.top().getSubmitTime() <= this->now) {
		if (hasEvent) {
			std::cout << "Start Registering Job [ " << this->jcbList.top().getName()
				<< " ]... " << std::endl;
		}
		this->sys.registJob(this->jcbList.top(), this->now);
		if (hasEvent) {
			std::cout << "Finsh Registering Job [ " << this->jcbList.top().getName()
				<< " ]... " << std::endl;
		}
		this->jcbList.pop();
	}
	// call interrupt 
	if (this->now >= this->nextInterrupt) {
		if (hasEvent) {
			std::cout << "Calling Operating System Interrupt Function..." << std::endl;
		}
		this->sys.interrupt(this->now);
		if (hasEvent) {
			std::cout << "Finsh Operating System Interrupt Function." << std::endl;
		}
		this->nextInterrupt = this->nextInterrupt + this->interruptInterval;
	}
	// has job
	if (this->sys.getCurrentJob(this->now) != JCB::EMPTY_JOB) {
		this->sys.getCurrentJob(this->now).taskBegin(this->now);
		// run job
		if (this->outputLevel == EVERY_TIME_INTERVAL) {
			std::cout << "Start Running Job [ " << this->sys.getCurrentJob(this->now).getName()
				<< " ]... " << std::endl;
		}
		if (hasEvent && this->outputLevel == EVERY_KEY_EVENT) {
			std::cout << "Current Running Job [ " << this->sys.getCurrentJob(this->now).getName()
				<< " ]... " << std::endl;
		}
		this->sys.getCurrentJob(this->now).runJob(this->timeInterval);
		if (this->outputLevel == EVERY_TIME_INTERVAL) {
			std::cout << "Stop Running Job [ " << this->sys.getCurrentJob(this->now).getName()
				<< " ]... " << std::endl;
		}
		// update time
		this->now = this->now + this->timeInterval;
		// has finish
		if (this->sys.getCurrentJob(this->now).hasFinished()) {
			if (hasEvent) {
				std::cout << "Job [ " << this->sys.getCurrentJob(this->now).getName()
					<< " ] Finished." << std::endl;
			}
			this->sys.getCurrentJob(this->now).taskFinish(this->now);
			this->endList.push_back(sys.getCurrentJob(this->now));
			this->sys.currentJobFinshCall(this->now);
		}
	}
	else {
		// update time
		this->now = this->now + this->timeInterval;
	}
	if (hasEvent) {
		std::cout << "---------------------------------------------" << std::endl;
	}
	if (this->jcbList.empty() && sys.getCurrentJob(this->now) == JCB::EMPTY_JOB) {
		return false;
	}
	return true;
}

void TimeSimulator::registerJob(const JCB& jcb) {
	this->jcbList.push(jcb);
}

void TimeSimulator::setOutputLevel(TimeSimulator::OutputLevel level) {
	this->outputLevel = level;
}

TimeSimulator::OutputLevel TimeSimulator::getOuputLevel() const {
	return this->outputLevel;
}

const DateTime& TimeSimulator::getNow() const {
	return this->now;
}

const std::vector<JCB>& TimeSimulator::getEndList() const {
	return this->endList;
}

bool TimeSimulator::JobCmpBySubmitTime::operator()(const JCB& a, const JCB& b) {
	return a.getSubmitTime() > b.getSubmitTime();
}