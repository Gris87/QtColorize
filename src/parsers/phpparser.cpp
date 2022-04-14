#include "phpparser.h"

#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



PhpParser::PhpParser(QObject *parent)
    : BaseParser(parent)
{
    COLORIZE_LOG(("PhpParser::PhpParser(parent = %p)", parent));
}

PhpParser::~PhpParser()
{
    COLORIZE_LOG(("PhpParser::~PhpParser()"));
}

QString PhpParser::singlelineComment() const
{
    COLORIZE_LOG(("PhpParser::singlelineComment()"));



    return "//";
}

QString PhpParser::multilineCommentBegin() const
{
    COLORIZE_LOG(("PhpParser::multilineCommentBegin()"));



    return "/*";
}

QString PhpParser::multilineCommentEnd() const
{
    COLORIZE_LOG(("PhpParser::multilineCommentEnd()"));



    return "*/";
}

bool PhpParser::isValidFileExtension(const QString &filePath) const
{
    COLORIZE_LOG(("PhpParser::isValidFileExtension(filePath = \"%s\")", filePath.toUtf8().constData()));



    return filePath.endsWith(".php");
}
