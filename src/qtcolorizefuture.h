#ifndef QTCOLORIZEFUTURE_H
#define QTCOLORIZEFUTURE_H



#include <QObject>

#include <QFuture>

#include <texteditor/texteditor.h>

#include "src/parsers/baseparser.h"
#include "src/qtcolorizerowtype.h"



namespace QtColorize
{
namespace Internal
{



class QtColorizeFuture : public QObject
{
    Q_OBJECT

public:
    explicit QtColorizeFuture(BaseParser *parser, TextEditor::BaseTextEditor *editor, QObject *parent = nullptr);
    ~QtColorizeFuture();

    void process(QFutureInterface<QList<QtColorizeRowType>> &future);

private:
    BaseParser *mParser;
    QString     mText;
};



} // namespace Internal
} // namespace QtColorize



#endif // QTCOLORIZEFUTURE_H
