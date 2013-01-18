countly-sdk-blackberry10-cascades
=================================

VERSION: alpha 0.1

A BlackBerry 10 Cascades SDK for count.ly

This is very first-draft code!

<h1>Installing Countly BlackBerry 10 Cascades SDK</h1>

<ol>
<li>Add all the .cpp and .hpp files in the sdk/ directory to your project (I symlink them).</li>
<li>Add the following line to your .pro file:<br />
	<code>LIBS += -lbb -lbbdata -lbbplatform -lbbdevice</code>
</li>
<li>Add the Internet (access_internet) and Device Identifying Information (read_device_identifying_information) permissions to your bar-descriptor.xml</li>
</ol>

<h1>Usage</h1>

<ol>
	<li>At the top of your main.cpp file:<br />
		<code>#include "Countly.hpp"</code>
	</li>
	<li>Just after your application is created in your main.cpp file, add:<br/>
		<code>countly::CountlyInit(&app, "http://10.0.0.6/", "73c1dbd6b5a917bfb54f50a87f2dc11fca84d0b9");</code>
		<br />
		Where the 10.0.0.6 is the address of your Count.ly server, and the 73... is your App Key from your
		Count.ly server
	</li>
	<li>Wherever you want to log a Count.ly event:<br />
		<ol>
			<li>Remember to <code>#include "Countly.hpp"</code></li>
			<li>
				<code>countly::CountlyEvent event(parentQObject, "key");
					event.set("segment_key", "segment_value");
					event.send();
				</code>
			</li>
		</ol>
	</li>
</ol>

EXAMPLE
=======
See project example in countly-sdk-example directory for example application.

LOGGING
=======
The Count.ly framework logs through CountlyLog::log(..) method. Easy location to change or reroute logging.

TODOS
=====
At the moment everything is very rough, and there is no queuing at all (the class is there, but not implemented), no heartbeat, and every event is sent when it is created, not held back and sent in the future.
Also, if the application cannot send an event at once, the event is discarded.

In other words, this is very much a bare-bones, just working implementation.

I'm working on queuing and storage for offline logging. And proper QML integration (at the moment, you need to send to a method on a C++ class - see the countly-sdk-example for example).

LICENCE
=======
Please see the LICENCE file