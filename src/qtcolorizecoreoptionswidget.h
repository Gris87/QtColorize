#ifndef QTCOLORIZECOREOPTIONSWIDGET_H
#define QTCOLORIZECOREOPTIONSWIDGET_H



#include <QWidget>

#include "src/qtcolorizecoresettings.h"



namespace QtColorize
{
namespace Internal
{



namespace Ui
{
class QtColorizeCoreOptionsWidget;
} // namespace Ui



class QtColorizeCoreOptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QtColorizeCoreOptionsWidget(QtColorizeCoreSettings *settings, QWidget *parent = nullptr);
    ~QtColorizeCoreOptionsWidget();

    const QtColorizeCoreSettings& settings() const;

private slots:
    void on_greenToolButton_clicked();
    void on_redToolButton_clicked();
    void on_greenResetToolButton_clicked();
    void on_redResetToolButton_clicked();
    void on_alignmentSpinBox_valueChanged(int value);

private:
    QString colorButtonStyleSheet(const QString &color);

    Ui::QtColorizeCoreOptionsWidget *ui;
    QtColorizeCoreSettings           mSettings;
};



} // namespace Internal
} // namespace QtColorize



#endif // QTCOLORIZECOREOPTIONSWIDGET_H
