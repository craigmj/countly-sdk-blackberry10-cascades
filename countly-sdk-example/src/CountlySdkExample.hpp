// Default empty project template
#ifndef CountlySdkExample_HPP_
#define CountlySdkExample_HPP_

#include <QObject>

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class CountlySdkExample : public QObject
{
    Q_OBJECT
public:
    CountlySdkExample(bb::cascades::Application *app);
    virtual ~CountlySdkExample() {}

    Q_INVOKABLE void eventFromCpp(const QString &key, const QString &segment);
};


#endif /* CountlySdkExample_HPP_ */
