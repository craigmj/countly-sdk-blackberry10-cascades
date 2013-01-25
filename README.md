<html>
<body>
<h1>countly-sdk-blackberry10-cascades</h1>
<h1>=================================</h1>

<p>VERSION: alpha 1.0</p>

<p>NEXT VERSION: beta 1.0</p>

<p>A BlackBerry 10 Cascades SDK for count.ly</p>

<h2>Installing Countly BlackBerry 10 Cascades SDK</h2>

<ol>
<li>Add all the .cpp and .hpp files in the sdk/ directory to your project (I symlink them).</li>
<li>Add the following line to your .pro file:<br />
	<code>LIBS += -lbb -lbbdata -lbbplatform -lbbdevice</code>
</li>
<li>Add the Internet (<code>access_internet</code>) and Device Identifying Information (<code>read_device_identifying_information</code>) permissions to your bar-descriptor.xml</li>
</ol>

<h2>USAGE</h2>

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

<h2>PERSISTENCE</h2>
<p>
	By default, events are persisted to a sqlite database that the SDK will create in your app's data folder. Any events that are not successfully delivered, are persisted to this database, and the application will attempt to deliver them on the next execution.
</p>
<p>
	Because one does not want to fill a user's device with events, events are deleted if:
	<ol>
		<li>An attempt to deliver them receives a JSON reponse from the server, but it is not 'Success': in this case, we presume there is something wrong with the event, and discard it.</li>
		<li>There are more than 5 'sessions' (defined as a start of the app) and the event is part of a session that is more than 2 weeks old.</li>
	</ol>
	You can change these parameters by providing additional parameters to the CountlyInit function. It's full signature is:</p>
	<code>
		void CountlyInit(bb::cascades::Application *app, const QString &server, const QString &appKey,
			bool useDatabase=true, long maxPersistedSessions=-1, long sessionsExpireAfter=-1);
	</code>
	<p>The last 3 parameters are:</p>
	<dl>
		<dt>useDatabase</dt>
		<dd>Set to <code>false</code> if you don't want to persist events to the database.</dd>
		<dt>maxPersistedSessions</dt>
		<dd>Set to the maximum number of sessions that you want persisted. Note that sessions will only be discarded when there are more than that number AND they have exceeded the expiry period.</dd>
		<dt>sessionsExpireAfter</dt>
		<dd>The number of seconds after which a session is considered expired. After this period, AND if there are more than maxPersistedSessions, the excess sessions will be discarded.</dd>
	</dl>

<h2>EXAMPLE</h2>
<p>
See project example in <code>countly-sdk-example directory</code> for example application.
</p>

<h2>LOGGING</h2>
<p>The Count.ly framework logs through CountlyLog::log(..) method. Easy location to change or reroute logging. By default, no logs are written when in a Release build.</p>

<h2>TODOS</h2>
<ol>
	<li>It needs testing!</li>
	<li>QML integration only happens through calls to C++. I'm trying to work out a better method.</li>
</ol>

<h2>LICENCE</h2>
<p>
Please see the LICENCE file
</p>

</body>
</html>