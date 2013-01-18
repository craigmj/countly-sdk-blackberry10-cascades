/*
 * CountlyLog.hpp
 *
 *  Created on: 18 Jan 2013
 *      Author: craig
 */

#ifndef COUNTLYLOG_HPP_
#define COUNTLYLOG_HPP_

#include <QObject>
#include <QString>

#include "CountlyLogStream.hpp"

namespace countly {

/**
 * Customizable Log framework abstraction to use with Countly.
 * Idea is to be able to quickly activate / deactivate logging, or to route logging to different
 * destinations, without needing to pull logging into/out of code at numerous points.
 */
class CountlyLog : public QObject {
	Q_OBJECT
protected:
	std::string _logName;
public:
	CountlyLog(const char *logName, QObject *parent=NULL);
	virtual ~CountlyLog();

	CountlyLogStream trace();
	CountlyLogStream debug();
	CountlyLogStream info();
	CountlyLogStream warn();
	CountlyLogStream severe();

	Q_INVOKABLE void trace(const QString &msg) { trace() << msg; }
	Q_INVOKABLE void debug(const QString &msg) { debug() << msg; }
	Q_INVOKABLE void info(const QString &msg) { info() << msg; }
	Q_INVOKABLE void warn(const QString &msg) { warn() << msg; }
	Q_INVOKABLE void severe(const QString &msg) { severe() << msg; }

	void log(LogLevel::Level level, const char *msg);
};

} /* namespace countly */
#endif /* COUNTLYLOG_HPP_ */
