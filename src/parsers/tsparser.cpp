#include "tsparser.h"

#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



TsParser::TsParser(QObject *parent)
    : BaseParser(parent)
{
    COLORIZE_LOG(("TsParser::TsParser(parent = %p)", parent));
}

TsParser::~TsParser()
{
    COLORIZE_LOG(("TsParser::~TsParser()"));
}

QString TsParser::multilineCommentBegin() const
{
    COLORIZE_LOG(("TsParser::multilineCommentBegin()"));



    return "<!--";
}

QString TsParser::multilineCommentEnd() const
{
    COLORIZE_LOG(("TsParser::multilineCommentEnd()"));



    return "-->";
}

bool TsParser::isValidFileExtension(const QString &filePath) const
{
    COLORIZE_LOG(("TsParser::isValidFileExtension(filePath = \"%s\")", filePath.toUtf8().constData()));



    return filePath.endsWith(".ts");
}
