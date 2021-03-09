#ifndef QTCOLORIZECORE_H
#define QTCOLORIZECORE_H



#include <QObject>

#include <QFutureWatcher>
#include <QTimer>

#include <texteditor/texteditor.h>

#include "src/parsers/baseparser.h"
#include "src/qtcolorizecoreoptionspage.h"
#include "src/qtcolorizecoresettings.h"
#include "src/qtcolorizefuture.h"



namespace QtColorize
{
namespace Internal
{



class QtColorizeCore : public QObject
{
    Q_OBJECT

public:
    explicit QtColorizeCore(QObject *parent = nullptr);
    ~QtColorizeCore();

    static QtColorizeCore* instance();

    void addParser(BaseParser *parser);

    void setCurrentParser(BaseParser *parser);
    void setCurrentEditor(TextEditor::BaseTextEditor *editor);

signals:
    void pluginSupported(bool supported);

public slots:
    void toggleColor();
    void colorGreen();
    void colorRed();
    void removeColor();

private slots:
    void settingsChanged();
    void editorOpened(Core::IEditor *editor);
    void managerEditorChanged(Core::IEditor *editor);
    void contentsChanged();
    void changeTimerTicked();
    void futureFinished();

private:
    void updateSelectedRows(QtColorizeRowType type, bool toggle = false);
    void cancelFuture();
    void startFuture();
    void updateRows();

    static QtColorizeCore                    *sInstance;
    QList<BaseParser *>                       mParsers;
    BaseParser                               *mCurrentParser;
    TextEditor::BaseTextEditor               *mCurrentEditor;
    QtColorizeCoreOptionsPage                *mQtColorizeCoreOptionsPage;
    QtColorizeCoreSettings                   *mQtColorizeCoreSettings;
    QTimer                                   *mChangeTimer;
    QtColorizeFuture                         *mFuture;
    QFutureWatcher<QList<QtColorizeRowType>> *mFutureWatcher;
    QList<QtColorizeRowType>                  mParsedRows;
};



} // namespace Internal
} // namespace QtColorize



#endif // QTCOLORIZECORE_H
