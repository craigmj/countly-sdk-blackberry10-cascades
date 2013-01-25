/*
 * CountlyQueue.hpp
 *
 *  Created on: 11 Jan 2013
 *      Author: craig
 *
 *  (c) 2013 Craig Mason-Jones. All Right Reserved.
 *  Please see LICENCE for licence details.
 *
 */

#ifndef COUNTLYQUEUE_HPP_
#define COUNTLYQUEUE_HPP_

#include <QObject>
#include <QThread>
#include <QAtomicInt>

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

#include <bb/cascades/Application>

#include "CountlyLog.hpp"
#include "CountlyQueuedUrl.hpp"
#include "CountlyDatabase.hpp"

namespace countly {

/**
 * Queues a list of URLs for delivery.
 * Each URL is held in the queue until flush() is called.
 * At that point, urls are requested in a fifo manner until the queue is empty or failure.
 */
class CountlyQueue : public QObject {
	Q_OBJECT
protected:
	static CountlyLog log;

	/// Lock to indicate when a flush is in progress
	QAtomicInt _flushInProgress;
	/// Lock to synchronize access to the queue
	QAtomicInt _queueLock;
	/// Queue of urls to be fetched
	QList<CountlyQueuedUrl *> _queue;

	CountlyDatabase *_database;

	QNetworkAccessManager _manager;

public:
	CountlyQueue(QObject *parent);
	virtual ~CountlyQueue();

	/**
	 * Set the queue's database.
	 * If this method is not called, events won't be persisted to a database.
	 * @param name Name of the database.
	 * @param maxPersistedSessions The maximum number of sessions to be persisted in the
	 * database. If more than this number is persisted, sessions will be purged when they
	 * exceed the number of seconds specified in sessionsExpireAfter.
	 * @param sessionsExpireAfter A maximum number of seconds for which a session will be
	 * persisted. Any sessions older than this (and if there are more than maxPersistedSessions)
	 * will be purged.
	 */
	void setDatabase(const QString &name, long maxPersistedSessions=-1, long sessionsExpireAfter=-1);

	/** Queue a URL for delivery */
	void queue(const QUrl &url);

	/** Flush the queue - send all pending URL's */
	void flush();

	/**
	 * Flush the queue and wait for n seconds.
	 * This is useful on stopApp, because it will start the flush, then wait for the given
	 * number of seconds before returning.
	 */
	void flushAndWait(bb::cascades::Application *app, int seconds=5);

public slots:
	void processorNetworkInaccessible();
	void processorDelivered(CountlyQueuedUrl *);
	void processorDeliveryError(CountlyQueuedUrl *, bool willRetry, const QString &message);
	void processorFlushCompleted();

};
} /* namespace countly */
#endif /* COUNTLYQUEUE_HPP_ */
