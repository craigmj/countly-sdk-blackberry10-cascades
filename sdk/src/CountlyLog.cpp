/*
 * CountlyLog.cpp
 *
 *  Created on: 18 Jan 2013
 *      Author: craig
 *
 *  (c) 2013 Craig Mason-Jones. All Right Reserved.
 *  Please see LICENCE for licence details.
 *
 */

#include "CountlyLog.hpp"

#include <QDebug>
#include <QtDeclarative>

namespace countly {

using namespace std;

CountlyLog::CountlyLog(const char *logName, QObject *parent) : QObject(parent), _logName(logName) {
}

CountlyLog::~CountlyLog() {
}

CountlyLogStream
CountlyLog::trace() {
	return CountlyLogStream(this, LogLevel::TRACE);
}

CountlyLogStream
CountlyLog::debug() {
	return CountlyLogStream(this, LogLevel::DEBUG);
}

CountlyLogStream
CountlyLog::info() {
	return CountlyLogStream(this, LogLevel::INFO);
}

CountlyLogStream
CountlyLog::warn() {
	return CountlyLogStream(this, LogLevel::WARN);
}

CountlyLogStream
CountlyLog::severe() {
	return CountlyLogStream(this, LogLevel::SEVERE);
}


void
CountlyLog::log(LogLevel::Level lvl, const char *message) {
	const char *level = "-";
	switch (lvl) {
	case LogLevel::TRACE:
		level = "TRACE"; break;
	case LogLevel::DEBUG:
		level = "DEBUG"; break;
	case LogLevel::INFO:
		level = "INFO "; break;
	case LogLevel::WARN:
		level = "WARN "; break;
	case LogLevel::SEVERE:
		level = "SVRE "; break;
	}
	qDebug() << level << " : " << _logName.c_str() << " : "  << message;

	fprintf(stdout, "%s : %s : %s\n", level, _logName.c_str(), message);
	fflush(stdout);
}



} /* namespace countly */
