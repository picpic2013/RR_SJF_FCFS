#include "DateTime.h"
#include<iomanip>

const DateTime DateTime::UNKNOWN = DateTime(10086, 99, 99, 99);

DateTime::DateTime() : DateTime(0, 0, 0, 0) {
}

DateTime::DateTime(int sec) {
	this->sec = sec % 60;
	this->min = (sec /= 60) % 60;
	this->hour = (sec /= 60) % 60;
	this->day = sec /= 24;
}

DateTime::DateTime(const DateTime& t) : DateTime(t.day, t.hour, t.min, t.sec){
}

DateTime::DateTime(const int day, const int hour, const int min, const int sec) {
	this->day = day;
	this->hour = hour;
	this->min = min;
	this->sec = sec;
}

DateTime::DateTime(const int hour, const int min) : DateTime(0, hour, min, 0) {
}

DateTime::~DateTime() {
}

void DateTime::tick(const int add) {
	this->sec += add;
	update();
}
void DateTime::tickMin(const int add) {
	this->min += add;
	update();
}

void DateTime::tickHour(const int add) {
	this->hour += add;
	update();
}

void DateTime::tickDay(const int add) {
	this->day += day;
	update();
}

int DateTime::getDay() const {
	return this->day;
}

int DateTime::getHour() const {
	return this->hour;
}

int DateTime::getMin() const {
	return this->min;
}

int DateTime::getSec() const {
	return this->sec;
}

void DateTime::setDay(const int day) {
	this->day = day;
}

void DateTime::setHour(const int hour) {
	this->hour = hour;
}

void DateTime::setMin(const int min) {
	this->min = min;
}

void DateTime::setSec(const int sec) {
	this->sec = sec;
}

void DateTime::update() {
	while (this->sec >= 60) {
		++this->min;
		this->sec -= 60;
	}
	while (this->min >= 60) {
		++this->hour;
		this->min -= 60;
	}
	while (this->hour >= 24) {
		++this->day;
		this->hour -= 24;
	}
}

std::ostream& operator<<(std::ostream& out, const DateTime& date) {
	out << "Day " << date.day << " - " 
		<< std::setw(2) << std::setfill('0') << date.hour << ":" 
		<< std::setw(2) << std::setfill('0') << date.min << ":" 
		<< std::setw(2) << std::setfill('0') << date.sec;
	return out;
}

bool DateTime::operator==(const DateTime& t) const {
	return this->day == t.day &&
		this->hour == t.hour &&
		this->min == t.min &&
		this->sec == t.sec;
}

bool DateTime::operator!=(const DateTime& t) const {
	return !(*this == t);
}

const int DateTime::operator-(const DateTime& t) const {
	return (this->day - t.day) * 3600 * 24 +
		(this->hour - t.hour) * 3600 +
		(this->min - t.min) * 60 +
		(this->sec - t.sec);
}

DateTime::operator int() const {
	return this->day * 3600 * 24 + this->hour * 3600 + this->min * 60 + this->sec;
}