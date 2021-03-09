#include "sqlparser.h"

#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



SqlParser::SqlParser(QObject *parent)
    : BaseParser(parent)
{
    COLORIZE_LOG(("SqlParser::SqlParser(parent = %p)", parent));
}

SqlParser::~SqlParser()
{
    COLORIZE_LOG(("SqlParser::~SqlParser()"));
}

QString SqlParser::singlelineComment() const
{
    COLORIZE_LOG(("SqlParser::singlelineComment()"));



    return "--";
}

QString SqlParser::multilineCommentBegin() const
{
    COLORIZE_LOG(("SqlParser::multilineCommentBegin()"));



    return "/*";
}

QString SqlParser::multilineCommentEnd() const
{
    COLORIZE_LOG(("SqlParser::multilineCommentEnd()"));



    return "*/";
}

bool SqlParser::isValidFileExtension(const QString &filePath) const
{
    COLORIZE_LOG(("SqlParser::isValidFileExtension(filePath = \"%s\")", filePath.toUtf8().constData()));



    return filePath.endsWith(".sql");
}
