/*
 * CountlySentry.hpp
 *
 *  Created on: 25 Jan 2013
 *      Author: craig
 */

#ifndef COUNTLYSENTRY_HPP_
#define COUNTLYSENTRY_HPP_

#include <QAtomicInt>

namespace countly {
/**
 * Simply utility class to manage a lock as RAII
 */
class CountlySentry {
protected:
	QAtomicInt *_lock;
public:
	CountlySentry(QAtomicInt *lock);
	virtual ~CountlySentry();
};

} /* namespace countly */
#endif /* COUNTLYSENTRY_HPP_ */
