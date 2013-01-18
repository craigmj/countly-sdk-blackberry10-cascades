// Default empty project template
#include "CountlySdkExample.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

#include "Countly.hpp"

using namespace bb::cascades;

CountlySdkExample::CountlySdkExample(bb::cascades::Application *app)
: QObject(app)
{
    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("_base", this);

    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    // set created root object as a scene
    app->setScene(root);
}

void
CountlySdkExample::eventFromCpp(const QString &key, const QString &segment) {
	countly::CountlyEvent event(this, key);
	event.set("subkey", segment);
	event.send();
}

