/*
 * CountlyMetrics.hpp
 *
 *  Created on: 11 Jan 2013
 *      Author: craig
 *
 *  (c) 2013 Craig Mason-Jones. All Right Reserved.
 *  Please see LICENCE for licence details.
 *
 */

#ifndef COUNTLYMETRICS_HPP_
#define COUNTLYMETRICS_HPP_

#include <QObject>
#include <QString>
#include <QVariant>

namespace countly {

class CountlyMetrics : public QVariantMap {
public:
	CountlyMetrics();
	virtual ~CountlyMetrics();
	QString toJson();
};

} /* namespace countly */
#endif /* COUNTLYMETRICS_HPP_ */
