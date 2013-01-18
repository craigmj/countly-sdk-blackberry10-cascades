/*
 * Countly.hpp
 *
 *  Created on: 10 Jan 2013
 *      Author: craig
 */

#ifndef COUNTLY_HPP_
#define COUNTLY_HPP_

#include <QObject>
#include <QString>
#include <QTimer>

#include <bb/cascades/Application>


#include "CountlyEvent.hpp"
#include "CountlyLog.hpp"
#include "CountlyMetrics.hpp"
#include "CountlyQueue.hpp"

namespace countly {

class Countly : public QObject {
	Q_OBJECT
protected:
	static CountlyLog log;
	static Countly singleton;
	CountlyQueue *thread;
	QTimer _timer;
	QString _server;
	QString _appKey;
	QString _deviceId;
public:
	Countly();
	virtual ~Countly();
	static Countly *instance() { return &singleton; }
	void init(bb::cascades::Application *app, const QString &server, const QString &appKey);

public:
	void startApp();
	void stopApp();
	void pauseApp();
	void continueApp();
	void event();

	QUrl sendUrl(bool includeSessionDuration=true);
	void sendUrl(const QUrl &url);
	void sendEvent(CountlyEvent &event);

public slots:
	void thumbnail();
	void fullscreen();
	void invisible();
	void asleep();
	void awake();
	void aboutToQuit();
	void processStateChanged(bb::ProcessState::Type processState);
	void unixSignal(int);
	void timerTimeout();
};

void CountlyInit(bb::cascades::Application *app, const QString &server, const QString &appKey);


} /* namespace countly */
#endif /* COUNTLY_HPP_ */
