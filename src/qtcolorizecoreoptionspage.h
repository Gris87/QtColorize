#ifndef QTCOLORIZECOREOPTIONSPAGE_H
#define QTCOLORIZECOREOPTIONSPAGE_H



#include <coreplugin/dialogs/ioptionspage.h>

#include <QRegularExpression>

#include "src/qtcolorizecoreoptionswidget.h"
#include "src/qtcolorizecoresettings.h"



namespace QtColorize
{
namespace Internal
{



class QtColorizeCoreOptionsPage : public Core::IOptionsPage
{
    Q_OBJECT

public:
    explicit QtColorizeCoreOptionsPage(QtColorizeCoreSettings *settings, QObject *parent = nullptr);
    ~QtColorizeCoreOptionsPage();

    bool matches(const QRegularExpression &regexp) const override;
    QWidget* widget() override;
    void apply() override;
    void finish() override;

private:
    QtColorizeCoreOptionsWidget *mWidget;
    QtColorizeCoreSettings      *mSettings;
};



} // namespace Internal
} // namespace QtColorize



#endif // QTCOLORIZECOREOPTIONSPAGE_H
