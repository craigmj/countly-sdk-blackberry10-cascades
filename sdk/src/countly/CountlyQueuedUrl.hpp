/*
 * CountlyQueuedUrl.hpp
 *
 *  Created on: 25 Jan 2013
 *      Author: craig
 */

#ifndef COUNTLYQUEUEDURL_HPP_
#define COUNTLYQUEUEDURL_HPP_

#include <QObject>
#include <QUrl>

namespace countly {

/**
 * URL queued for delivery.
 */
class CountlyQueuedUrl : public QObject {
	Q_OBJECT
protected:
	QUrl _url;
	long _id;
public:
	CountlyQueuedUrl(QObject *parent, const QUrl &url, long id=-1);
	virtual ~CountlyQueuedUrl();

	const QUrl &url() const { return _url; }
	long id() const { return _id; }
	void id(long id) { _id=id; }
};

} /* namespace countly */
#endif /* COUNTLYQUEUEDURL_HPP_ */
