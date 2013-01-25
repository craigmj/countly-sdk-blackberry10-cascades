/*
 * CountlyEvent.cpp
 *
 *  Created on: 11 Jan 2013
 *      Author: craig
 *
 *  (c) 2013 Craig Mason-Jones. All Right Reserved.
 *  Please see LICENCE for licence details.
 *
 */

#include "CountlyEvent.hpp"

#include "Countly.hpp"

#include <bb/data/JsonDataAccess>

using namespace bb::data;

namespace countly {

CountlyLog CountlyEvent::log("CountlyEvent");

CountlyEvent::CountlyEvent(QObject *parent) : QObject(parent) {
	_timestamp = Countly::secondsSinceEpoch();
}

CountlyEvent::CountlyEvent(QObject *parent, const QString &key, int count, double sum, long timestamp) : QObject(parent), _key(key), _count(count), _sum(sum) {
	_timestamp = (0==timestamp) ? timestamp : Countly::secondsSinceEpoch();
}

CountlyEvent::~CountlyEvent() {

}

void
CountlyEvent::send() {
	Countly::instance()->sendEvent(*this);
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
