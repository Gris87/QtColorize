#include "asmparser.h"

#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



AsmParser::AsmParser(QObject *parent)
    : BaseParser(parent)
{
    COLORIZE_LOG(("AsmParser::AsmParser(parent = %p)", parent));
}

AsmParser::~AsmParser()
{
    COLORIZE_LOG(("AsmParser::~AsmParser()"));
}

QString AsmParser::singlelineComment() const
{
    COLORIZE_LOG(("AsmParser::singlelineComment()"));



    return "#";
}

bool AsmParser::isValidFileExtension(const QString &filePath) const
{
    COLORIZE_LOG(("AsmParser::isValidFileExtension(filePath = \"%s\")", filePath.toUtf8().constData()));



    return filePath.endsWith(".S");
}
