#include "manifestparser.h"

#include "src/qtcolorizelog.h"



using namespace QtColorize::Internal;



ManifestParser::ManifestParser(QObject *parent)
    : BaseParser(parent)
{
    COLORIZE_LOG(("ManifestParser::ManifestParser(parent = %p)", parent));
}

ManifestParser::~ManifestParser()
{
    COLORIZE_LOG(("ManifestParser::~ManifestParser()"));
}

QString ManifestParser::multilineCommentBegin() const
{
    COLORIZE_LOG(("ManifestParser::multilineCommentBegin()"));



    return "<!--";
}

QString ManifestParser::multilineCommentEnd() const
{
    COLORIZE_LOG(("ManifestParser::multilineCommentEnd()"));



    return "-->";
}

bool ManifestParser::isValidFileExtension(const QString &filePath) const
{
    COLORIZE_LOG(("ManifestParser::isValidFileExtension(filePath = \"%s\")", filePath.toUtf8().constData()));



    return filePath.endsWith(".manifest");
}
