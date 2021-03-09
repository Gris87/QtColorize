#include "qtcolorizeutils.h"

#include <QRegularExpression>

#include "src/qtcolorizelog.h"



#define REGEXP_PATTERN  "Colorize: *(\\w+)"
#define COMMENT_PATTERN "Colorize: %1"



using namespace QtColorize::Internal;



QString QtColorizeUtils::regexpPattern(BaseParser *parser)
{
    COLORIZE_LOG(("QtColorizeUtils::regexpPattern(parser = %p)", parser));



    QString singlelineComment = parser->singlelineComment();

    if (singlelineComment != "")
    {
        singlelineComment = QRegularExpression::escape(singlelineComment);

        return " *" + singlelineComment + " *" REGEXP_PATTERN;
    }
    else
    {
        QString multilineCommentBegin = QRegularExpression::escape(parser->multilineCommentBegin());
        QString multilineCommentEnd   = QRegularExpression::escape(parser->multilineCommentEnd());

        return " *" + multilineCommentBegin + " *" REGEXP_PATTERN " *" + multilineCommentEnd;
    }
}

QString QtColorizeUtils::commentPattern(BaseParser *parser)
{
    COLORIZE_LOG(("QtColorizeUtils::commentPattern(parser = %p)", parser));



    QString singlelineComment = parser->singlelineComment();

    if (singlelineComment != "")
    {
        return " " + singlelineComment + " " COMMENT_PATTERN;
    }
    else
    {
        QString multilineCommentBegin = parser->multilineCommentBegin();
        QString multilineCommentEnd   = parser->multilineCommentEnd();

        return " " + multilineCommentBegin + " " COMMENT_PATTERN " " + multilineCommentEnd;
    }
}
