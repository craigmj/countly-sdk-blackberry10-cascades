// Default empty project template
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

#include <QLocale>
#include <QTranslator>
#include <Qt/qdeclarativedebug.h>
#include "CountlySdkExample.hpp"

#include "Countly.hpp"

using namespace bb::cascades;

Q_DECL_EXPORT int main(int argc, char **argv)
{
    // this is where the server is started etc
    Application app(argc, argv);
    countly::CountlyInit(&app, "http://10.0.0.7/", "73c1dbd6b5a917bfb54f50a87f2dc11fca84d0b9");

    // localization support
    QTranslator translator;
    QString locale_string = QLocale().name();
    QString filename = QString( "countly_sdk_example_%1" ).arg( locale_string );
    if (translator.load(filename, "app/native/qm")) {
        app.installTranslator( &translator );
    }

    new CountlySdkExample(&app);

    // we complete the transaction started in the app constructor and start the client event loop here
    return Application::exec();
    // when loop is exited the Application deletes the scene which deletes all its children (per qt rules for children)
}
