#pragma once
#include <iostream>
class DateTime {
public:
	DateTime();
	DateTime(int sec);
	DateTime(const DateTime& t);
	DateTime(const int day, const int hour, const int min, const int sec);
	DateTime(const int hour, const int min);
	~DateTime();

	void tick(const int add = 1);
	void tickMin(const int add = 1);
	void tickHour(const int add = 1);
	void tickDay(const int add = 1);

	int getDay() const;
	int getHour() const;
	int getMin() const;
	int getSec() const;

	void setDay(const int day);
	void setHour(const int hour);
	void setMin(const int min);
	void setSec(const int sec);

	friend std::ostream& operator<<(std::ostream& out, const DateTime& date);
	bool operator==(const DateTime& t) const;
	bool operator!=(const DateTime& t) const;
	const int operator-(const DateTime& t) const;

	operator int() const;

	const static DateTime UNKNOWN;

private:
	int day, hour, min, sec;
	void update();
};