#include "qtcolorizecoreoptionswidget.h"
#include "ui_qtcolorizecoreoptionswidget.h"

#include <QColorDialog>

#include "src/qtcolorizeconstants.h"
#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



QtColorizeCoreOptionsWidget::QtColorizeCoreOptionsWidget(QtColorizeCoreSettings *settings, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QtColorizeCoreOptionsWidget)
    , mSettings(*settings, nullptr)
{
    COLORIZE_LOG(("QtColorizeCoreOptionsWidget::QtColorizeCoreOptionsWidget(settings = %p, parent = %p)", settings, parent));



    ui->setupUi(this);

    ui->greenToolButton->setStyleSheet(colorButtonStyleSheet(mSettings.greenColor));
    ui->redToolButton->setStyleSheet(colorButtonStyleSheet(mSettings.redColor));

    ui->greenResetToolButton->setEnabled(mSettings.greenColor != Constants::SETTING_GREEN_COLOR_DEFAULT);
    ui->redResetToolButton->setEnabled(mSettings.redColor     != Constants::SETTING_RED_COLOR_DEFAULT);

    ui->alignmentSpinBox->setValue(mSettings.alignment);
}

QtColorizeCoreOptionsWidget::~QtColorizeCoreOptionsWidget()
{
    COLORIZE_LOG(("QtColorizeCoreOptionsWidget::~QtColorizeCoreOptionsWidget()"));



    delete ui;
}

const QtColorizeCoreSettings& QtColorizeCoreOptionsWidget::settings() const
{
    COLORIZE_LOG(("QtColorizeCoreOptionsWidget::settings()"));



    return mSettings;
}

QString QtColorizeCoreOptionsWidget::colorButtonStyleSheet(const QString &color)
{
    COLORIZE_LOG(("QtColorizeCoreOptionsWidget::colorButtonStyleSheet(color = \"%s\")", color.toUtf8().constData()));



    return "border: 2px solid black; border-radius: 2px; background:" + color;
}

void QtColorizeCoreOptionsWidget::on_greenToolButton_clicked()
{
    COLORIZE_LOG(("QtColorizeCoreOptionsWidget::on_greenToolButton_clicked()"));



    const QColor newColor = QColorDialog::getColor(QColor(mSettings.greenColor), window());

    if (newColor.isValid())
    {
        mSettings.greenColor = newColor.name().toUpper();

        ui->greenToolButton->setStyleSheet(colorButtonStyleSheet(mSettings.greenColor));
        ui->greenResetToolButton->setEnabled(mSettings.greenColor != Constants::SETTING_GREEN_COLOR_DEFAULT);
    }
}

void QtColorizeCoreOptionsWidget::on_redToolButton_clicked()
{
    COLORIZE_LOG(("QtColorizeCoreOptionsWidget::on_redToolButton_clicked()"));



    const QColor newColor = QColorDialog::getColor(QColor(mSettings.redColor), window());

    if (newColor.isValid())
    {
        mSettings.redColor = newColor.name().toUpper();

        ui->redToolButton->setStyleSheet(colorButtonStyleSheet(mSettings.redColor));
        ui->redResetToolButton->setEnabled(mSettings.redColor != Constants::SETTING_RED_COLOR_DEFAULT);
    }
}

void QtColorizeCoreOptionsWidget::on_greenResetToolButton_clicked()
{
    COLORIZE_LOG(("QtColorizeCoreOptionsWidget::on_greenResetToolButton_clicked()"));



    mSettings.greenColor = Constants::SETTING_GREEN_COLOR_DEFAULT;

    ui->greenToolButton->setStyleSheet(colorButtonStyleSheet(mSettings.greenColor));
    ui->greenResetToolButton->setEnabled(false);
}

void QtColorizeCoreOptionsWidget::on_redResetToolButton_clicked()
{
    COLORIZE_LOG(("QtColorizeCoreOptionsWidget::on_redResetToolButton_clicked()"));



    mSettings.redColor = Constants::SETTING_RED_COLOR_DEFAULT;

    ui->redToolButton->setStyleSheet(colorButtonStyleSheet(mSettings.redColor));
    ui->redResetToolButton->setEnabled(false);
}

void QtColorize::Internal::QtColorizeCoreOptionsWidget::on_alignmentSpinBox_valueChanged(int value)
{
    COLORIZE_LOG(("QtColorizeCoreOptionsWidget::on_alignmentSpinBox_valueChanged(value = %d)", value));



    mSettings.alignment = value;
}
