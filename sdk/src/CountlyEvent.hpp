/*
 * CountlyEvent.hpp
 *
 *  Created on: 11 Jan 2013
 *      Author: craig
 */

#ifndef COUNTLYEVENT_HPP_
#define COUNTLYEVENT_HPP_

#include <QObject>
#include <QString>
#include <QUrl>
#include <QVariant>

#include "CountlyLog.hpp"

namespace countly {

class CountlyEvent : public QObject {
	Q_OBJECT
protected:
	static CountlyLog log;
	QString _key;
	int _count;
	double _sum;
	QVariantMap _segmentation;
public:
	CountlyEvent(QObject *parent=NULL);
	CountlyEvent(QObject *parent, const QString &key, int count=1, double sum=0);
	virtual ~CountlyEvent();

	Q_INVOKABLE void setKey(const QString &key) { _key = key; }
	Q_INVOKABLE void setCount(int count) { _count = count; }
	Q_INVOKABLE void setCount(const QVariant &count) { _count = count.toInt(); }
	Q_INVOKABLE void setSum(double sum) { _sum = sum; }
	Q_INVOKABLE void setSum(const QVariant &sum) { _sum = sum.toDouble(); }
	Q_INVOKABLE void set(const QString &key, const QVariant &value) {
		_segmentation.insert(key, value);
	}

	Q_INVOKABLE void send();

	void populateUrl(QUrl &url);

	QVariant toVariant();
};

} /* namespace countly */
#endif /* COUNTLYEVENT_HPP_ */
