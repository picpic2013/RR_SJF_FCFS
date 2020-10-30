#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include "DateTime.h"
#include "OperatingSystem.h"

class TimeSimulator {
public:
	enum OutputLevel {
		SILENT,
		EVERY_KEY_EVENT,
		EVERY_TIME_INTERVAL
	};
	TimeSimulator(OperatingSystem& sys, 
		const DateTime timeInterval, 
		const DateTime interruptInterval, 
		const OutputLevel outputLevel
	);
	~TimeSimulator();

	void init(const DateTime& t = DateTime::UNKNOWN);
	void setTimeInterval(const DateTime& t);
	void setInterruptInterval(const DateTime& t);
	void update();
	void registerJob(const JCB& jcb);
	void setOutputLevel(OutputLevel level);
	OutputLevel getOuputLevel() const;

	const DateTime& getNow() const;

private:
	DateTime now, nextInterrupt, interruptInterval, timeInterval;
	OperatingSystem& sys;
	OutputLevel outputLevel;

	struct JobCmpBySubmitTime {
		bool operator()(const JCB& a, const JCB& b);
	};
	
	std::priority_queue<JCB, std::vector<JCB>, JobCmpBySubmitTime> jcbList;
};