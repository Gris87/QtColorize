#include "gitignoreparser.h"

#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



GitIgnoreParser::GitIgnoreParser(QObject *parent)
    : BaseParser(parent)
{
    COLORIZE_LOG(("GitIgnoreParser::GitIgnoreParser(parent = %p)", parent));
}

GitIgnoreParser::~GitIgnoreParser()
{
    COLORIZE_LOG(("GitIgnoreParser::~GitIgnoreParser()"));
}

QString GitIgnoreParser::singlelineComment() const
{
    COLORIZE_LOG(("GitIgnoreParser::singlelineComment()"));



    return "#";
}

bool GitIgnoreParser::isValidFileExtension(const QString &filePath) const
{
    COLORIZE_LOG(("GitIgnoreParser::isValidFileExtension(filePath = \"%s\")", filePath.toUtf8().constData()));



    return filePath.endsWith("/.gitignore");
}
