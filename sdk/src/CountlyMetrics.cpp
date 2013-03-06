/*
 * CountlyMetrics.cpp
 *
 *  Created on: 11 Jan 2013
 *      Author: craig
 *
 *  (c) 2013 Craig Mason-Jones. All Right Reserved.
 *  Please see LICENCE for licence details.
 *
 */

#include "CountlyMetrics.hpp"

#include <QLocale>
#include <bb/ApplicationInfo>
#include <bb/data/JsonDataAccess>
#include <bb/device/CellularNetworkInfo>
#include <bb/device/DisplayInfo>
#include <bb/device/HardwareInfo>
#include <bb/platform/PlatformInfo>

using namespace bb::data;
using namespace bb::device;
using namespace bb::platform;

namespace countly {

CountlyMetrics::CountlyMetrics() {
	// These are the metrics we require
	/*
	  metrics={
		  "_os": "DDD",
		  "_os_version": "EEE",
		  "_device": "FFF",
		  "_resolution": "GGG",
		  "_carrier": "HHH",
		  "_app_version": "III"
  	  }
	 */
	// OS and OS_VERSION
	PlatformInfo platform;
	insert("_os", "BlackBerry");
	insert("_os_version", platform.osVersion());

	// DEVICE
	HardwareInfo hardware;
	insert("_device", hardware.deviceName() + " (" + hardware.modelNumber() + ")");
//	log.debug() << "pin: " << hardware.pin() << ", serial: " << hardware.serialNumber()
//			<< ", imei: " << hardware.imei() << ", meid: " << hardware.meid();}

	// Resolution
	DisplayInfo display;
	QString resolution;
	resolution.sprintf("%dx%d", display.pixelSize().width(), display.pixelSize().height());
	insert("_resolution", resolution);

	// CARRIER
	CellularNetworkInfo cell;
	insert("_carrier", cell.name() + " (" + cell.mobileCountryCode() + ":" + cell.mobileNetworkCode() + ")");


	// APP VERSION
	bb::ApplicationInfo application;
	insert("_app_version", application.version());

	// LOCALE
	QLocale locale;
	insert ("_locale", locale.name());
}

CountlyMetrics::~CountlyMetrics() {
}

QString
CountlyMetrics::toJson() {
	JsonDataAccess json;
	QString jsonString;
	json.saveToBuffer(*this, &jsonString);
	return jsonString;
}

} /* namespace countly */
