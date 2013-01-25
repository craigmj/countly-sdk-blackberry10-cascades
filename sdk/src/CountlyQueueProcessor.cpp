/*
 * CountlyQueueProcessor.cpp
 *
 *  Created on: 25 Jan 2013
 *      Author: craig
 */

#include "CountlyQueueProcessor.hpp"

#include <QObject>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

#include <bb/data/DataAccessError>
#include <bb/data/JsonDataAccess>

#include "CountlySentry.hpp"

using namespace bb::data;

namespace countly {


CountlyLog CountlyQueueProcessor::log("CountlyQueueProcessor");

CountlyQueueProcessor::CountlyQueueProcessor(QObject *parent, QNetworkAccessManager *manager, QAtomicInt *queueLock, QList<CountlyQueuedUrl *> *queue) :
	QObject(parent), _manager(manager), _queueLock(queueLock), _queue(queue)
{
	if (!connect(_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(requestFinished(QNetworkReply *)))) {
		COUNTLY_SEVERE(log, "failed to connect _manager::finished to CountlyQueueProcessor::finished");
	}
}

CountlyQueueProcessor::~CountlyQueueProcessor() {
	// nothing to do  - all replies should delete through QObject framework
}

void
CountlyQueueProcessor::process() {
	CountlySentry lock(_queueLock);
	COUNTLY_DEBUG(log, "processing: queue.length() = " << _queue->length());
	if (0==_queue->length()) {
		emit flushCompleted();
		deleteLater();	// delete ourself, and all associated request / replies
		return;
	}
	if (_manager->networkAccessible() == QNetworkAccessManager::NotAccessible) {
		COUNTLY_DEBUG(log, "Network not accessible");
		emit networkInaccessible();
		emit flushCompleted();
		deleteLater();
		return;
	}
	CountlyQueuedUrl *url = _queue->at(0);
	QNetworkRequest request(url->url());
	COUNTLY_DEBUG(log, "GET request starting: " << url->url().toString());
	QNetworkReply *reply = _manager->get(request);
	if (NULL==reply) {
		COUNTLY_WARN(log, "_manager.get return NULL reply for url " << url->url().toString());
		return;
	}
	if (!connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
			this, SLOT(requestError(QNetworkReply::NetworkError)))) {
		COUNTLY_SEVERE(log, "Failed to connect to reply error signal");
	}
	reply->setParent(this);	// So that the reply will be deleted when we delete ourselves
}

void
CountlyQueueProcessor::requestError(QNetworkReply::NetworkError error) {
	Q_UNUSED(error);
	COUNTLY_INFO(log, "Network error on reply: " << error);
}

void
CountlyQueueProcessor::requestFinished(QNetworkReply *reply) {
	QString resultJson(reply->readAll());
	COUNTLY_DEBUG(log, "finished request " << reply->request().url().toString() << "\n"	\
			<< "Read: " << resultJson);
	CountlyQueuedUrl *url = _queue->at(0);
	if (QNetworkReply::NoError != reply->error()) {
		QString errorMessage;
		errorMessage.sprintf("QNetworkReply::NetworkError : %d", reply->error());
		emit deliveryError(url, true, errorMessage);
		emit flushCompleted();
		deleteLater();
		return;
	}
	// Check that we got json from the server
	JsonDataAccess json;
	QVariant result = json.loadFromBuffer(resultJson);
	if (json.hasError()) {
		emit deliveryError(url, true, json.error().errorMessage());
		emit flushCompleted();
		deleteLater();
		return;
	}
	// If we get json from the server, but not success, we assume there is
	// something wrong with our URL.
	bool succeeded = result.toMap()["result"].toString()=="Success";

	if (!succeeded) {
		emit deliveryError(url, false, result.toMap()["result"].toString());
	}
	{
		CountlySentry lock(_queueLock);
		_queue->pop_front();
	}
	emit delivered(url);
	process();	// Process the next URL in the queue, or exit if we're done
}

} /* namespace countly */
