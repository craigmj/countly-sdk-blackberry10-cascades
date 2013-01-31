/*
 * Countly.hpp
 *
 *  Created on: 10 Jan 2013
 *      Author: craig
 *
 *  (c) 2013 Craig Mason-Jones. All Right Reserved.
 *  Please see LICENCE for licence details.
 */

#ifndef COUNTLY_HPP_
#define COUNTLY_HPP_

#include <QObject>
#include <QString>
#include <QTimer>

#include <QtNetwork/QNetworkAccessManager>

#include <bb/cascades/Application>


#include "CountlyEvent.hpp"
#include "CountlyLog.hpp"
#include "CountlyMetrics.hpp"
#include "CountlyQueue.hpp"

namespace countly {

/**
 * Countly class for recording application analytics with Count.ly server.
 *
 *
 */
class Countly : public QObject {
	Q_OBJECT
protected:
	static CountlyLog log;
	static Countly singleton;

	bb::cascades::Application *_app;
	CountlyQueue _queue;
	QTimer _timer;
	QString _server;
	QString _appKey;
	QString _deviceId;

public:
	Countly();
	virtual ~Countly();

	/** Return singleton instance of the Countly interface*/
	static Countly *instance() { return &singleton; }

	/**
	 * Initialize the Countly interface.
	 * @param app Pointer to the application instance. This is necessary to ensure that Count.ly can
	 * track when the app has started (when init is called), and when it closes.
	 * @param server String address of your count.ly server. e.g. "http://cloud.count.ly". Do not add the full
	 * path information ("/i?") - the class will add this itself.
	 * @param appKey The application key for your application in Count.ly.
	 */
	void init(bb::cascades::Application *app, const QString &server, const QString &appKey, 			bool useDatabase=true, long maxPersistedSessions=-1, long sessionsExpireAfter=-1);

	/*------------------------------------- methods used by CountlyEvent class -----------------------------*/
	/**  Return the number of seconds since the epoch */
	static qint64 secondsSinceEpoch();
	void sendEvent(CountlyEvent &event);

public:
	void startApp();
	void stopApp();
	void pauseApp();
	void continueApp();
	void event();

protected:
	QUrl createSendUrl();
	void sendUrl(const QUrl &url);

public:

public slots:
	void thumbnail();
	void fullscreen();
	void invisible();
	void asleep();
	void awake();
	void aboutToQuit();
	void manualExit();
	void processStateChanged(bb::ProcessState::Type processState);
	void unixSignal(int);
	void timerTimeout();
};

void CountlyInit(bb::cascades::Application *app, const QString &server, const QString &appKey,
			bool useDatabase=true, long maxPersistedSessions=-1, long sessionsExpireAfter=-1);


} /* namespace countly */
#endif /* COUNTLY_HPP_ */
