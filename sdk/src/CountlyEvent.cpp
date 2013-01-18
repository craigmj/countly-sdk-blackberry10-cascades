/*
 * CountlyEvent.cpp
 *
 *  Created on: 11 Jan 2013
 *      Author: craig
 */

#include "CountlyEvent.hpp"
#include "CountlyRequest.hpp"

#include "Countly.hpp"

#include <bb/data/JsonDataAccess>

using namespace bb::data;

namespace countly {

CountlyLog CountlyEvent::log("CountlyEvent");

CountlyEvent::CountlyEvent(QObject *parent) : QObject(parent) {}

CountlyEvent::CountlyEvent(QObject *parent, const QString &key, int count, double sum) : QObject(parent), _key(key), _count(count), _sum(sum) {
}

CountlyEvent::~CountlyEvent() {
}

void
CountlyEvent::send() {
	Countly::instance()->sendEvent(*this);
}

void
CountlyEvent::populateUrl(QUrl &url) {
	url.addQueryItem("key", _key);
	QString count;
	count.sprintf("%d", _count);
	url.addQueryItem("count", count);
	if (0!=_sum) {
		QString sum;
		sum.sprintf("%f", _sum);
		url.addQueryItem("sum", sum);
	}
	JsonDataAccess json;
	QString jsonString;
	json.saveToBuffer(_segmentation, &jsonString);

	url.addQueryItem("segmentation", jsonString);
}

QVariant
CountlyEvent::toVariant() {
	QVariantMap var;
	var.insert("key", _key);
	var.insert("count", QVariant(_count));
	if (0.0!=_sum) {
		var.insert("sum", QVariant(_sum));
	}
	var.insert("segmentation", _segmentation);
	return var;
}

} /* namespace countly */
