/*
 * CountlyLog.hpp
 *
 *  Created on: 18 Jan 2013
 *      Author: craig
 *
 *  (c) 2013 Craig Mason-Jones. All Right Reserved.
 *  Please see LICENCE for licence details.
 *
 */

#ifndef COUNTLYLOG_HPP_
#define COUNTLYLOG_HPP_

#include <QObject>
#include <QString>

#include "CountlyLogStream.hpp"

/**
 * All Countly Log code can be quickly excluded from the app by undef'ing _DEBUG (or some other symbol if you prefer)
 */
#ifdef QT_DEBUG
#define COUNTLY_TRACE(log, msg) { log.trace() << msg; }
#define COUNTLY_DEBUG(log, msg) { log.debug() << msg; }
#define COUNTLY_INFO(log, msg) { log.info() << msg; }
#define COUNTLY_WARN(log, msg) { log.warn() << msg; }
#define COUNTLY_SEVERE(log, msg) { log.severe() << msg; }
#else
#define COUNTLY_TRACE(log, msg)
#define COUNTLY_DEBUG(log, msg)
#define COUNTLY_INFO(log, msg)
#define COUNTLY_WARN(log, msg)
#define COUNTLY_SEVERE(log, msg)
#endif


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
