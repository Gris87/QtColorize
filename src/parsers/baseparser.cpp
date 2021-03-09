#include "baseparser.h"

#include <texteditor/texteditor.h>

#include "src/qtcolorizecore.h"
#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



BaseParser::BaseParser(QObject *parent)
    : QObject(parent)
{
    COLORIZE_LOG(("BaseParser::BaseParser(parent = %p)", parent));
}

BaseParser::~BaseParser()
{
    COLORIZE_LOG(("BaseParser::~BaseParser()"));
}

QString BaseParser::singlelineComment() const
{
    COLORIZE_LOG(("BaseParser::singlelineComment()"));



    return "";
}

QString BaseParser::multilineCommentBegin() const
{
    COLORIZE_LOG(("BaseParser::multilineCommentBegin()"));



    return "";
}

QString BaseParser::multilineCommentEnd() const
{
    COLORIZE_LOG(("BaseParser::multilineCommentEnd()"));



    return "";
}

bool BaseParser::isValidFileExtension(const QString &filePath) const
{
    COLORIZE_LOG(("BaseParser::isValidFileExtension(filePath = \"%s\")", filePath.toUtf8().constData()));



    Q_UNUSED(filePath);



    return false;
}
