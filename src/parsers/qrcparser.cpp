#include "qrcparser.h"

#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



QrcParser::QrcParser(QObject *parent)
    : BaseParser(parent)
{
    COLORIZE_LOG(("QrcParser::QrcParser(parent = %p)", parent));
}

QrcParser::~QrcParser()
{
    COLORIZE_LOG(("QrcParser::~QrcParser()"));
}

QString QrcParser::multilineCommentBegin() const
{
    COLORIZE_LOG(("QrcParser::multilineCommentBegin()"));



    return "<!--";
}

QString QrcParser::multilineCommentEnd() const
{
    COLORIZE_LOG(("QrcParser::multilineCommentEnd()"));



    return "-->";
}

bool QrcParser::isValidFileExtension(const QString &filePath) const
{
    COLORIZE_LOG(("QrcParser::isValidFileExtension(filePath = \"%s\")", filePath.toUtf8().constData()));



    return filePath.endsWith(".qrc");
}
