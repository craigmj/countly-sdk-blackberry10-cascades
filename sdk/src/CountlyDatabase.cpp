/*
 * CountlyDatabase.cpp
 *
 *  Created on: 25 Jan 2013
 *      Author: craig
 */

#include "CountlyDatabase.hpp"
#include <string>

#include "Countly.hpp"

namespace countly {

CountlyLog CountlyDatabase::log("CountlyDatabase");

CountlyDatabase::CountlyDatabase(QObject *parent, long maxPersistedSessions, long sessionsExpireAfter) : QObject(parent) {
	// Only store a maximum of 5 sessions of data
	_max_persisted_sessions = (maxPersistedSessions==-1) ? 5 : maxPersistedSessions;
	// Any sessions older than 2 weeks are expired
	_sessions_expire_after = (-1==sessionsExpireAfter) ? 14 * 24 * 60 * 60 : sessionsExpireAfter;
}

CountlyDatabase::~CountlyDatabase() {
	close();
}

void
CountlyDatabase::close() {
	if (NULL!=_db) {
		sqlite3_finalize(_insert);
		sqlite3_finalize(_delete);
		sqlite3_close_v2(_db);
	}
	COUNTLY_DEBUG(log, "Closed database");
}

void
CountlyDatabase::openDatabase(const QString &name) {
	QDir dir = QDir::home();
	openDatabaseWithPath(QDir::home().absoluteFilePath(name + ".db"));
}

void
CountlyDatabase::openDatabaseWithPath(const QString &path) {
	int res = sqlite3_initialize();
	if (SQLITE_OK!=res) {
		COUNTLY_SEVERE(log, "ERROR on sqlite3_initialize:" << res);
		return;
	}

	COUNTLY_DEBUG(log, "Opening database " << path);
	res = sqlite3_open_v2(
			path.toAscii(),
			&_db,
			SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX,
			NULL);

	if (SQLITE_OK!=res) {
		COUNTLY_SEVERE(log, "Error opening database " << path << ": " << sqlite3_errmsg(_db));
		close();
		return;
	}

	res = sqlite3_exec(_db, "create table if not exists ctly_queue (id integer primary key not null, url varchar(8192) not null)", NULL, NULL, NULL);
	if (SQLITE_OK!=res) {
		COUNTLY_SEVERE(log, "Error creating table ctly_queue: " << sqlite3_errmsg(_db));
		close();
		return;
	}

	res = sqlite3_exec(_db, "create table if not exists ctly_session (start integer primary key not null, glbid int not null)", NULL, NULL, NULL);
	if (SQLITE_OK!=res) {
		COUNTLY_SEVERE(log, "Error creating table ctly_session: " << sqlite3_errmsg(_db));
		close();
		return;
	}

//	purge();

	// Work out the greatest lowest bound id in the queue (glbid)
	sqlite3_stmt *glb;
	res = sqlite3_prepare_v2(_db, "select max(id) from ctly_queue", -1, &glb, NULL);
	if (SQLITE_OK!=res) {
		COUNTLY_SEVERE(log, "Error on preparing glbid select: " << sqlite3_errmsg(_db));
		close();
		return;
	}
	if (SQLITE_ROW != sqlite3_step(glb)) {
		COUNTLY_SEVERE(log, "Error retrieving max glbid: " << sqlite3_errmsg(_db));
		close();
		return;
	}
	long maxid = sqlite3_column_int64(glb, 0);
	sqlite3_finalize(glb);

	sqlite3_stmt *session;
	res = sqlite3_prepare_v2(_db, "insert into ctly_session(start, glbid) values (?, ?)", -1, &session, NULL);
	if (SQLITE_OK != res) {
		COUNTLY_SEVERE(log, "Error preparing session insert: " << sqlite3_errmsg(_db));
		close();
		return;
	}

	long sessionStart = Countly::secondsSinceEpoch();


	if (SQLITE_OK != sqlite3_bind_int64(session, 1, sessionStart)) {
		COUNTLY_SEVERE(log, "Error binding start to ctly_session insert: " << sqlite3_errmsg(_db));
		close();
		return;
	}
	if (SQLITE_OK != sqlite3_bind_int64(session, 2, maxid)) {
		COUNTLY_SEVERE(log, "Error binding maxid to ctly_session insert: " << sqlite3_errmsg(_db));
		close();
		return;

	}
	if (SQLITE_DONE != (res = sqlite3_step(session))) {
		COUNTLY_WARN(log, "Error executing session insert: " << sqlite3_errmsg(_db));
		// Note that we don't close here - this could occur if we have 2 startups in 1 second, in which case
		// we're ok to assume that this is the same session.
	}

	sqlite3_finalize(session);

	deleteOldSessions();

	res = sqlite3_prepare_v2(_db, "insert into ctly_queue(url) values (?)", -1, &_insert, NULL);
	if (SQLITE_OK != res) {
		COUNTLY_SEVERE(log, "Error preparing insertion: " << sqlite3_errmsg(_db));
		close();
		return;
	}

	res = sqlite3_prepare_v2(_db, "delete from ctly_queue where id=?", -1, &_delete, NULL);
	if (SQLITE_OK != res) {
		COUNTLY_SEVERE(log, "Error preparing deletion: " << sqlite3_errmsg(_db));
		close();
		return;
	}

	COUNTLY_DEBUG(log, "Successfully opened database " << path);
}

/**
 * Delete any old session data that for some or other reason has not been transmitted
 * to the server.
 * This could be because there is something wrong with the data, or because the server has been
 * unavailable.
 * Our idea here is that we delete data if both of two things are true:
 * 1. The data is older than a session that is more than 2 weeks old.
 * 2. There are five more recent sessions.
 */
void
CountlyDatabase::deleteOldSessions() {
	sqlite3_stmt *session;
	int res;
	Q_UNUSED(res);
	if (SQLITE_OK != sqlite3_prepare_v2(_db, "select start, glbid from ctly_session order by start desc", -1, &session, NULL)) {
		COUNTLY_SEVERE(log, "Error preparing session cleanup: " << sqlite3_errmsg(_db));
		return;
	}

	long currentTime = Countly::secondsSinceEpoch();
	long glbid = -1;
	int sessionCount = 0;

	while (SQLITE_ROW == sqlite3_step(session)) {
		sessionCount++;
		if (_max_persisted_sessions>=sessionCount) continue;
		if (currentTime - sqlite3_column_int64(session, 0) > _sessions_expire_after) {
			glbid = sqlite3_column_int64(session, 1);
			break;
		}
	}
	sqlite3_finalize(session);

	COUNTLY_DEBUG(log, "deleteOldSessions: " << sessionCount << " sessions recorded");
	// Did we find a session(s) that should be deleted?
	if (-1<glbid) {
		sqlite3_stmt *deleteQueue;
		sqlite3_stmt *deleteSessions;

		COUNTLY_DEBUG(log, "Deleting sessions where glbid < " << glbid);

		res = sqlite3_prepare_v2(_db, "delete from ctly_session where glbid < ?", -1, &deleteSessions, NULL);
		Q_ASSERT(SQLITE_OK==res);
		sqlite3_bind_int64(deleteSessions, 1, glbid);
		sqlite3_step(deleteSessions);
		sqlite3_finalize(deleteSessions);

		COUNTLY_DEBUG(log, "Deleting queued data where glbid < " << glbid);
		res = sqlite3_prepare_v2(_db, "delete from ctly_queue where id <= ?", -1, &deleteQueue, NULL);
		Q_ASSERT(SQLITE_OK==res);
		sqlite3_bind_int64(deleteQueue, 1, glbid);
		sqlite3_step(deleteQueue);
		sqlite3_finalize(deleteQueue);
	}
}

void
CountlyDatabase::storeUrl(CountlyQueuedUrl *url) {
	if (0 > url->id()) {	// This url hasn't been stored yet
		std::string urlText(url->url().toString().toStdString());
		int res = sqlite3_bind_text(_insert, 1, urlText.c_str(), -1, NULL);
		if (SQLITE_OK != res) {
			COUNTLY_SEVERE(log, "Error on Insert binding url " << urlText << ": " << sqlite3_errmsg(_db));
			return;
		}
		res = sqlite3_step(_insert);
		if (SQLITE_DONE != res) {
			COUNTLY_SEVERE(log, "Error executing insert " << urlText << ": " << sqlite3_errmsg(_db));
		} else {
			long id = sqlite3_last_insert_rowid(_db);
//			COUNTLY_DEBUG(log, "Inserted (" << id << "): " << urlText);
			url->id(id);
		}
		sqlite3_reset(_insert);
	}
}

void
CountlyDatabase::purge() {
	sqlite3_exec(_db, "delete from ctly_queue", NULL, NULL, NULL);
	sqlite3_exec(_db, "delete ctly_session", NULL, NULL, NULL);
}

void
CountlyDatabase::deleteUrl(CountlyQueuedUrl *url) {
	if (0 <= url->id()) {	// If the url id < 0 => the record hasn't been stored to the db
		int res = sqlite3_bind_int64(_delete, 1, url->id());
		if (SQLITE_OK != res) {
			COUNTLY_SEVERE(log, "Error on Delete binding id " << url->id() << ": " << sqlite3_errmsg(_db));
			return;
		}
		res = sqlite3_step(_delete);
		if (SQLITE_DONE != res) {
			COUNTLY_SEVERE(log, "Error executing delete " << url->id() << ": " << sqlite3_errmsg(_db));
		} else {
			url->id(-1);
		}
		sqlite3_reset(_delete);
	}
}


void
CountlyDatabase::fetchAll(QObject *parent, QList<CountlyQueuedUrl *> *list) {
	sqlite3_stmt *fetch = NULL;
	int res = sqlite3_prepare_v2(_db, "select id, url from ctly_queue order by id", -1, &fetch, NULL);
	if (SQLITE_OK != res) {
		COUNTLY_SEVERE(log, "Failed to prepare select for fetchAll");
		sqlite3_finalize(fetch);
		return;
	}
	while (SQLITE_ROW == (res = sqlite3_step(fetch))) {
		long id = sqlite3_column_int64(fetch, 0);
		QString urlText  = (const char *) sqlite3_column_text(fetch, 1);
		QUrl url = QUrl(urlText);
		CountlyQueuedUrl *queueUrl = new CountlyQueuedUrl(parent, url, id);
		list->append(queueUrl);
//		COUNTLY_DEBUG(log, "Fetched " << urlText << " (" << id << ")");
	}
	if (SQLITE_DONE != res) {
		COUNTLY_SEVERE(log, "Error on step in fetchAll: " << sqlite3_errmsg(_db));
	}
	sqlite3_finalize(fetch);
}


} /* namespace countly */
