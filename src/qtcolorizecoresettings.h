#ifndef QTCOLORIZECORESETTINGS_H
#define QTCOLORIZECORESETTINGS_H



#include <QObject>
#include <QSettings>



namespace QtColorize
{
namespace Internal
{



class QtColorizeCoreSettings : public QObject
{
    Q_OBJECT

public:
    explicit QtColorizeCoreSettings(QObject *parent = nullptr);
    explicit QtColorizeCoreSettings(const QtColorizeCoreSettings &other, QObject *parent = nullptr);
    ~QtColorizeCoreSettings();

    void saveToSettings(QSettings *settings) const;
    void loadFromSettings(QSettings *settings);

    QtColorizeCoreSettings& operator=(const QtColorizeCoreSettings &other);

    QString toString() const;

    QString greenColor;
    QString redColor;
    quint16 alignment;

signals:
    void settingsChanged();
};



} // namespace Internal
} // namespace QtColorize



#endif // QTCOLORIZECORESETTINGS_H
