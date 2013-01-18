/*
 * Countly.cpp
 *
 *  Created on: 10 Jan 2013
 *      Author: craig
 */

#include "Countly.hpp"
#include "CountlyEvent.hpp"
#include "CountlyRequest.hpp"

#include <QObject>
#include <bb/device/DisplayInfo>
#include <bb/device/HardwareInfo>

#include <bb/data/JsonDataAccess>

#include "CountlyLog.hpp"

using namespace bb::data;
using namespace bb::device;
using namespace bb::cascades;

namespace countly {

Countly Countly::singleton;
CountlyLog Countly::log("Countly");

Countly::Countly() : QObject(NULL) {
}

Countly::~Countly() {
}

void
CountlyInit(bb::cascades::Application *app, const QString &server, const QString &appKey) {
	Countly::instance()->init(app, server, appKey);
	qmlRegisterType<Countly>("count.ly", 1, 0, "CountlyEvent");
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

	HardwareInfo hardware;
	QCryptographicHash hash(QCryptographicHash::Sha1);
	hash.addData(hardware.pin().toAscii());
	hash.addData(hardware.serialNumber().toAscii());
	hash.addData(hardware.imei().toAscii());
	_deviceId = hash.result().toHex();

	if (!QObject::connect(app, SIGNAL(thumbnail()), this, SLOT(thumbnail()))) {
		log.severe() << "failed to connect to thumbnail()";
	}
	if (!QObject::connect(app, SIGNAL(fullscreen()), this, SLOT(fullscreen()))) {
		log.severe() << "failed to connect to fullscreen()";
	}
	if (!QObject::connect(app, SIGNAL(invisible()), this, SLOT(invisible()))) {
		log.severe() << "failed to connect to invisible()";
	}
	if (!QObject::connect(app, SIGNAL(asleep()), this, SLOT(asleep()))) {
		log.severe() << "failed to connect to asleep()";
	}
	if (!QObject::connect(app, SIGNAL(awake()), this, SLOT(awake()))) {
		log.severe() << "failed to connect to awake()";
	}
	if (!QObject::connect(app, SIGNAL(aboutToQuit()), this, SLOT(aboutToQuit()))) {
		log.severe() << "failed to connect to aboutToQuit";
	}
	if (!QObject::connect(app, SIGNAL(processStateChanged(bb::ProcessState::Type)), this,
			SLOT(processStateChanged(bb::ProcessState::Type)))) {
		log.severe() << "failed to connect to processStateChanged";
	}

	if (!QObject::connect(app, SIGNAL(unixSignal(int)), this, SLOT(unixSignal(int)))) {
		log.severe() << "failed to connect to unixSignal";
	}

	_timer.setInterval(30 * 1000);
	if (!QObject::connect(&_timer, SIGNAL(timeout()), this, SLOT(timerTimeout()))) {
		log.severe() << "failed to connect to QTimer::timeout()";
	}

	startApp();
}


void
Countly::thumbnail() {
	log.debug() << "thumbnail";
}

void
Countly::fullscreen() {
	log.debug() << "fullscreen";
}

void
Countly::invisible() {
	log.debug() << "invisible";
}

void
Countly::asleep() {
	log.debug() << "asleep";
}

void
Countly::awake() {
	log.debug() << "awake";
}

void
Countly::aboutToQuit() {
	log.debug() << "aboutToQuit";
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
	log.debug() << "processStateChanged(" << processState << ")";
}

void
Countly::startApp() {
	CountlyMetrics metrics;
	QUrl url = sendUrl(false);
	url.addQueryItem("begin_session", "1");
	url.addQueryItem("metrics", metrics.toJson());
	url.addQueryItem("sdk_version", "1.0");
	sendUrl(url);
//	_timer.start();
}

void
Countly::stopApp() {
	QUrl url = sendUrl();
	url.addQueryItem("end_session", "1");
	sendUrl(url);
	_timer.stop();
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
Countly::sendUrl(bool includeSessionDuration) {
	QUrl url(_server);
	url.addQueryItem("app_key", _appKey);
	url.addQueryItem("device_id", _deviceId);
	if (includeSessionDuration) {
		url.addQueryItem("session_duration", "30");
	}
	return  url;
}

void
Countly::sendUrl(const QUrl &url) {
	new CountlyRequest(url);
}

void
Countly::sendEvent(CountlyEvent &event) {
	QVariantList events;
	events.append(event.toVariant());
	JsonDataAccess json;
	QString eventsString;
	json.saveToBuffer(events, &eventsString);
	QUrl url(sendUrl());

	url.addQueryItem("events", eventsString);
	sendUrl(url);
}

void
Countly::timerTimeout() {
	log.debug() << "timer timeout";
	QUrl url = sendUrl();
	QVariantList events;
	if (0 < events.size()) {
		JsonDataAccess json;
		QString eventsString;
		json.saveToBuffer(events, &eventsString);
		url.addQueryItem("events", eventsString);
	}
	sendUrl(url);
}


} /* namespace countly */
