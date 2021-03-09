#include "qtcolorizecoreoptionspage.h"

#include "src/qtcolorizeconstants.h"
#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



QtColorizeCoreOptionsPage::QtColorizeCoreOptionsPage(QtColorizeCoreSettings *settings, QObject *parent)
    : Core::IOptionsPage(parent)
    , mWidget(nullptr)
    , mSettings(settings)
{
    COLORIZE_LOG(("QtColorizeCoreOptionsPage::QtColorizeCoreOptionsPage(settings = %p, parent = %p)", settings, parent));



    setId("QtColorize::CoreSettings");
    setDisplayName(tr("Colorize"));
    setCategory("QtColorize");
    setDisplayCategory(tr("Colorize"));
    setCategoryIcon(Utils::Icon(Constants::ICON_QTCOLORIZEPLUGIN_OPTIONS));
}

QtColorizeCoreOptionsPage::~QtColorizeCoreOptionsPage()
{
    COLORIZE_LOG(("QtColorizeCoreOptionsPage::~QtColorizeCoreOptionsPage()"));
}

bool QtColorizeCoreOptionsPage::matches(const QRegularExpression &regexp) const
{
    COLORIZE_LOG(("QtColorizeCoreOptionsPage::matches(regexp = \"%s\")", regexp.pattern().toUtf8().constData()));



    return regexp.match("QtColorize").hasMatch();
}

QWidget* QtColorizeCoreOptionsPage::widget()
{
    COLORIZE_LOG(("QtColorizeCoreOptionsPage::widget()"));



    mWidget = new QtColorizeCoreOptionsWidget(mSettings);

    return mWidget;
}

void QtColorizeCoreOptionsPage::apply()
{
    COLORIZE_LOG(("QtColorizeCoreOptionsPage::apply()"));



    *mSettings = mWidget->settings();
}

void QtColorizeCoreOptionsPage::finish()
{
    COLORIZE_LOG(("QtColorizeCoreOptionsPage::finish()"));
}
