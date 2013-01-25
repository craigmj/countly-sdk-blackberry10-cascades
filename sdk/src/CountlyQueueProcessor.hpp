/*
 * CountlyQueueProcessor.hpp
 *
 *  Created on: 25 Jan 2013
 *      Author: craig
 */

#ifndef COUNTLYQUEUEPROCESSOR_HPP_
#define COUNTLYQUEUEPROCESSOR_HPP_

#include "CountlyLog.hpp"
#include "CountlyQueuedUrl.hpp"


#include <QObject>

#include <QAtomicInt>

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

namespace countly {

/**
 * A queue processor is able to process the entire queue, and every request and reply is deleted when the
 * processor is completed.
 * Each success is also reported through a signal.
 */
class CountlyQueueProcessor : public QObject {
	Q_OBJECT
protected:
	static CountlyLog log;

	QNetworkAccessManager *_manager;
	QAtomicInt *_queueLock;
	QList<CountlyQueuedUrl *> *_queue;
public:
	CountlyQueueProcessor(QObject *parent, QNetworkAccessManager *manager, QAtomicInt *queueLock, QList<CountlyQueuedUrl *> *queue);
	virtual ~CountlyQueueProcessor();
	void process();

signals:
	void networkInaccessible();
	void delivered(CountlyQueuedUrl *);
	void deliveryError(CountlyQueuedUrl *, bool willRetry, const QString &message);
	void flushCompleted();

public slots:
	void requestFinished(QNetworkReply *reply);
	void requestError(QNetworkReply::NetworkError code);
};
} /* namespace countly */
#endif /* COUNTLYQUEUEPROCESSOR_HPP_ */
