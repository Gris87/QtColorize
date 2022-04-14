#include "qtcolorizefuture.h"

#include <QRegularExpression>

#include "src/qtcolorizelog.h"
#include "src/qtcolorizeutils.h"



using namespace QtColorize::Internal;



QtColorizeFuture::QtColorizeFuture(BaseParser *parser, TextEditor::BaseTextEditor *editor, QObject *parent)
    : QObject(parent)
    , mParser(parser)
    , mText("")
{
    COLORIZE_LOG(("QtColorizeFuture::QtColorizeFuture(parser = %p, editor = %p, parent = %p)", parser, editor, parent));



    mText = editor->editorWidget()->toPlainText();
}

QtColorizeFuture::~QtColorizeFuture()
{
    COLORIZE_LOG(("QtColorizeFuture::~QtColorizeFuture()"));
}

void QtColorizeFuture::process(QFutureInterface<QList<QtColorizeRowType>> &future)
{
    COLORIZE_LOG(("QtColorizeFuture::process(future)"));



    QList<QtColorizeRowType> res;



    QRegularExpression regexp(QtColorizeUtils::regexpPattern(mParser));



    QStringList lines = mText.split('\n');

    for (qint64 i = 0; i < lines.size() && !future.isCanceled(); ++i)
    {
        QRegularExpressionMatch match = regexp.match(lines.at(i));

        if (match.hasMatch())
        {
            QString color = match.captured(1);

            if (color == "green")
            {
                res.append(QtColorizeRowType::GREEN);
            }
            else
            if (color == "red")
            {
                res.append(QtColorizeRowType::RED);
            }
            else
            {
                res.append(QtColorizeRowType::NONE);
            }
        }
        else
        {
            res.append(QtColorizeRowType::NONE);
        }
    }



    if (future.isCanceled())
    {
        future.reportCanceled();
        return;
    }

    future.reportResult(res);
}
