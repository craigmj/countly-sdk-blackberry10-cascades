/*
 * CountlyQueue.hpp
 *
 *  Created on: 11 Jan 2013
 *      Author: craig
 */

#ifndef COUNTLYQUEUE_HPP_
#define COUNTLYQUEUE_HPP_


#include <QObject>
#include <QThread>

#include "CountlyLog.hpp"

namespace countly {

class CountlyQueue : public QThread {
	Q_OBJECT
protected:
	static CountlyLog log;
public:
	CountlyQueue();
	virtual ~CountlyQueue();

	virtual void run();


};
} /* namespace countly */
#endif /* COUNTLYQUEUE_HPP_ */
