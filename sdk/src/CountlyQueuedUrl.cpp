/*
 * CountlyQueuedUrl.cpp
 *
 *  Created on: 25 Jan 2013
 *      Author: craig
 */

#include "CountlyQueuedUrl.hpp"

namespace countly {

CountlyQueuedUrl::CountlyQueuedUrl(QObject *parent, const QUrl &url, long id) : QObject(parent), _url(url), _id(id) {
}

CountlyQueuedUrl::~CountlyQueuedUrl() {}



} /* namespace countly */
