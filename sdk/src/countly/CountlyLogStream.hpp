/*
 * CountlyLogStream.hpp
 *
 *  Created on: 18 Jan 2013
 *      Author: craig
 *
 *  (c) 2013 Craig Mason-Jones. All Right Reserved.
 *  Please see LICENCE for licence details.
 *
 */

#ifndef COUNTLYLOGSTREAM_HPP_
#define COUNTLYLOGSTREAM_HPP_

#include <iostream>
#include <sstream>

#include <QString>

#include "CountlyLogLevel.hpp"

namespace countly {

class CountlyLog;

/**
 * A Stream class for writing log messages.
 */
class CountlyLogStream {
protected:
	CountlyLog *_log;
	LogLevel::Level _level;
	std::stringstream _message;
public:
	CountlyLogStream(CountlyLog *log, LogLevel::Level level);
	CountlyLogStream(const CountlyLogStream &rhs) { operator=(rhs); }
	virtual ~CountlyLogStream();
	template <class T>
	CountlyLogStream &operator <<(const T &in) { _message<<in; return *this; }
	CountlyLogStream &operator <<(const QString &in) { _message<<in.toUtf8().data(); return *this; }
	const CountlyLogStream &operator=(const CountlyLogStream &rhs) { _log=rhs._log; _level=rhs._level; return rhs; }
};

} /* namespace countly */
#endif /* COUNTLYLOGSTREAM_HPP_ */
