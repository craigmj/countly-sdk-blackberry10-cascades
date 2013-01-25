/*
 * CountlySentry.cpp
 *
 *  Created on: 25 Jan 2013
 *      Author: craig
 */

#include "CountlySentry.hpp"

#include <QThread>

namespace countly {

CountlySentry::CountlySentry(QAtomicInt *lock) : _lock(lock) {
	while (!_lock->testAndSetOrdered(0,1)) QThread::yieldCurrentThread();
}

CountlySentry::~CountlySentry() {
	bool succeeded = _lock->testAndSetOrdered(1,0);
	Q_ASSERT(succeeded);
	Q_UNUSED(succeeded);
}

} /* namespace countly */
