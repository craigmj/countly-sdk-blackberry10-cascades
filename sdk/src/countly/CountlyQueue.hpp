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

#include "CountlyLog.hpp"
#include "CountlyQueuedUrl.hpp"

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

public:
	CountlyQueue(QObject *parent);
	virtual ~CountlyQueue();

	/** Queue a URL for delivery */
	void queue(const QUrl &url);

	/** Flush the queue - send all pending URL's */
	void flush();

	/**
	 * Flush the queue and wait for n seconds.
	 * This is useful on stopApp, because it will start the flush, then wait for the given
	 * number of seconds before returning.
	 */
	void flushAndWait(int seconds=5);

public slots:
	void processorNetworkInaccessible();
	void processorDelivered(CountlyQueuedUrl *);
	void processorDeliveryError(CountlyQueuedUrl *, const QString &message);
	void processorFlushCompleted();

};
} /* namespace countly */
#endif /* COUNTLYQUEUE_HPP_ */
