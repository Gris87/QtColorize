#include "makefileparser.h"

#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



MakefileParser::MakefileParser(QObject *parent)
    : BaseParser(parent)
{
    COLORIZE_LOG(("MakefileParser::MakefileParser(parent = %p)", parent));
}

MakefileParser::~MakefileParser()
{
    COLORIZE_LOG(("MakefileParser::~MakefileParser()"));
}

QString MakefileParser::singlelineComment() const
{
    COLORIZE_LOG(("MakefileParser::singlelineComment()"));



    return "#";
}

bool MakefileParser::isValidFileExtension(const QString &filePath) const
{
    COLORIZE_LOG(("MakefileParser::isValidFileExtension(filePath = \"%s\")", filePath.toUtf8().constData()));



    return filePath.endsWith("/Makefile");
}
