#pragma once
#include <string>
#include "DateTime.h"

class JCB {
public:
	JCB(const JCB& j);
	JCB(int id, const std::string& name,
		const DateTime& submitTime, int timeRequired);
	~JCB();

	void update(const DateTime& now);
	void taskBegin(const DateTime& now);
	void taskFinish(const DateTime& now);
	bool hasBegin() const;
	bool hasEnd() const;
	
	int getID() const;
	std::string getName() const;
	int getTimeRequired() const;
	int getWaitTime() const;
	int getTotalTime() const;
	DateTime getSubmitTime() const;
	DateTime getBeginTime() const;
	DateTime getEndTime() const;
	double getRightTotal() const;

	void setTimeRequired(const int t);

private:
	const int id;
	const std::string name;
	int timeRequired, waitTime, totalTime;
	DateTime submitTime, beginTime, endTime;
	double rightTotal;
};