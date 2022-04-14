#include "proparser.h"

#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



ProParser::ProParser(QObject *parent)
    : BaseParser(parent)
{
    COLORIZE_LOG(("ProParser::ProParser(parent = %p)", parent));
}

ProParser::~ProParser()
{
    COLORIZE_LOG(("ProParser::~ProParser()"));
}

QString ProParser::singlelineComment() const
{
    COLORIZE_LOG(("ProParser::singlelineComment()"));



    return "#";
}

bool ProParser::isValidFileExtension(const QString &filePath) const
{
    COLORIZE_LOG(("ProParser::isValidFileExtension(filePath = \"%s\")", filePath.toUtf8().constData()));



    return filePath.endsWith(".pro") || filePath.endsWith(".pri");
}
