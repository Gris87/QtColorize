#include "bashparser.h"

#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



BashParser::BashParser(QObject *parent)
    : BaseParser(parent)
{
    COLORIZE_LOG(("BashParser::BashParser(parent = %p)", parent));
}

BashParser::~BashParser()
{
    COLORIZE_LOG(("BashParser::~BashParser()"));
}

QString BashParser::singlelineComment() const
{
    COLORIZE_LOG(("BashParser::singlelineComment()"));



    return "#";
}

bool BashParser::isValidFileExtension(const QString &filePath) const
{
    COLORIZE_LOG(("BashParser::isValidFileExtension(filePath = \"%s\")", filePath.toUtf8().constData()));



    return filePath.endsWith(".sh");
}
