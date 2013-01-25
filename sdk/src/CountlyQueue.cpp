/*
 * CountlyQueue.cpp
 *
 *  Created on: 11 Jan 2013
 *      Author: craig
 *
 *  (c) 2013 Craig Mason-Jones. All Right Reserved.
 *  Please see LICENCE for licence details.
 *
 */

#include "CountlyQueue.hpp"

#include <QObject>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

#include <bb/data/DataAccessError>
#include <bb/data/JsonDataAccess>
using namespace bb::data;


#include "CountlyQueueProcessor.hpp"
#include "CountlySentry.hpp"
#include "Countly.hpp"

namespace countly {

CountlyLog CountlyQueue::log("CountlyQueue");


CountlyQueue::CountlyQueue(QObject *parent) : QObject(parent) {
	_database = NULL;
}

CountlyQueue::~CountlyQueue() {
	if (NULL!=_database) {
		delete _database;
	}
}

void
CountlyQueue::flush() {
	// If _flushLock is already 1, then we're got a flush currently in progress, and we don't need to do anything more
	if (!_flushInProgress.testAndSetOrdered(0,1)) {
		COUNTLY_DEBUG(log, "A flush is already in progress - no new flush initiated");
		return;
	}
	COUNTLY_DEBUG(log, "Initiating new flush");

	CountlyQueueProcessor *processor = new CountlyQueueProcessor(this, &_manager, &_queueLock, &_queue);
	if (!connect(processor, SIGNAL(networkInaccessible()),
			this, SLOT(processorNetworkInaccessible()))) {
		COUNTLY_SEVERE(log, "Failed to connect processor networkInaccessible()");
	}
	if (!connect(processor, SIGNAL(delivered(CountlyQueuedUrl*)),
			this, SLOT(processorDelivered(CountlyQueuedUrl *)))) {
		COUNTLY_SEVERE(log, "Failed to connect processor delivered");
	}
	if (!connect(processor, SIGNAL(deliveryError(CountlyQueuedUrl*, bool, const QString &)),
			this, SLOT(processorDeliveryError(CountlyQueuedUrl*, bool, const QString &)))) {
		COUNTLY_SEVERE(log, "Failed to connect processor deliveryError");
	}
	if (!connect(processor, SIGNAL(flushCompleted()),
			this, SLOT(processorFlushCompleted()))) {
		COUNTLY_SEVERE(log, "Failed to connect processor flushCompleted");
	}
	processor->process();

	// The processor will delete itself upon completion
}

void
CountlyQueue::flushAndWait(bb::cascades::Application *app, int seconds) {
	flush();
	COUNTLY_DEBUG(log, "flush and wait for " << seconds << "s");
	qint64 now = Countly::secondsSinceEpoch();
	qint64 stop = now + seconds;
	qint64 extend = now + 1;
	while (1==_flushInProgress) {
		now = Countly::secondsSinceEpoch();
		if (stop<now) break;
		if (now >= extend) {
			// We keep giving ourselves 2 additional seconds until we reach our stop point
			app->extendTerminationTimeout();
			extend = now + 1;
		}
		QThread::yieldCurrentThread();
	}
	COUNTLY_DEBUG(log, "flush and wait finished, flushInProgress = " << _flushInProgress._q_value);
}

void
CountlyQueue::processorNetworkInaccessible() {
	COUNTLY_DEBUG(log, "Network inaccessible to Countly");
}

void
CountlyQueue::processorDelivered(CountlyQueuedUrl *url) {
	if (_database) {
		_database->deleteUrl(url);
	}
	COUNTLY_DEBUG(log, "Delivered URL : " << url->url().toString());
}

void
CountlyQueue::processorDeliveryError(CountlyQueuedUrl *url, bool willRetry, const QString &message) {
	Q_UNUSED(message);	// only used in DEBUG build
	if ((!willRetry) && (NULL!=_database)) {
		_database->deleteUrl(url);
	}
	COUNTLY_DEBUG(log, "Delivery error on URL " << url->url().toString() << " (willRetry = "
			<< (willRetry ? "YES" : "NO")
			<< ": " << message);
}

void
CountlyQueue::processorFlushCompleted() {
	bool completed = _flushInProgress.testAndSetOrdered(1,0);
	Q_ASSERT(completed);
	Q_UNUSED(completed);
	COUNTLY_DEBUG(log, "processor flush completed");
}


void
CountlyQueue::queue(const QUrl &url) {
	CountlyQueuedUrl *item = new CountlyQueuedUrl(this, url, -1);
	if (_database) {
		_database->storeUrl(item);
	}
	CountlySentry lock(&_queueLock);
	_queue.append(item);
	COUNTLY_DEBUG(log, "Queued: " << url.toString());
}

void
CountlyQueue::setDatabase(const QString &name, long maxPersistedSessions, long sessionsExpireAfter) {
	_database = new CountlyDatabase(this, maxPersistedSessions, sessionsExpireAfter);
	_database->openDatabase(name);
	_database->fetchAll(this, &_queue);
}
} /* namespace countly */
