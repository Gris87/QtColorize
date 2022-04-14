#include "markdownparser.h"

#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



MarkdownParser::MarkdownParser(QObject *parent)
    : BaseParser(parent)
{
    COLORIZE_LOG(("MarkdownParser::MarkdownParser(parent = %p)", parent));
}

MarkdownParser::~MarkdownParser()
{
    COLORIZE_LOG(("MarkdownParser::~MarkdownParser()"));
}

QString MarkdownParser::singlelineComment() const
{
    COLORIZE_LOG(("MarkdownParser::singlelineComment()"));



    return "//";
}

bool MarkdownParser::isValidFileExtension(const QString &filePath) const
{
    COLORIZE_LOG(("MarkdownParser::isValidFileExtension(filePath = \"%s\")", filePath.toUtf8().constData()));



    return filePath.endsWith(".md");
}
