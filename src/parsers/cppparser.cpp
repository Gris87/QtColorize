#include "cppparser.h"

#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



CppParser::CppParser(QObject *parent)
    : BaseParser(parent)
{
    COLORIZE_LOG(("CppParser::CppParser(parent = %p)", parent));
}

CppParser::~CppParser()
{
    COLORIZE_LOG(("CppParser::~CppParser()"));
}

QString CppParser::singlelineComment() const
{
    COLORIZE_LOG(("CppParser::singlelineComment()"));



    return "//";
}

QString CppParser::multilineCommentBegin() const
{
    COLORIZE_LOG(("CppParser::multilineCommentBegin()"));



    return "/*";
}

QString CppParser::multilineCommentEnd() const
{
    COLORIZE_LOG(("CppParser::multilineCommentEnd()"));



    return "*/";
}

bool CppParser::isValidFileExtension(const QString &filePath) const
{
    COLORIZE_LOG(("CppParser::isValidFileExtension(filePath = \"%s\")", filePath.toUtf8().constData()));



    return filePath.endsWith(".cpp") || filePath.endsWith(".h");
}
