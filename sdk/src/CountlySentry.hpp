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
 * Simply utility class to manage a lock as RAII.
 * The lock is based around an AtomicInt, which functions as an inter-process semaphore.
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
