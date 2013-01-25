/*
 * CountlyDatabase.hpp
 *
 *  Created on: 25 Jan 2013
 *      Author: craig
 */

#ifndef COUNTLYDATABASE_HPP_
#define COUNTLYDATABASE_HPP_

#include <QObject>

#include <QDir>
#include <QList>
#include <QString>

#include <sqlite3.h>

#include "CountlyLog.hpp"
#include "CountlyQueuedUrl.hpp"

namespace countly {


/**
 * CountlyDatabase stores Countly URL requests before they are sent. They are deleted on delivery.
 * In this manner, even if the device is offline, activity can still be recorded for analytics purposes.
 */
class CountlyDatabase : public QObject {
	Q_OBJECT
protected:
	static CountlyLog log;
	sqlite3 *_db;

	sqlite3_stmt *_insert;
	sqlite3_stmt *_delete;

	long _max_persisted_sessions;
	long _sessions_expire_after;

public:
	CountlyDatabase(QObject *parent, long maxPersistedSessions=-1, long sessionsExpireAfter=-1);
	virtual ~CountlyDatabase();
	void close();

	void openDatabase(const QString &dbName);

	void storeUrl(CountlyQueuedUrl *url);
	void deleteUrl(CountlyQueuedUrl *url);
	void fetchAll(QObject *parent, QList<CountlyQueuedUrl *> *list);

	void purge();
protected:
	void openDatabaseWithPath(const QString &path);
	void deleteOldSessions();
};

} /* namespace countly */
#endif /* COUNTLYDATABASE_HPP_ */
