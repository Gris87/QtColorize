#ifndef QTCOLORIZEPLUGIN_H
#define QTCOLORIZEPLUGIN_H



#include <extensionsystem/iplugin.h>

#include "src/qtcolorizecore.h"



namespace QtColorize
{
namespace Internal
{



class QtColorizePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "QtColorize.json")

public:
    explicit QtColorizePlugin();
    ~QtColorizePlugin();

    bool initialize(const QStringList &arguments, QString *errorString) override;

private:
    void initLanguage();

    QtColorizeCore *mQtColorizeCore;
};



} // namespace Internal
} // namespace QtColorize



#endif // QTCOLORIZEPLUGIN_H
