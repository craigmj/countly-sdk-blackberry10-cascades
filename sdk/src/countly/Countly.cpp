/*
 * Countly.cpp
 *
 *  Created on: 10 Jan 2013
 *      Author: craig
 *
 *  (c) 2013 Craig Mason-Jones. All Right Reserved.
 *  Please see LICENCE for licence details.
 *
 */

#include "Countly.hpp"
#include "CountlyEvent.hpp"
#include "CountlyRequest.hpp"

#include <QObject>
#include <QDateTime>

#include <bb/device/DisplayInfo>
#include <bb/device/HardwareInfo>
#include <bb/data/JsonDataAccess>

#include "CountlyLog.hpp"

using namespace bb::data;
using namespace bb::device;
using namespace bb::cascades;

namespace countly {

const int HEARTBEAT_INTERVAL = 10;

Countly Countly::singleton;
CountlyLog Countly::log("Countly");

Countly::Countly() : QObject(NULL), _queue(this) {
}

Countly::~Countly() {
}

void
CountlyInit(bb::cascades::Application *app, const QString &server, const QString &appKey) {
	Countly::instance()->init(app, server, appKey);
	qmlRegisterType<CountlyEvent>("count.ly", 1, 0, "CountlyEvent");
}

void
Countly::init(bb::cascades::Application *app, const QString &server, const QString &appKey) {
	QRegExp httpRegexp("^https?://.*");
	if (httpRegexp.exactMatch(server)) {
		_server = server;
	} else {
		_server = "http://" + server;
	}
	QRegExp pathRegexp(".*/i$");
	if (!pathRegexp.exactMatch(server)) {
		QRegExp slashRegexp(".*/$");
		if (!slashRegexp.exactMatch(server)) {
			_server += "/";
		}
		_server += "i";
	}

	_appKey = appKey;

	/* We calculate the deviceId as a cryptographic hash of hardware pin, serialNumber and imei.
	 * Should be unique, and will remain anonymous when it reaches count.ly server.
	 */
	HardwareInfo hardware;
	QCryptographicHash hash(QCryptographicHash::Sha1);
	hash.addData(hardware.pin().toAscii());
	hash.addData(hardware.serialNumber().toAscii());
	hash.addData(hardware.imei().toAscii());
	_deviceId = hash.result().toHex();

	if (!QObject::connect(app, SIGNAL(thumbnail()), this, SLOT(thumbnail()))) {
		COUNTLY_SEVERE(log, "failed to connect to thumbnail()");
	}
	if (!QObject::connect(app, SIGNAL(fullscreen()), this, SLOT(fullscreen()))) {
		COUNTLY_SEVERE(log, "failed to connect to fullscreen()");
	}
	if (!QObject::connect(app, SIGNAL(invisible()), this, SLOT(invisible()))) {
		COUNTLY_SEVERE(log, "failed to connect to invisible()");
	}
	if (!QObject::connect(app, SIGNAL(asleep()), this, SLOT(asleep()))) {
		COUNTLY_SEVERE(log, "failed to connect to asleep()");
	}
	if (!QObject::connect(app, SIGNAL(awake()), this, SLOT(awake()))) {
		COUNTLY_SEVERE(log, "failed to connect to awake()");
	}
	if (!QObject::connect(app, SIGNAL(aboutToQuit()), this, SLOT(aboutToQuit()))) {
		COUNTLY_SEVERE(log, "failed to connect to aboutToQuit");
	}
	if (!QObject::connect(app, SIGNAL(processStateChanged(bb::ProcessState::Type)), this,
			SLOT(processStateChanged(bb::ProcessState::Type)))) {
		COUNTLY_SEVERE(log, "failed to connect to processStateChanged");
	}

	if (!QObject::connect(app, SIGNAL(unixSignal(int)), this, SLOT(unixSignal(int)))) {
		COUNTLY_SEVERE(log, "failed to connect to unixSignal");
	}

	_timer.setInterval(HEARTBEAT_INTERVAL * 1000);
	if (!QObject::connect(&_timer, SIGNAL(timeout()), this, SLOT(timerTimeout()))) {
		COUNTLY_SEVERE(log, "failed to connect to QTimer::timeout()");
	}

	startApp();
}


void
Countly::thumbnail() {
//	COUNTLY_DEBUG(log, "thumbnail");
}

void
Countly::fullscreen() {
//	COUNTLY_DEBUG(log, "fullscreen");
}

void
Countly::invisible() {
//	COUNTLY_DEBUG(log, "invisible");
}

void
Countly::asleep() {
//	COUNTLY_DEBUG(log, "asleep");
	_timer.stop();
}

void
Countly::awake() {
//	COUNTLY_DEBUG(log, "awake");
	_timer.start();
}

void
Countly::aboutToQuit() {
//	COUNTLY_DEBUG(log, "aboutToQuit");
	stopApp();
}

void
Countly::unixSignal(int sig) {
	CountlyEvent event(this, "signal");
	event.set("sig", QVariant(sig));
	event.send();
}

void
Countly::processStateChanged(bb::ProcessState::Type processState) {
	Q_UNUSED(processState);
//	COUNTLY_DEBUG(log, "processStateChanged(" << processState << ")");
}

void
Countly::startApp() {
	CountlyMetrics metrics;
	QUrl url = createSendUrl(false);
	url.addQueryItem("begin_session", "1");
	url.addQueryItem("metrics", metrics.toJson());
	url.addQueryItem("sdk_version", "1.0");
	sendUrl(url);
	_timer.start();
	_queue.flush();
}

void
Countly::stopApp() {
	QUrl url = createSendUrl();
	url.addQueryItem("end_session", "1");
	sendUrl(url);
	_timer.stop();
	_queue.flushAndWait(10);
}

void
Countly::pauseApp() {
	// @TODO Implement pausing of an app
}

void
Countly::continueApp() {
	// @TODO Implement app continuation
}

void
Countly::event() {

}

QUrl
Countly::createSendUrl(bool includeSessionDuration) {
	QUrl url(_server);
	url.addQueryItem("app_key", _appKey);
	url.addQueryItem("device_id", _deviceId);
	QString timestamp;
	long sec = secondsSinceEpoch();
	timestamp.sprintf("%ld", sec);
	url.addQueryItem("timestamp", timestamp);
	if (includeSessionDuration) {
		QString sessionDuration;
		sessionDuration.sprintf("%d", HEARTBEAT_INTERVAL);
		url.addQueryItem("session_duration", sessionDuration);
	}
	return  url;
}

void
Countly::sendUrl(const QUrl &url) {
	_queue.queue(url);
}

void
Countly::sendEvent(CountlyEvent &event) {
	QVariantList events;
	events.append(event.toVariant());
	JsonDataAccess json;
	QString eventsString;
	json.saveToBuffer(events, &eventsString);
	QUrl url(createSendUrl());

	url.addQueryItem("events", eventsString);
	sendUrl(url);
}

void
Countly::timerTimeout() {
	COUNTLY_DEBUG(log, "timer timeout");
	QUrl url = createSendUrl();
	sendUrl(url);
	_queue.flush();
}

qint64
Countly::secondsSinceEpoch() {
	return QDateTime::currentDateTime().toMSecsSinceEpoch()/1000;
}

} /* namespace countly */
