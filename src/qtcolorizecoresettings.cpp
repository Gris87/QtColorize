#include "qtcolorizecoresettings.h"

#include "src/qtcolorizeconstants.h"
#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



QtColorizeCoreSettings::QtColorizeCoreSettings(QObject *parent)
    : QObject(parent)
    , greenColor(Constants::SETTING_GREEN_COLOR_DEFAULT)
    , redColor(Constants::SETTING_RED_COLOR_DEFAULT)
    , alignment(Constants::SETTING_ALIGNMENT_DEFAULT)
{
    COLORIZE_LOG(("QtColorizeCoreSettings::QtColorizeCoreSettings(parent = %p)", parent));
}

QtColorizeCoreSettings::QtColorizeCoreSettings(const QtColorizeCoreSettings &other, QObject *parent)
    : QObject(parent)
    , greenColor(other.greenColor)
    , redColor(other.redColor)
    , alignment(other.alignment)
{
    COLORIZE_LOG(("QtColorizeCoreSettings::QtColorizeCoreSettings(other = %s, parent = %p)", other.toString().toUtf8().constData(), parent));
}

QtColorizeCoreSettings::~QtColorizeCoreSettings()
{
    COLORIZE_LOG(("QtColorizeCoreSettings::~QtColorizeCoreSettings()"));
}

void QtColorizeCoreSettings::saveToSettings(QSettings *settings) const
{
    COLORIZE_LOG(("QtColorizeCoreSettings::saveToSettings(settings = %p)", settings));



    settings->beginGroup(Constants::CORE_SETTINGS_GROUP);
    settings->setValue(Constants::SETTING_GREEN_COLOR, greenColor);
    settings->setValue(Constants::SETTING_RED_COLOR,   redColor);
    settings->setValue(Constants::SETTING_ALIGNMENT,   alignment);
    settings->endGroup(); // CORE_SETTINGS_GROUP

    settings->sync();
}

void QtColorizeCoreSettings::loadFromSettings(QSettings *settings)
{
    COLORIZE_LOG(("QtColorizeCoreSettings::loadFromSettings(settings = %p)", settings));



    settings->beginGroup(Constants::CORE_SETTINGS_GROUP);
    greenColor = settings->value(Constants::SETTING_GREEN_COLOR, Constants::SETTING_GREEN_COLOR_DEFAULT).toString();
    redColor   = settings->value(Constants::SETTING_RED_COLOR,   Constants::SETTING_RED_COLOR_DEFAULT).toString();
    alignment  = settings->value(Constants::SETTING_ALIGNMENT,   Constants::SETTING_ALIGNMENT_DEFAULT).toULongLong();
    settings->endGroup(); // CORE_SETTINGS_GROUP
}

QtColorizeCoreSettings& QtColorizeCoreSettings::operator=(const QtColorizeCoreSettings &other)
{
    COLORIZE_LOG(("QtColorizeCoreSettings::operator=(other = %s)", other.toString().toUtf8().constData()));



    if (
        greenColor != other.greenColor
        ||
        redColor != other.redColor
        ||
        alignment != other.alignment
       )
    {
        greenColor = other.greenColor;
        redColor   = other.redColor;
        alignment  = other.alignment;

        COLORIZE_LOG(("emit settingsChanged()"));
        emit settingsChanged();
    }



    return *this;
}

QString QtColorizeCoreSettings::toString() const
{
    COLORIZE_LOG(("QtColorizeCoreSettings::toString()"));



    return QString("{ greenColor = \"%1\", redColor = \"%2\", alignment = %3 }")
            .arg(greenColor)
            .arg(redColor)
            .arg(alignment);
}
