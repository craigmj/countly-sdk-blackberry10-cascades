/*
 * CountlyRequest.hpp
 *
 *  Created on: 11 Jan 2013
 *      Author: craig
 */

#ifndef COUNTLYREQUEST_HPP_
#define COUNTLYREQUEST_HPP_

#include <QObject>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

#include "CountlyLog.hpp"

namespace countly {

class CountlyRequest : public QObject {
	Q_OBJECT
protected:
	static CountlyLog log;

	QNetworkRequest request;
	QNetworkAccessManager manager;
public:
	CountlyRequest(const QUrl &url) : QObject(NULL) {
		request.setUrl(url);
		log.debug() << "about to request " << url.toString();
		if (!connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)))) {
			log.severe() << "Failed to connect to manager.finished";
		}
		manager.get(request);
		log.debug() << "done with manager.get(..)";
	}
	virtual ~CountlyRequest();
public slots:
	void finished(QNetworkReply *reply) {
		log.debug() << "finished request " << request.url().toString();
		log.debug() << "Read: " << QString(reply->readAll());
		reply->deleteLater();
		deleteLater();
	}
};
} /* namespace countly */
#endif /* COUNTLYREQUEST_HPP_ */
